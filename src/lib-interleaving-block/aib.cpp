/// \file
/// Command-line tool for adding nondeterministic interleaving call blocks
/// across an entire project tree.

#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace
{
using line_to_namest = std::map<std::size_t, std::vector<std::string>>;
using file_to_linet = std::map<std::string, line_to_namest>;

struct project_configt
{
  std::string project_root;
  std::vector<std::string> interleaving_source_files;
  std::vector<std::string> translation_units;
  std::string interleaving_array_json;
  file_to_linet file_to_lines;
};

struct aib_ignoret
{
  std::set<std::string> files;
  std::set<std::string> directory_prefixes;
};

std::string trim(const std::string &s)
{
  const auto first = s.find_first_not_of(" \t\r\n");
  if(first == std::string::npos)
    return "";

  const auto last = s.find_last_not_of(" \t\r\n");
  return s.substr(first, last - first + 1);
}

bool read_file(const std::string &file, std::string &content)
{
  std::ifstream in(file);
  if(!in)
    return false;

  std::ostringstream buffer;
  buffer << in.rdbuf();
  content = buffer.str();
  return true;
}

std::string normalize_relative_path(const std::string &path)
{
  return std::filesystem::path(path).lexically_normal().generic_string();
}

std::string normalize_absolute_path(const std::string &path)
{
  return std::filesystem::absolute(std::filesystem::path(path))
    .lexically_normal()
    .generic_string();
}

bool path_matches_or_is_within(
  const std::string &candidate_path,
  const std::string &root_path)
{
  const std::string normalized_candidate = normalize_absolute_path(candidate_path);
  const std::string normalized_root = normalize_absolute_path(root_path);

  if(normalized_candidate == normalized_root)
    return true;

  if(normalized_candidate.size() <= normalized_root.size())
    return false;

  return
    normalized_candidate.compare(0, normalized_root.size(), normalized_root) ==
      0 &&
    normalized_candidate[normalized_root.size()] == '/';
}

std::string json_escape(const std::string &value)
{
  std::ostringstream escaped;
  for(char ch : value)
  {
    switch(ch)
    {
    case '\\':
      escaped << "\\\\";
      break;
    case '"':
      escaped << "\\\"";
      break;
    case '\n':
      escaped << "\\n";
      break;
    case '\r':
      escaped << "\\r";
      break;
    case '\t':
      escaped << "\\t";
      break;
    default:
      escaped << ch;
      break;
    }
  }

  return escaped.str();
}

std::string relative_project_path(
  const std::filesystem::path &path,
  const std::filesystem::path &project_root)
{
  return std::filesystem::relative(path, project_root)
    .lexically_normal()
    .generic_string();
}

bool starts_with(const std::string &value, const std::string &prefix)
{
  return value.compare(0, prefix.size(), prefix) == 0;
}

bool is_ignored_path(
  const aib_ignoret &ignore,
  const std::string &relative_path)
{
  const std::string normalized_path = normalize_relative_path(relative_path);
  if(ignore.files.find(normalized_path) != ignore.files.end())
    return true;

  for(const auto &directory_prefix : ignore.directory_prefixes)
  {
    const std::string directory_name =
      directory_prefix.substr(0, directory_prefix.size() - 1);
    if(
      normalized_path == directory_name ||
      starts_with(normalized_path, directory_prefix))
    {
      return true;
    }
  }

  return false;
}

bool load_aibignore(
  const std::string &project_root,
  aib_ignoret &ignore)
{
  ignore = aib_ignoret{};
  const auto ignore_path =
    std::filesystem::path(project_root).lexically_normal() / ".aibignore";

  if(!std::filesystem::exists(ignore_path))
    return true;

  if(!std::filesystem::is_regular_file(ignore_path))
  {
    std::cerr << "error: .aibignore exists but is not a regular file: "
              << ignore_path.string() << '\n';
    return false;
  }

  std::ifstream in(ignore_path);
  if(!in)
  {
    std::cerr << "error: unable to open .aibignore file: "
              << ignore_path.string() << '\n';
    return false;
  }

  std::string line;
  std::size_t line_number = 0;
  while(std::getline(in, line))
  {
    ++line_number;
    const std::string rule = trim(line);
    if(rule.empty() || rule[0] == '#')
      continue;

    if(rule.find('!') != std::string::npos || rule.find('*') != std::string::npos)
    {
      std::cerr << "error: unsupported .aibignore rule on line " << line_number
                << ": " << rule << '\n';
      return false;
    }

    if(std::filesystem::path(rule).is_absolute())
    {
      std::cerr << "error: .aibignore rules must be relative to project_root: "
                << rule << '\n';
      return false;
    }

    const std::string normalized_rule = normalize_relative_path(rule);
    if(normalized_rule.empty() || normalized_rule == ".")
    {
      std::cerr << "error: invalid .aibignore rule on line " << line_number
                << ": " << rule << '\n';
      return false;
    }

    if(rule.back() == '/')
      ignore.directory_prefixes.insert(
        normalize_relative_path(rule.substr(0, rule.size() - 1)) + "/");
    else
      ignore.files.insert(normalized_rule);
  }

  ignore.files.insert(".aibignore");

  return true;
}

std::vector<std::string>
extract_top_level_objects(const std::string &text, char open_char, char close_char)
{
  std::vector<std::string> objects;
  bool in_string = false;
  bool escaped = false;
  int depth = 0;
  std::size_t object_start = std::string::npos;

  for(std::size_t i = 0; i < text.size(); ++i)
  {
    const char ch = text[i];

    if(escaped)
    {
      escaped = false;
      continue;
    }

    if(ch == '\\' && in_string)
    {
      escaped = true;
      continue;
    }

    if(ch == '"')
    {
      in_string = !in_string;
      continue;
    }

    if(in_string)
      continue;

    if(ch == open_char)
    {
      if(depth == 0)
        object_start = i;
      ++depth;
    }
    else if(ch == close_char)
    {
      if(depth == 0)
        continue;

      --depth;
      if(depth == 0 && object_start != std::string::npos)
      {
        objects.push_back(text.substr(object_start, i - object_start + 1));
        object_start = std::string::npos;
      }
    }
  }

  return objects;
}

bool find_json_field_value(
  const std::string &text,
  const std::string &field,
  std::size_t &value_start)
{
  const std::string quoted_field = "\"" + field + "\"";
  const auto field_pos = text.find(quoted_field);
  if(field_pos == std::string::npos)
    return false;

  const auto colon_pos = text.find(':', field_pos + quoted_field.size());
  if(colon_pos == std::string::npos)
    return false;

  value_start = text.find_first_not_of(" \t\r\n", colon_pos + 1);
  return value_start != std::string::npos;
}

bool extract_json_string_field(
  const std::string &text,
  const std::string &field,
  std::string &value)
{
  std::size_t value_start = 0;
  if(!find_json_field_value(text, field, value_start) || text[value_start] != '"')
    return false;

  value.clear();
  bool escaped = false;
  for(std::size_t i = value_start + 1; i < text.size(); ++i)
  {
    const char ch = text[i];
    if(escaped)
    {
      value.push_back(ch);
      escaped = false;
      continue;
    }

    if(ch == '\\')
    {
      escaped = true;
      continue;
    }

    if(ch == '"')
      return true;

    value.push_back(ch);
  }

  return false;
}

bool extract_json_array_field(
  const std::string &text,
  const std::string &field,
  std::string &value)
{
  std::size_t value_start = 0;
  if(!find_json_field_value(text, field, value_start) || text[value_start] != '[')
    return false;

  bool in_string = false;
  bool escaped = false;
  int depth = 0;
  for(std::size_t i = value_start; i < text.size(); ++i)
  {
    const char ch = text[i];

    if(escaped)
    {
      escaped = false;
      continue;
    }

    if(ch == '\\' && in_string)
    {
      escaped = true;
      continue;
    }

    if(ch == '"')
    {
      in_string = !in_string;
      continue;
    }

    if(in_string)
      continue;

    if(ch == '[')
      ++depth;
    else if(ch == ']')
    {
      --depth;
      if(depth == 0)
      {
        value = text.substr(value_start, i - value_start + 1);
        return true;
      }
    }
  }

  return false;
}

bool extract_json_object_field(
  const std::string &text,
  const std::string &field,
  std::string &value)
{
  std::size_t value_start = 0;
  if(!find_json_field_value(text, field, value_start) || text[value_start] != '{')
    return false;

  bool in_string = false;
  bool escaped = false;
  int depth = 0;
  for(std::size_t i = value_start; i < text.size(); ++i)
  {
    const char ch = text[i];

    if(escaped)
    {
      escaped = false;
      continue;
    }

    if(ch == '\\' && in_string)
    {
      escaped = true;
      continue;
    }

    if(ch == '"')
    {
      in_string = !in_string;
      continue;
    }

    if(in_string)
      continue;

    if(ch == '{')
      ++depth;
    else if(ch == '}')
    {
      --depth;
      if(depth == 0)
      {
        value = text.substr(value_start, i - value_start + 1);
        return true;
      }
    }
  }

  return false;
}

bool parse_string_list(
  const std::string &list_content,
  const std::string &field_name,
  std::vector<std::string> &values)
{
  values.clear();

  std::size_t index = 0;
  while(index < list_content.size())
  {
    index = list_content.find('"', index);
    if(index == std::string::npos)
      break;

    std::string value;
    bool escaped = false;
    bool closed = false;
    for(std::size_t i = index + 1; i < list_content.size(); ++i)
    {
      const char ch = list_content[i];
      if(escaped)
      {
        value.push_back(ch);
        escaped = false;
        continue;
      }

      if(ch == '\\')
      {
        escaped = true;
        continue;
      }

      if(ch == '"')
      {
        values.push_back(value);
        index = i + 1;
        closed = true;
        break;
      }

      value.push_back(ch);
    }

    if(!closed)
    {
      std::cerr << "error: unterminated string in array field \"" << field_name
                << "\"\n";
      return false;
    }
  }

  return true;
}

void normalize_string_list(std::vector<std::string> &values)
{
  for(auto &value : values)
    value = normalize_relative_path(value);
}

bool parse_line_number_list(
  const std::string &list_content,
  const std::string &name,
  const std::string &file,
  line_to_namest &line_to_names)
{
  const std::regex number_regex("[0-9]+");
  auto begin = std::sregex_iterator(
    list_content.begin(), list_content.end(), number_regex);
  const auto end = std::sregex_iterator();

  if(begin == end)
  {
    std::cerr << "error: line list must contain at least one line for "
              << name << " in file " << file << '\n';
    return false;
  }

  for(auto it = begin; it != end; ++it)
  {
    const std::size_t line_number =
      static_cast<std::size_t>(std::stoull((*it).str()));
    if(line_number == 0)
    {
      std::cerr << "error: line numbers are 1-based and must be > 0\n";
      return false;
    }

    auto &names = line_to_names[line_number];
    if(std::find(names.begin(), names.end(), name) == names.end())
      names.push_back(name);
  }

  return true;
}

bool parse_project_line_additions(
  const std::string &json_file,
  project_configt &project_config,
  const aib_ignoret &ignore)
{
  std::string json;
  if(!read_file(json_file, json))
  {
    std::cerr << "error: unable to open json file: " << json_file << '\n';
    return false;
  }

  std::string project_object;
  if(!extract_json_object_field(json, "project", project_object))
  {
    std::cerr << "error: expecting object field \"project\" in " << json_file
              << '\n';
    return false;
  }

  if(!extract_json_string_field(
       project_object, "project_root", project_config.project_root))
  {
    std::cerr << "error: project must include string field \"project_root\"\n";
    return false;
  }

  std::string interleaving_source_files_array;
  if(!extract_json_array_field(
       project_object,
       "interleaving_source_files",
       interleaving_source_files_array))
  {
    std::cerr << "error: project must include array field "
                 "\"interleaving_source_files\"\n";
    return false;
  }

  if(
    !parse_string_list(
      interleaving_source_files_array,
      "interleaving_source_files",
      project_config.interleaving_source_files))
  {
    return false;
  }
  normalize_string_list(project_config.interleaving_source_files);

  std::string translation_units_array;
  if(!extract_json_array_field(
       project_object, "translation_units", translation_units_array))
  {
    std::cerr << "error: project must include array field "
                 "\"translation_units\"\n";
    return false;
  }

  if(
    !parse_string_list(
      translation_units_array,
      "translation_units",
      project_config.translation_units))
  {
    return false;
  }
  normalize_string_list(project_config.translation_units);

  for(const auto &interleaving_source_file :
      project_config.interleaving_source_files)
  {
    if(is_ignored_path(ignore, interleaving_source_file))
    {
      std::cerr << "error: config references ignored interleaving source file: "
                << interleaving_source_file << '\n';
      return false;
    }
  }

  std::string interleaving_array;
  if(!extract_json_array_field(json, "interleaving", interleaving_array))
  {
    std::cerr << "error: expecting array field \"interleaving\" in "
              << json_file << '\n';
    return false;
  }

  const auto objects = extract_top_level_objects(interleaving_array, '{', '}');
  if(objects.empty())
  {
    std::cerr << "error: interleaving must contain at least one object in "
              << json_file << '\n';
    return false;
  }
  project_config.interleaving_array_json = interleaving_array;

  for(const auto &object_text : objects)
  {
    std::string name;
    if(!extract_json_string_field(object_text, "name", name))
    {
      std::cerr << "error: each object must include string field \"name\"\n";
      return false;
    }

    std::string file_entries_array;
    if(!extract_json_array_field(
         object_text, "line_added_block_with_file", file_entries_array))
    {
      std::cerr << "error: each object must include array field "
                   "\"line_added_block_with_file\"\n";
      return false;
    }

    const auto file_objects =
      extract_top_level_objects(file_entries_array, '{', '}');
    if(file_objects.empty())
    {
      std::cerr << "error: line_added_block_with_file must contain at least "
                   "one file entry for "
                << name << '\n';
      return false;
    }

    for(const auto &file_object : file_objects)
    {
      std::string file;
      if(!extract_json_string_field(file_object, "file", file))
      {
        std::cerr << "error: each file entry must include string field "
                     "\"file\"\n";
        return false;
      }

      std::string line_array;
      if(!extract_json_array_field(file_object, "line", line_array))
      {
        std::cerr << "error: each file entry must include array field "
                     "\"line\"\n";
        return false;
      }

      const std::string normalized_file = normalize_relative_path(file);
      if(is_ignored_path(ignore, normalized_file))
      {
        std::cerr << "error: config references ignored file: " << normalized_file
                  << '\n';
        return false;
      }

      if(!parse_line_number_list(
           line_array,
           name,
           normalized_file,
           project_config.file_to_lines[normalized_file]))
      {
        return false;
      }
    }
  }

  return true;
}

std::string call_suffix_for(const std::string &name, const std::string &content)
{
  const std::regex decl("\\b" + name + "\\s*\\(([^)]*)\\)\\s*(?:\\{|;)");

  std::smatch match;
  if(!std::regex_search(content, match, decl) || match.size() < 2)
    return "()";

  const std::string params = trim(match[1].str());
  if(params.empty() || params == "void")
    return "()";

  return "(0)";
}

std::string detect_call_suffix(
  const std::string &project_root,
  const std::string &name,
  const aib_ignoret &ignore)
{
  const auto project_root_path =
    std::filesystem::path(project_root).lexically_normal();

  auto it =
    std::filesystem::recursive_directory_iterator(project_root_path);
  const auto end = std::filesystem::recursive_directory_iterator();
  while(it != end)
  {
    const auto &entry = *it;
    const std::string relative_path =
      relative_project_path(entry.path(), project_root_path);

    if(is_ignored_path(ignore, relative_path))
    {
      if(entry.is_directory())
        it.disable_recursion_pending();
      ++it;
      continue;
    }

    if(!entry.is_regular_file())
    {
      ++it;
      continue;
    }

    const auto extension = entry.path().extension().generic_string();
    if(extension != ".c" && extension != ".h" && extension != ".i")
    {
      ++it;
      continue;
    }

    std::string content;
    if(!read_file(entry.path().string(), content))
    {
      ++it;
      continue;
    }

    const std::string suffix = call_suffix_for(name, content);
    if(suffix == "(0)")
      return suffix;

    if(suffix == "()")
    {
      const std::regex decl("\\b" + name + "\\s*\\(([^)]*)\\)\\s*(?:\\{|;)");
      if(std::regex_search(content, decl))
        return suffix;
    }

    ++it;
  }

  return "()";
}

std::string indentation_for(const std::string &line)
{
  const auto first_non_ws = line.find_first_not_of(" \t");
  if(first_non_ws == std::string::npos)
    return "";

  return line.substr(0, first_non_ws);
}

bool rewrite_source_file(
  const std::filesystem::path &input_file,
  const std::filesystem::path &output_file,
  const line_to_namest &line_to_names,
  const std::unordered_map<std::string, std::string> &name_to_suffix)
{
  std::ifstream source_stream(input_file);
  if(!source_stream)
  {
    std::cerr << "error: unable to open input source: " << input_file.string()
              << '\n';
    return false;
  }

  std::vector<std::string> lines;
  std::string line;
  while(std::getline(source_stream, line))
    lines.push_back(line);

  for(const auto &line_entry : line_to_names)
  {
    if(line_entry.first > lines.size())
    {
      std::cerr << "error: line " << line_entry.first << " is out of range in "
                << input_file.string() << '\n';
      return false;
    }
  }

  std::filesystem::create_directories(output_file.parent_path());
  std::ofstream out(output_file);
  if(!out)
  {
    std::cerr << "error: unable to open output source: " << output_file.string()
              << '\n';
    return false;
  }

  for(std::size_t i = 0; i < lines.size(); ++i)
  {
    const std::size_t line_number = i + 1;
    const auto it = line_to_names.find(line_number);

    if(it != line_to_names.end())
    {
      const std::string indent = indentation_for(lines[i]);
      for(const auto &name : it->second)
      {
        const auto suffix_it = name_to_suffix.find(name);
        const std::string suffix =
          suffix_it == name_to_suffix.end() ? "()" : suffix_it->second;
        out << indent << "if (nondet_bool()) " << name << suffix << ";\n";
      }
    }

    out << lines[i] << '\n';
  }

  return true;
}

bool copy_project_with_rewrites(
  const std::string &project_root,
  const std::string &output_root,
  const file_to_linet &file_to_lines,
  const aib_ignoret &ignore)
{
  const auto project_root_path =
    std::filesystem::path(project_root).lexically_normal();
  const auto output_root_path =
    std::filesystem::path(output_root).lexically_normal();

  if(std::filesystem::exists(output_root_path))
  {
    std::cerr << "error: output root already exists: "
              << output_root_path.string() << '\n';
    return false;
  }

  std::unordered_map<std::string, std::string> name_to_suffix;
  for(const auto &file_entry : file_to_lines)
  {
    for(const auto &line_entry : file_entry.second)
    {
      for(const auto &name : line_entry.second)
      {
        if(name_to_suffix.find(name) == name_to_suffix.end())
        {
          name_to_suffix.emplace(
            name, detect_call_suffix(project_root, name, ignore));
        }
      }
    }
  }

  for(const auto &file_entry : file_to_lines)
  {
    const auto source_path =
      (project_root_path / std::filesystem::path(file_entry.first))
        .lexically_normal();

    if(
      !std::filesystem::exists(source_path) ||
      !std::filesystem::is_regular_file(source_path))
    {
      std::cerr << "error: config references missing source file: "
                << source_path.string() << '\n';
      return false;
    }
  }

  std::filesystem::create_directories(output_root_path);
  for(const auto &entry : std::filesystem::directory_iterator(project_root_path))
  {
    const auto output_path = output_root_path / entry.path().filename();
    if(entry.is_directory())
    {
      std::filesystem::copy(
        entry.path(),
        output_path,
        std::filesystem::copy_options::recursive |
          std::filesystem::copy_options::overwrite_existing);
    }
    else if(entry.is_regular_file())
    {
      std::filesystem::copy_file(
        entry.path(),
        output_path,
        std::filesystem::copy_options::overwrite_existing);
    }
  }

  for(const auto &ignored_file : ignore.files)
  {
    std::error_code ec;
    std::filesystem::remove(
      output_root_path / std::filesystem::path(ignored_file), ec);
  }

  for(const auto &ignored_directory_prefix : ignore.directory_prefixes)
  {
    std::error_code ec;
    const std::string directory_name =
      ignored_directory_prefix.substr(0, ignored_directory_prefix.size() - 1);
    std::filesystem::remove_all(
      output_root_path / std::filesystem::path(directory_name), ec);
  }

  for(const auto &file_entry : file_to_lines)
  {
    const auto source_path =
      (project_root_path / std::filesystem::path(file_entry.first))
        .lexically_normal();
    const auto output_path =
      (output_root_path / std::filesystem::path(file_entry.first))
        .lexically_normal();

    if(!rewrite_source_file(
         source_path, output_path, file_entry.second, name_to_suffix))
    {
      return false;
    }
  }

  return true;
}

bool write_effective_manifest(
  const std::filesystem::path &output_manifest_path,
  const std::string &output_root,
  const project_configt &project_config,
  const aib_ignoret &ignore)
{
  std::vector<std::string> effective_translation_units;
  effective_translation_units.reserve(project_config.translation_units.size());

  for(const auto &translation_unit : project_config.translation_units)
  {
    if(is_ignored_path(ignore, translation_unit))
      continue;

    const auto output_path =
      (std::filesystem::path(output_root) / std::filesystem::path(translation_unit))
        .lexically_normal();
    if(!std::filesystem::exists(output_path) || !std::filesystem::is_regular_file(output_path))
    {
      std::cerr << "error: output manifest translation unit missing from output root: "
                << translation_unit << '\n';
      return false;
    }

    effective_translation_units.push_back(translation_unit);
  }

  std::vector<std::string> effective_interleaving_source_files;
  effective_interleaving_source_files.reserve(
    project_config.interleaving_source_files.size());

  for(const auto &interleaving_source_file :
      project_config.interleaving_source_files)
  {
    if(is_ignored_path(ignore, interleaving_source_file))
    {
      std::cerr << "error: output manifest interleaving source file was ignored: "
                << interleaving_source_file << '\n';
      return false;
    }

    const auto output_path =
      (std::filesystem::path(output_root) /
       std::filesystem::path(interleaving_source_file))
        .lexically_normal();
    if(!std::filesystem::exists(output_path) || !std::filesystem::is_regular_file(output_path))
    {
      std::cerr << "error: output manifest interleaving source file missing from output root: "
                << interleaving_source_file << '\n';
      return false;
    }

    effective_interleaving_source_files.push_back(interleaving_source_file);
  }

  std::filesystem::create_directories(output_manifest_path.parent_path());
  std::ofstream out(output_manifest_path);
  if(!out)
  {
    std::cerr << "error: unable to write output manifest: "
              << output_manifest_path.string() << '\n';
    return false;
  }

  out << "{\n";
  out << "  \"project\": {\n";
  out << "    \"project_root\": \""
      << json_escape(normalize_absolute_path(output_root)) << "\",\n";

  out << "    \"interleaving_source_files\": [";
  bool first_source = true;
  for(const auto &source_file : effective_interleaving_source_files)
  {
    if(!first_source)
      out << ", ";
    out << "\"" << json_escape(source_file) << "\"";
    first_source = false;
  }
  out << "],\n";

  out << "    \"translation_units\": [";
  bool first_translation_unit = true;
  for(const auto &translation_unit : effective_translation_units)
  {
    if(!first_translation_unit)
      out << ", ";
    out << "\"" << json_escape(translation_unit) << "\"";
    first_translation_unit = false;
  }
  out << "]\n";
  out << "  },\n";
  out << "  \"interleaving\": " << project_config.interleaving_array_json << "\n";
  out << "}\n";
  return true;
}
} // namespace

int main(int argc, char **argv)
{
  if(argc != 5)
  {
    std::cerr
      << "usage: aib <project_root> <input_config.json> <output_root> "
         "<output_config.json>\n";
    return 1;
  }

  const std::string project_root = argv[1];
  const std::string json_file = argv[2];
  const std::string output_root = argv[3];
  const std::string output_config_file = argv[4];
  const auto output_manifest_path =
    std::filesystem::path(output_config_file).lexically_normal();

  if(
    !std::filesystem::exists(project_root) ||
    !std::filesystem::is_directory(project_root))
  {
    std::cerr << "error: project root is not a directory: " << project_root
              << '\n';
    return 1;
  }

  if(
    !path_matches_or_is_within(output_manifest_path.string(), output_root) ||
    normalize_absolute_path(output_manifest_path.string()) ==
      normalize_absolute_path(output_root))
  {
    std::cerr << "error: output_config.json must be a file path inside "
                 "output_root: "
              << output_manifest_path.string() << '\n';
    return 1;
  }

  aib_ignoret ignore;
  if(!load_aibignore(project_root, ignore))
    return 1;

  project_configt project_config;
  if(!parse_project_line_additions(json_file, project_config, ignore))
    return 1;

  if(
    !project_config.project_root.empty() &&
    normalize_absolute_path(project_root) !=
      normalize_absolute_path(project_config.project_root))
  {
    std::cerr << "error: project root does not match config project_root: "
              << project_config.project_root << '\n';
    return 1;
  }

  if(
    !copy_project_with_rewrites(
      project_root, output_root, project_config.file_to_lines, ignore))
  {
    return 1;
  }

  if(
    !write_effective_manifest(
      output_manifest_path, output_root, project_config, ignore))
  {
    return 1;
  }

  return 0;
}
