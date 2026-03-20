#ifndef CPROVER_INTERLEAVING_ANALYSIS_INTERLEAVING_ANALYSIS_H
#define CPROVER_INTERLEAVING_ANALYSIS_INTERLEAVING_ANALYSIS_H

#include <goto-programs/goto_model.h>
#include <util/message.h>

#include <map>
#include <set>
#include <string>
#include <vector>

enum class interleaving_modet
{
  analysis_only,
  analysis_and_instrument
};

struct interleaving_configt
{
  std::vector<std::string> function_names;
  std::string json_output_path = "interleaving_adding.json";
  interleaving_modet mode = interleaving_modet::analysis_only;
};

struct interleaving_function_resultt
{
  std::string display_name;
  std::set<irep_idt> written_variables;
  std::set<int> candidate_lines;
};

struct interleaving_resultt
{
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
