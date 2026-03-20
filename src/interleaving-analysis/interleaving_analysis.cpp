#include "interleaving_analysis.h"

#include <pointer-analysis/value_set_analysis.h>

#include "rw_set.h"

#include <fstream>

namespace
{
using function_write_mapt = std::map<irep_idt, std::set<irep_idt>>;

function_write_mapt build_function_write_map(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::vector<std::string> &function_names,
  interleaving_resultt &result)
{
  namespacet ns(goto_model.symbol_table);
  value_set_analysist value_sets(ns);
  function_write_mapt function_write_map;

  messaget log(message_handler);
  log.status() << "[interleaving] collecting variables written by target "
                  "functions"
               << messaget::eom;

  for(const auto &interleaving_function_name : function_names)
  {
    const irep_idt function_id = interleaving_function_name;
    auto &function_result = result.functions[function_id];
    function_result.display_name = interleaving_function_name;

    const auto f_it =
      goto_model.goto_functions.function_map.find(function_id);

    if(f_it == goto_model.goto_functions.function_map.end())
    {
      log.warning() << "[interleaving] function not found: "
                    << interleaving_function_name << messaget::eom;
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
        if(id2string(variable_id).find('$') == std::string::npos)
        {
          function_write_map[function_id].insert(variable_id);
          function_result.written_variables.insert(variable_id);
        }
      }
    }
  }

  return function_write_map;
}

void record_candidate_lines(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::vector<std::string> &function_names,
  const function_write_mapt &function_write_map,
  interleaving_resultt &result)
{
  namespacet ns(goto_model.symbol_table);
  value_set_analysist value_sets(ns);
  std::set<irep_idt> interleaving_function_ids(
    function_names.begin(), function_names.end());

  messaget log(message_handler);
  log.status() << "[interleaving] scanning for candidate interleaving points"
               << messaget::eom;

  for(auto &func_pair : goto_model.goto_functions.function_map)
  {
    const irep_idt &func_name = func_pair.first;
    auto &func = func_pair.second;
    const std::string name_str = id2string(func_name);

    if(
      !func.body_available() || name_str.find("__CPROVER") == 0 ||
      interleaving_function_ids.count(func_name) != 0)
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
          if(!line_num.empty())
          {
            result.functions[interleaving_function_id].candidate_lines.insert(
              std::stoi(line_num));
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
  auto function_write_map = build_function_write_map(
    goto_model, message_handler, config.function_names, result);

  record_candidate_lines(
    goto_model,
    message_handler,
    config.function_names,
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

  json_file << "[\n";
  bool first_interleaving_function = true;
  for(const auto &function_name : config.function_names)
  {
    const irep_idt function_id = function_name;
    auto result_it = result.functions.find(function_id);

    if(!first_interleaving_function)
      json_file << ",\n";
    first_interleaving_function = false;

    json_file << "  {\n";
    json_file << "    \"name\": \"" << function_name << "\",\n";

    json_file << "    \"write_var\": [";
    bool first_var = true;
    if(result_it != result.functions.end())
    {
      for(const auto &var : result_it->second.written_variables)
      {
        if(!first_var)
          json_file << ", ";
        json_file << "\"" << id2string(var) << "\"";
        first_var = false;
      }
    }
    json_file << "],\n";

    json_file << "    \"line_added_block\": [";
    bool first_line = true;
    if(result_it != result.functions.end())
    {
      for(const int line : result_it->second.candidate_lines)
      {
        if(!first_line)
          json_file << ", ";
        json_file << line;
        first_line = false;
      }
    }
    json_file << "]\n";
    json_file << "  }";
  }
  json_file << "\n]\n";
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
