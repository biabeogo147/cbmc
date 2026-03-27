#include "interleaving_analysis.h"

#include <pointer-analysis/value_set_analysis.h>

#include "rw_set.h"

#include <util/namespace.h>
#include <util/symbol.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace
{
using function_write_mapt = std::map<irep_idt, std::set<irep_idt>>;
using normalized_pathst = std::set<std::string>;

std::string normalize_path(const std::string &path)
{
  return std::filesystem::absolute(std::filesystem::path(path))
    .lexically_normal()
    .generic_string();
}

bool is_c_source_file(const std::string &path)
{
  return std::filesystem::path(path).extension() == ".c";
}

normalized_pathst normalize_paths(const std::vector<std::string> &paths)
{
  normalized_pathst result;
  for(const auto &path : paths)
  {
    if(!path.empty())
      result.insert(normalize_path(path));
  }
  return result;
}

bool path_matches_or_is_within(
  const std::string &candidate_path,
  const std::string &root_path)
{
  if(root_path.empty())
    return true;

  const std::string normalized_candidate = normalize_path(candidate_path);
  const std::string normalized_root = normalize_path(root_path);

  if(normalized_candidate == normalized_root)
    return true;

  if(normalized_candidate.size() <= normalized_root.size())
    return false;

  return
    normalized_candidate.compare(0, normalized_root.size(), normalized_root) ==
      0 &&
    normalized_candidate[normalized_root.size()] == '/';
}

std::string relative_report_path(
  const std::string &path,
  const std::string &project_root_path)
{
  const auto normalized_path =
    std::filesystem::path(normalize_path(path)).lexically_normal();

  if(project_root_path.empty())
    return normalized_path.generic_string();

  const auto normalized_root =
    std::filesystem::path(normalize_path(project_root_path)).lexically_normal();
  const auto relative_path = normalized_path.lexically_relative(normalized_root);

  if(relative_path.empty())
    return normalized_path.generic_string();

  return relative_path.generic_string();
}

std::vector<std::string> relative_report_paths(
  const std::vector<std::string> &paths,
  const std::string &project_root_path)
{
  std::vector<std::string> result;
  result.reserve(paths.size());

  for(const auto &path : paths)
    result.push_back(relative_report_path(path, project_root_path));

  std::sort(result.begin(), result.end());
  return result;
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

std::string function_source_file(
  const goto_modelt &goto_model,
  const irep_idt &function_id,
  const goto_functiont &function)
{
  if(const symbolt *function_symbol = goto_model.symbol_table.lookup(function_id))
  {
    const auto &symbol_file = function_symbol->location.get_file();
    if(!symbol_file.empty())
      return id2string(symbol_file);
  }

  for(const auto &instruction : function.body.instructions)
  {
    const auto &instruction_file = instruction.source_location().get_file();
    if(!instruction_file.empty())
      return id2string(instruction_file);
  }

  return "";
}

std::vector<std::string> collect_translation_units_from_goto_model(
  const goto_modelt &goto_model,
  const std::string &project_root_path)
{
  std::set<std::string> translation_units;

  for(const auto &function_entry : goto_model.goto_functions.function_map)
  {
    const auto &function_id = function_entry.first;
    const auto &function = function_entry.second;

    if(!function.body_available())
      continue;

    const std::string source_file =
      function_source_file(goto_model, function_id, function);
    if(source_file.empty() || !is_c_source_file(source_file))
      continue;

    if(
      !project_root_path.empty() &&
      !path_matches_or_is_within(source_file, project_root_path))
    {
      continue;
    }

    translation_units.insert(normalize_path(source_file));
  }

  return std::vector<std::string>(
    translation_units.begin(), translation_units.end());
}

std::vector<irep_idt> resolve_target_function_ids(
  const goto_modelt &goto_model,
  message_handlert &message_handler,
  const interleaving_configt &config)
{
  std::vector<irep_idt> target_functions;
  std::set<irep_idt> seen_functions;
  normalized_pathst interleaving_source_files =
    normalize_paths(config.interleaving_source_files);

  if(interleaving_source_files.empty())
    return target_functions;

  messaget log(message_handler);
  log.status() << "[interleaving] discovering target functions from source files"
               << messaget::eom;

  for(const auto &function_entry : goto_model.goto_functions.function_map)
  {
    const irep_idt &function_id = function_entry.first;
    const auto &function = function_entry.second;

    if(!function.body_available())
      continue;

    const std::string source_file =
      function_source_file(goto_model, function_id, function);
    if(source_file.empty())
      continue;

    if(interleaving_source_files.count(normalize_path(source_file)) != 0)
    {
      if(seen_functions.insert(function_id).second)
        target_functions.push_back(function_id);
    }
  }

  std::sort(target_functions.begin(), target_functions.end());
  return target_functions;
}

bool is_global_written_symbol(
  const namespacet &ns,
  const irep_idt &identifier)
{
  const symbolt *symbol = nullptr;
  if(ns.lookup(identifier, symbol))
    return false;

  return
    symbol->is_static_lifetime && symbol->location.get_function().empty() &&
    !symbol->is_type && !symbol->is_auxiliary && symbol->type.id() != ID_code;
}

bool should_skip_candidate_function(
  const goto_modelt &goto_model,
  const irep_idt &function_id,
  const goto_functiont &function,
  const std::set<irep_idt> &interleaving_function_ids,
  const normalized_pathst &interleaving_source_files)
{
  const std::string function_name = id2string(function_id);
  if(
    !function.body_available() || function_name.find("__CPROVER") == 0 ||
    interleaving_function_ids.count(function_id) != 0)
  {
    return true;
  }

  if(interleaving_source_files.empty())
    return false;

  const std::string source_file =
    function_source_file(goto_model, function_id, function);
  return
    !source_file.empty() &&
    interleaving_source_files.count(normalize_path(source_file)) != 0;
}

bool should_record_candidate_location(
  const std::string &source_file,
  const interleaving_configt &config)
{
  if(source_file.empty())
    return false;

  if(!config.project_root_path.empty())
  {
    return
      is_c_source_file(source_file) &&
      path_matches_or_is_within(source_file, config.project_root_path);
  }

  return true;
}

function_write_mapt build_function_write_map(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::vector<irep_idt> &function_ids,
  interleaving_resultt &result)
{
  namespacet ns(goto_model.symbol_table);
  value_set_analysist value_sets(ns);
  function_write_mapt function_write_map;

  messaget log(message_handler);
  log.status() << "[interleaving] collecting variables written by target "
                  "functions"
               << messaget::eom;

  for(const auto &function_id : function_ids)
  {
    auto &function_result = result.functions[function_id];
    function_result.display_name = id2string(function_id);

    const auto f_it =
      goto_model.goto_functions.function_map.find(function_id);

    if(f_it == goto_model.goto_functions.function_map.end())
    {
      log.warning() << "[interleaving] function not found: "
                    << id2string(function_id) << messaget::eom;
      continue;
    }

    for(auto instruction = f_it->second.body.instructions.begin();
        instruction != f_it->second.body.instructions.end();
        ++instruction)
    {
      rw_set_loct rw_set(
        ns, value_sets, function_id, instruction, message_handler);
      for(const auto &entry : rw_set.w_entries)
      {
        const irep_idt &variable_id = entry.first;
        if(is_global_written_symbol(ns, variable_id))
        {
          function_write_map[function_id].insert(variable_id);
          function_result.written_global_variables.insert(variable_id);
        }
      }
    }
  }

  return function_write_map;
}

void record_candidate_lines(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const interleaving_configt &config,
  const std::vector<irep_idt> &function_ids,
  const function_write_mapt &function_write_map,
  interleaving_resultt &result)
{
  namespacet ns(goto_model.symbol_table);
  value_set_analysist value_sets(ns);
  std::set<irep_idt> interleaving_function_ids(
    function_ids.begin(), function_ids.end());
  normalized_pathst interleaving_source_files =
    normalize_paths(config.interleaving_source_files);

  messaget log(message_handler);
  log.status() << "[interleaving] scanning for candidate interleaving points"
               << messaget::eom;

  for(auto &func_pair : goto_model.goto_functions.function_map)
  {
    const irep_idt &func_name = func_pair.first;
    auto &func = func_pair.second;

    if(should_skip_candidate_function(
         goto_model,
         func_name,
         func,
         interleaving_function_ids,
         interleaving_source_files))
    {
      continue;
    }

    for(auto instruction = func.body.instructions.begin();
        instruction != func.body.instructions.end();
        ++instruction)
    {
      rw_set_loct rw_set(
        ns, value_sets, func_name, instruction, message_handler);

      for(const auto &map_pair : function_write_map)
      {
        const irep_idt &interleaving_function_id = map_pair.first;
        const auto &modified_vars = map_pair.second;
        bool conflict = false;

        for(const auto &entry : rw_set.r_entries)
        {
          if(modified_vars.count(entry.first) != 0)
          {
            conflict = true;
            break;
          }
        }

        if(!conflict)
        {
          for(const auto &entry : rw_set.w_entries)
          {
            if(modified_vars.count(entry.first) != 0)
            {
              conflict = true;
              break;
            }
          }
        }

        if(conflict)
        {
          const std::string line_num =
            id2string(instruction->source_location().get_line());
          const std::string source_file =
            id2string(instruction->source_location().get_file());

          if(!line_num.empty() && should_record_candidate_location(source_file, config))
          {
            const int line_number = std::stoi(line_num);
            auto &function_result = result.functions[interleaving_function_id];
            function_result
              .candidate_lines_by_file[relative_report_path(
                source_file, config.project_root_path)]
              .insert(line_number);
          }
        }
      }
    }
  }
}
} // namespace

interleaving_resultt analyze_interleavings(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const interleaving_configt &config)
{
  interleaving_resultt result;
  result.project.project_root = config.project_root_path;
  result.project.interleaving_source_files = relative_report_paths(
    config.interleaving_source_files, config.project_root_path);
  const auto &translation_units =
    config.translation_units.empty()
      ? collect_translation_units_from_goto_model(
          goto_model, config.project_root_path)
      : config.translation_units;
  result.project.translation_units =
    relative_report_paths(translation_units, config.project_root_path);

  const auto target_function_ids =
    resolve_target_function_ids(goto_model, message_handler, config);
  result.function_order = target_function_ids;

  if(
    target_function_ids.empty() &&
    !config.interleaving_source_files.empty())
  {
    messaget log(message_handler);
    log.warning()
      << "[interleaving] no interleaving functions were found in the current "
         "goto model for the requested source files; the emitted manifest will "
         "only reflect the effective build inputs"
      << messaget::eom;
  }

  auto function_write_map = build_function_write_map(
    goto_model, message_handler, target_function_ids, result);

  record_candidate_lines(
    goto_model,
    message_handler,
    config,
    target_function_ids,
    function_write_map,
    result);

  return result;
}

bool write_interleaving_report(
  const interleaving_resultt &result,
  const interleaving_configt &config,
  message_handlert &message_handler)
{
  std::ofstream json_file(config.json_output_path);
  if(!json_file.is_open())
  {
    messaget log(message_handler);
    log.error() << "[interleaving] failed to create JSON file: "
                << config.json_output_path << messaget::eom;
    return true;
  }

  json_file << "{\n";
  json_file << "  \"project\": {\n";
  json_file << "    \"project_root\": \""
            << json_escape(result.project.project_root) << "\",\n";

  json_file << "    \"interleaving_source_files\": [";
  bool first_interleaving_source_file = true;
  for(const auto &source_file : result.project.interleaving_source_files)
  {
    if(!first_interleaving_source_file)
      json_file << ", ";
    json_file << "\"" << json_escape(source_file) << "\"";
    first_interleaving_source_file = false;
  }
  json_file << "],\n";

  json_file << "    \"translation_units\": [";
  bool first_translation_unit = true;
  for(const auto &translation_unit : result.project.translation_units)
  {
    if(!first_translation_unit)
      json_file << ", ";
    json_file << "\"" << json_escape(translation_unit) << "\"";
    first_translation_unit = false;
  }
  json_file << "]\n";
  json_file << "  },\n";

  json_file << "  \"interleaving\": [\n";
  bool first_interleaving_function = true;
  for(const auto &function_id : result.function_order)
  {
    auto result_it = result.functions.find(function_id);

    if(!first_interleaving_function)
      json_file << ",\n";
    first_interleaving_function = false;

    json_file << "  {\n";
    json_file << "    \"name\": \"" << json_escape(id2string(function_id))
              << "\",\n";

    json_file << "    \"write_global_var\": [";
    bool first_var = true;
    if(result_it != result.functions.end())
    {
      for(const auto &var : result_it->second.written_global_variables)
      {
        if(!first_var)
          json_file << ", ";
        json_file << "\"" << json_escape(id2string(var)) << "\"";
        first_var = false;
      }
    }
    json_file << "],\n";

    json_file << "    \"line_added_block_with_file\": [";
    bool first_file = true;
    if(result_it != result.functions.end())
    {
      for(const auto &file_entry : result_it->second.candidate_lines_by_file)
      {
        if(!first_file)
          json_file << ", ";

        json_file << "{ \"file\": \"" << json_escape(file_entry.first)
                  << "\", \"line\": [";
        bool first_line = true;
        for(const int line : file_entry.second)
        {
          if(!first_line)
            json_file << ", ";
          json_file << line;
          first_line = false;
        }
        json_file << "] }";
        first_file = false;
      }
    }
    json_file << "]\n";
    json_file << "  }";
  }
  json_file << "\n  ]\n";
  json_file << "}\n";
  json_file.close();

  messaget log(message_handler);
  log.status() << "[interleaving] saved metadata to "
               << config.json_output_path << messaget::eom;
  return false;
}

interleaving_resultt run_interleaving_analysis(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const interleaving_configt &config)
{
  interleaving_resultt result =
    analyze_interleavings(goto_model, message_handler, config);

  if(config.mode == interleaving_modet::analysis_and_instrument)
  {
    messaget log(message_handler);
    log.status() << "[interleaving] instrumentation mode is reserved for a "
                    "future implementation; reporting candidates only"
                 << messaget::eom;
  }

  write_interleaving_report(result, config, message_handler);
  return result;
}
