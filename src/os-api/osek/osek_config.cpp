#include "osek_config.h"

#include <util/exception_utils.h>

#include <cstdint>
#include <fstream>
#include <optional>
#include <regex>
#include <string>

namespace os_api
{
namespace osek
{

namespace
{

std::string trim(const std::string &text)
{
  const auto begin = text.find_first_not_of(" \t\r\n");
  if(begin == std::string::npos)
    return "";

  const auto end = text.find_last_not_of(" \t\r\n");
  return text.substr(begin, end - begin + 1);
}

std::string strip_line_comment(const std::string &text)
{
  const auto comment_pos = text.find("//");
  if(comment_pos == std::string::npos)
    return text;
  return text.substr(0, comment_pos);
}

std::uint64_t parse_event_mask(
  const std::string &token,
  const std::string &path,
  const std::size_t line_number)
{
  try
  {
    return std::stoull(token, nullptr, 0);
  }
  catch(const std::exception &)
  {
    throw invalid_command_line_argument_exceptiont(
      "invalid EVENT_MASK value '" + token + "' at line " +
        std::to_string(line_number) + " in '" + path + "'",
      "--osek-oil");
  }
}

} // namespace

osek_configt osek_configt::from_oil_file(const std::string &path)
{
  std::ifstream input(path);
  if(!input)
  {
    throw invalid_command_line_argument_exceptiont(
      "failed to open OIL configuration file '" + path + "'",
      "--osek-oil");
  }

  const std::regex task_start_regex(R"(^TASK\s+([A-Za-z_][A-Za-z0-9_]*)\s*\{$)");
  const std::regex priority_regex(R"(^PRIORITY\s*=\s*([0-9]+)\s*;$)");
  const std::regex schedule_regex(R"(^SCHEDULE\s*=\s*(FULL|NON)\s*;$)");
  const std::regex task_type_regex(R"(^TYPE\s*=\s*(BASIC|EXTENDED)\s*;$)");
  const std::regex event_mask_regex(
    R"(^EVENT_MASK\s*=\s*(0[xX][0-9A-Fa-f]+|[0-9]+)\s*;$)");
  const std::regex autostart_regex(R"(^AUTOSTART\s*=\s*(TRUE|FALSE)\s*;$)");
  const std::regex task_end_regex(R"(^\}\s*;$)");

  struct partial_taskt
  {
    task_configurationt task;
    bool saw_priority = false;
    bool saw_schedule = false;
  };

  osek_configt configuration;
  std::optional<partial_taskt> current_task;
  std::size_t next_task_id = 1;
  std::string raw_line;
  std::size_t line_number = 0;

  while(std::getline(input, raw_line))
  {
    ++line_number;
    const std::string line = trim(strip_line_comment(raw_line));
    if(line.empty())
      continue;

    std::smatch match;

    if(!current_task.has_value())
    {
      if(std::regex_match(line, match, task_start_regex))
      {
        partial_taskt partial;
        partial.task.task_id = next_task_id++;
        partial.task.task_name = match[1].str();
        partial.task.function_identifier = partial.task.task_name;
        current_task = partial;
      }

      continue;
    }

    if(std::regex_match(line, match, priority_regex))
    {
      current_task->task.priority = std::stoi(match[1].str());
      current_task->saw_priority = true;
      continue;
    }

    if(std::regex_match(line, match, schedule_regex))
    {
      current_task->task.schedule =
        match[1].str() == "NON" ? schedule_typet::NON : schedule_typet::FULL;
      current_task->saw_schedule = true;
      continue;
    }

    if(std::regex_match(line, match, task_type_regex))
    {
      current_task->task.task_type =
        match[1].str() == "EXTENDED" ? task_typet::EXTENDED : task_typet::BASIC;
      continue;
    }

    if(std::regex_match(line, match, event_mask_regex))
    {
      current_task->task.event_mask =
        parse_event_mask(match[1].str(), path, line_number);
      continue;
    }

    if(std::regex_match(line, match, autostart_regex))
    {
      current_task->task.autostart = match[1].str() == "TRUE";
      continue;
    }

    if(std::regex_match(line, task_end_regex))
    {
      if(!current_task->saw_priority)
      {
        throw invalid_command_line_argument_exceptiont(
          "missing PRIORITY for task '" +
            id2string(current_task->task.task_name) + "' in '" + path + "'",
          "--osek-oil");
      }

      if(!current_task->saw_schedule)
      {
        throw invalid_command_line_argument_exceptiont(
          "missing SCHEDULE for task '" +
            id2string(current_task->task.task_name) + "' in '" + path + "'",
          "--osek-oil");
      }

      configuration.add_task(current_task->task);
      current_task.reset();
      continue;
    }
  }

  if(current_task.has_value())
  {
    throw invalid_command_line_argument_exceptiont(
      "unterminated TASK block in '" + path + "'",
      "--osek-oil");
  }

  return configuration;
}

bool osek_configt::empty() const
{
  return tasks.empty();
}

const std::vector<task_configurationt> &osek_configt::get_tasks() const
{
  return tasks;
}

const task_configurationt *
osek_configt::find_task_by_id(const std::size_t task_id) const
{
  const auto it = task_index_by_id.find(task_id);
  if(it == task_index_by_id.end())
    return nullptr;
  return &tasks[it->second];
}

const task_configurationt *
osek_configt::find_task_by_function(const irep_idt &identifier) const
{
  const auto it = task_index_by_function.find(identifier);
  if(it == task_index_by_function.end())
    return nullptr;
  return &tasks[it->second];
}

void osek_configt::add_task(const task_configurationt &task)
{
  const std::size_t index = tasks.size();
  tasks.push_back(task);
  task_index_by_id.emplace(task.task_id, index);
  task_index_by_function.emplace(task.function_identifier, index);
}

} // namespace osek
} // namespace os_api
