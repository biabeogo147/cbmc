#include "read_written_variable_checking.h"

#include <util/std_code.h>

#include <pointer-analysis/value_set_analysis.h>

#include "rw_set.h"

#include <fstream>
#include <iostream>
#include <map>
#include <set>

void show_read_written_variables(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::vector<std::string> &function_name,
  const std::string &json_output_path)
{
  namespacet ns(goto_model.symbol_table);
  value_set_analysist value_sets(ns);

  // --- Storage for JSON output ---
  // Store variables touched by each function (set deduplicates entries).
  std::map<std::string, std::set<std::string>> json_write_vars;
  // Store line numbers where ISR calls are added (sorted + unique).
  std::map<std::string, std::set<int>> json_added_lines;

  // Map: function name -> variables written by that function.
  std::map<irep_idt, std::set<irep_idt>> function_write_map;

  std::cout << "\n[POR] --- STEP 1: BUILD WRITE-VARIABLE MAP FROM FUNCTIONS ---\n";
  for(const auto &interleaving_function_name : function_name)
  {
    const irep_idt target_interleaving_function = interleaving_function_name;
    const auto f_it = goto_model.goto_functions.function_map.find(target_interleaving_function);

    if(f_it == goto_model.goto_functions.function_map.end())
    {
      std::cout << " [Warning] Function not found: " << interleaving_function_name << "\n";
      continue;
    }

    std::cout << "Analyzing function: " << interleaving_function_name << "\n";
    for(auto it = f_it->second.body.instructions.begin();
        it != f_it->second.body.instructions.end();
        ++it)
    {
      rw_set_loct rw_set(ns, value_sets, target_interleaving_function, it, message_handler);
      for(const auto &entry : rw_set.w_entries)
      {
        std::string var_name = id2string(entry.first);
        if(var_name.find('$') == std::string::npos)
        {
          function_write_map[target_interleaving_function].insert(entry.first);
          json_write_vars[interleaving_function_name].insert(var_name); // Save to JSON data structures
          std::cout << " -> Writes variable: " << var_name << "\n";
        }
      }
    }
  }

  std::cout << "\n[POR] --- STEPS 2 & 3: SCAN MAIN FLOW AND ADD INTERRUPTS ---\n";

  for(auto &func_pair : goto_model.goto_functions.function_map)
  {
    const irep_idt func_name = func_pair.first;
    auto &func = func_pair.second;
    const std::string name_str = id2string(func_name);

    // Skip internal functions and the ISR functions themselves.
    bool is_an_interleaving_function = false;
    for(const auto &interleaving_function : function_name)
    {
      if(name_str == interleaving_function)
      {
        is_an_interleaving_function = true;
      }
    }

    if(!func.body_available() || name_str.find("__CPROVER") == 0 || is_an_interleaving_function)
    {
      continue;
    }

    std::cout << "Scanning function: " << name_str << "\n";

    // Use a basic iterator to keep insertion logic explicit.
    for(auto it = func.body.instructions.begin();
        it != func.body.instructions.end();)
    {
      rw_set_loct rw_set(ns, value_sets, func_name, it, message_handler);
      std::vector<irep_idt> interleaving_functions_to_inject; // ISR functions to inject before this instruction.

      // Check whether this instruction touches any ISR-written variable.
      for(const auto &map_pair : function_write_map)
      {
        const irep_idt current_interleaving_function = map_pair.first;
        const auto &modified_vars = map_pair.second;
        bool conflict = false;

        for(const auto &entry : rw_set.r_entries)
        {
          if(modified_vars.count(entry.first))
          {
            conflict = true;
          }
        }

        for(const auto &entry : rw_set.w_entries)
        {
          if(modified_vars.count(entry.first))
          {
            conflict = true;
          }
        }

        if(conflict)
        {
          interleaving_functions_to_inject.push_back(current_interleaving_function);
        }
      }

      // PERFORM INSTRUMENTATION
      if(!interleaving_functions_to_inject.empty())
      {
        const std::string line_num = id2string(it->source_location().get_line());

        for(const auto &interleaving_function_to_call : interleaving_functions_to_inject)
        {
          std::string interleaving_function_str = id2string(interleaving_function_to_call);

          std::cout << " -> Inject call to " << id2string(interleaving_function_to_call)
                    << " before line " << line_num << "\n";
          json_added_lines[interleaving_function_str].insert(std::stoi(line_num)); // Save to JSON data structures.

          const symbolt *interleaving_function_sym = nullptr;
          if(ns.lookup(interleaving_function_to_call, interleaving_function_sym))
          {
            std::cout << " [Warning] Function symbol not found: "
                      << id2string(interleaving_function_to_call) << "\n";
          }
        }
      }

      // Move to the next original instruction.
      ++it;
    }

    // Refresh jump targets after structural changes in the function body.
    func.body.update();
  }

  // --- STEP 4: WRITE JSON FILE ---
  std::ofstream json_file(json_output_path);
  if(json_file.is_open())
  {
    json_file << "[\n";
    bool first_interleaving_function = true;
    for(const auto &interleaving_function_name : function_name)
    {
      if(!first_interleaving_function)
        json_file << ",\n";
      first_interleaving_function = false;

      json_file << "  {\n";
      json_file << "    \"name\": \"" << interleaving_function_name << "\",\n";

      // Emit write_var array.
      json_file << "    \"write_var\": [";
      bool first_var = true;
      for(const auto &var : json_write_vars[interleaving_function_name])
      {
        if(!first_var)
          json_file << ", ";
        json_file << "\"" << var << "\"";
        first_var = false;
      }
      json_file << "],\n";

      // Emit line_added_block array.
      json_file << "    \"line_added_block\": [";
      bool first_line = true;
      for(int line : json_added_lines[interleaving_function_name])
      {
        if(!first_line)
          json_file << ", ";
        json_file << line;
        first_line = false;
      }
      json_file << "]\n";
      json_file << "  }";
    }
    json_file << "\n]\n";
    json_file.close();
    std::cout << "\n[POR] Saved interrupt metadata to: " << json_output_path
              << "\n";
  }
  else
  {
    std::cout << "\n[Error] Failed to create JSON file: " << json_output_path
              << "\n";
  }
}