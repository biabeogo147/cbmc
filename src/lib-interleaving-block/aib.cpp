/// \file
/// Command-line tool for adding nondeterministic interleaving call blocks.

#include <util/message.h>

#include <json/json_parser.h>

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
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

bool parse_line_additions(
  const std::string &json_file,
  std::map<std::size_t, std::vector<std::string>> &line_to_names)
{
  ui_message_handlert message_handler;
  jsont json;

  if(parse_json(json_file, message_handler, json))
  {
    std::cerr << "error: unable to parse json file: " << json_file << '\n';
    return false;
  }

  if(!json.is_array())
  {
    std::cerr << "error: expected top-level JSON array in: " << json_file
              << '\n';
    return false;
  }

  for(const auto &entry : to_json_array(json))
  {
    if(!entry.is_object())
    {
      std::cerr << "error: each json entry must be an object\n";
      return false;
    }

    const std::string name = entry["name"].value;
    const auto &line_blocks = entry["line_added_block"];

    if(name.empty() || !line_blocks.is_array())
    {
      std::cerr << "error: each entry must have name and line_added_block[]\n";
      return false;
    }

    for(const auto &line : to_json_array(line_blocks))
    {
      if(!line.is_number())
      {
        std::cerr << "error: line_added_block values must be numbers\n";
        return false;
      }

      const auto line_number = static_cast<std::size_t>(line.value);
      if(line_number == 0)
      {
        std::cerr << "error: line numbers are 1-based and must be > 0\n";
        return false;
      }

      line_to_names[line_number].push_back(name);
    }
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
