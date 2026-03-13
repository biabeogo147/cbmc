/// \file
/// Command-line tool for adding nondeterministic interleaving call blocks.

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace
{
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

std::string
call_suffix_for(const std::string &name, const std::string &source_content)
{
  const std::regex decl("\\b" + name + "\\s*\\(([^)]*)\\)\\s*(?:\\{|;)");

  std::smatch match;
  if(!std::regex_search(source_content, match, decl) || match.size() < 2)
    return "()";

  const std::string params = trim(match[1].str());
  if(params.empty() || params == "void")
    return "()";

  return "(0)";
}

bool parse_line_number_list(
  const std::string &list_content,
  const std::string &name,
  std::map<std::size_t, std::vector<std::string>> &line_to_names)
{
  const std::regex number_regex("[0-9]+");
  auto begin = std::sregex_iterator(
    list_content.begin(), list_content.end(), number_regex);
  const auto end = std::sregex_iterator();

  if(begin == end)
  {
    std::cerr << "error: line_added_block must contain at least one line for "
              << name << '\n';
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

    line_to_names[line_number].push_back(name);
  }

  return true;
}

bool parse_line_additions(
  const std::string &json_file,
  std::map<std::size_t, std::vector<std::string>> &line_to_names)
{
  std::string json;
  if(!read_file(json_file, json))
  {
    std::cerr << "error: unable to open json file: " << json_file << '\n';
    return false;
  }

  const std::regex object_regex("\\{[^{}]*\\}");
  auto begin = std::sregex_iterator(json.begin(), json.end(), object_regex);
  const auto end = std::sregex_iterator();

  if(begin == end)
  {
    std::cerr << "error: expecting json array of objects in " << json_file
              << '\n';
    return false;
  }

  for(auto it = begin; it != end; ++it)
  {
    const std::string object_text = (*it).str();

    const std::regex name_regex("\"name\"\\s*:\\s*\"([^\"]+)\"");
    std::smatch name_match;
    if(
      !std::regex_search(object_text, name_match, name_regex) ||
      name_match.size() < 2)
    {
      std::cerr << "error: each object must include string field \"name\"\n";
      return false;
    }

    const std::string name = name_match[1].str();

    const std::regex line_block_regex(
      "\"line_added_block\"\\s*:\\s*\\[([^\\]]*)\\]");
    std::smatch line_block_match;
    if(
      !std::regex_search(object_text, line_block_match, line_block_regex) ||
      line_block_match.size() < 2)
    {
      std::cerr << "error: each object must include array field "
                   "\"line_added_block\"\n";
      return false;
    }

    if(!parse_line_number_list(line_block_match[1].str(), name, line_to_names))
      return false;
  }

  return true;
}

std::string indentation_for(const std::string &line)
{
  const auto first_non_ws = line.find_first_not_of(" \t");
  if(first_non_ws == std::string::npos)
    return "";

  return line.substr(0, first_non_ws);
}
} // namespace

int main(int argc, char **argv)
{
  if(argc != 4)
  {
    std::cerr << "usage: aib <input.c> <config.json> <output.c>\n";
    return 1;
  }

  const std::string input_file = argv[1];
  const std::string json_file = argv[2];
  const std::string output_file = argv[3];

  std::ifstream source_stream(input_file);
  if(!source_stream)
  {
    std::cerr << "error: unable to open input source: " << input_file << '\n';
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;
  while(std::getline(source_stream, line))
    lines.push_back(line);

  std::ostringstream source_joined;
  for(const auto &l : lines)
    source_joined << l << '\n';

  std::map<std::size_t, std::vector<std::string>> line_to_names;
  if(!parse_line_additions(json_file, line_to_names))
    return 1;

  std::unordered_map<std::string, std::string> name_to_suffix;
  for(const auto &line_and_names : line_to_names)
  {
    for(const auto &name : line_and_names.second)
    {
      if(name_to_suffix.find(name) == name_to_suffix.end())
      {
        name_to_suffix.emplace(
          name, call_suffix_for(name, source_joined.str()));
      }
    }
  }

  std::ofstream out(output_file);
  if(!out)
  {
    std::cerr << "error: unable to open output source: " << output_file << '\n';
    return 1;
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
        out << indent << "if (nondet_bool()) " << name << name_to_suffix[name]
            << ";\n";
      }
    }

    out << lines[i] << '\n';
  }

  return 0;
}
