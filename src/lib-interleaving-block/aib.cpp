/// \file
/// Command-line tool for adding nondeterministic interleaving call blocks
/// across an entire project tree.

#include <filesystem>
#include <fstream>
#include <iostream>
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
  file_to_linet &file_to_lines)
{
  std::string json;
  if(!read_file(json_file, json))
  {
    std::cerr << "error: unable to open json file: " << json_file << '\n';
    return false;
  }

  const auto objects = extract_top_level_objects(json, '{', '}');
  if(objects.empty())
  {
    std::cerr << "error: expecting json array of objects in " << json_file
              << '\n';
    return false;
  }

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
      if(!parse_line_number_list(
           line_array, name, normalized_file, file_to_lines[normalized_file]))
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
  const std::string &name)
{
  for(const auto &entry :
      std::filesystem::recursive_directory_iterator(project_root))
  {
    if(!entry.is_regular_file())
      continue;

    const auto extension = entry.path().extension().generic_string();
    if(extension != ".c" && extension != ".h" && extension != ".i")
      continue;

    std::string content;
    if(!read_file(entry.path().string(), content))
      continue;

    const std::string suffix = call_suffix_for(name, content);
    if(suffix == "(0)")
      return suffix;

    if(suffix == "()")
    {
      const std::regex decl("\\b" + name + "\\s*\\(([^)]*)\\)\\s*(?:\\{|;)");
      if(std::regex_search(content, decl))
        return suffix;
    }
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
  const file_to_linet &file_to_lines)
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
          name_to_suffix.emplace(name, detect_call_suffix(project_root, name));
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
  for(const auto &entry :
      std::filesystem::recursive_directory_iterator(project_root_path))
  {
    const auto relative_path =
      std::filesystem::relative(entry.path(), project_root_path)
        .lexically_normal()
        .generic_string();
    const auto output_path = output_root_path / relative_path;

    if(entry.is_directory())
    {
      std::filesystem::create_directories(output_path);
      continue;
    }

    if(!entry.is_regular_file())
      continue;

    const auto rewrite_it = file_to_lines.find(relative_path);
    if(rewrite_it != file_to_lines.end())
    {
      if(!rewrite_source_file(
           entry.path(), output_path, rewrite_it->second, name_to_suffix))
      {
        return false;
      }
    }
    else
    {
      std::filesystem::create_directories(output_path.parent_path());
      std::filesystem::copy_file(
        entry.path(),
        output_path,
        std::filesystem::copy_options::overwrite_existing);
    }
  }

  return true;
}
} // namespace

int main(int argc, char **argv)
{
  if(argc != 4)
  {
    std::cerr << "usage: aib <project_root> <config.json> <output_root>\n";
    return 1;
  }

  const std::string project_root = argv[1];
  const std::string json_file = argv[2];
  const std::string output_root = argv[3];

  if(
    !std::filesystem::exists(project_root) ||
    !std::filesystem::is_directory(project_root))
  {
    std::cerr << "error: project root is not a directory: " << project_root
              << '\n';
    return 1;
  }

  file_to_linet file_to_lines;
  if(!parse_project_line_additions(json_file, file_to_lines))
    return 1;

  if(!copy_project_with_rewrites(project_root, output_root, file_to_lines))
    return 1;

  return 0;
}
