#ifndef CPROVER_INTERLEAVING_ANALYSIS_INTERLEAVING_ANALYSIS_H
#define CPROVER_INTERLEAVING_ANALYSIS_INTERLEAVING_ANALYSIS_H

#include <goto-programs/goto_model.h>
#include <util/message.h>

#include <map>
#include <set>
#include <string>
#include <vector>

struct interleaving_configt
{
  std::vector<std::string> interleaving_source_files;
  std::vector<std::string> translation_units;
  std::string project_root_path;
  std::string json_output_path = "interleaving_manifest.json";
};

struct interleaving_function_resultt
{
  std::set<irep_idt> written_global_variables;
  std::map<std::string, std::set<int>> candidate_lines_by_file;
};

struct interleaving_project_resultt
{
  std::string project_root;
  std::vector<std::string> interleaving_source_files;
  std::vector<std::string> translation_units;
};

struct interleaving_resultt
{
  interleaving_project_resultt project;
  std::vector<irep_idt> function_order;
  std::map<irep_idt, interleaving_function_resultt> functions;
};

interleaving_resultt analyze_interleavings(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const interleaving_configt &config);

bool write_interleaving_report(
  const interleaving_resultt &result,
  const interleaving_configt &config,
  message_handlert &message_handler);

interleaving_resultt run_interleaving_analysis(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const interleaving_configt &config);

#endif // CPROVER_INTERLEAVING_ANALYSIS_INTERLEAVING_ANALYSIS_H
