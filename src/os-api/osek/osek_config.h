/// \file
/// Loads OSEK task metadata from a small OIL subset.

#ifndef CPROVER_OS_API_OSEK_OSEK_CONFIG_H
#define CPROVER_OS_API_OSEK_OSEK_CONFIG_H

#include "osek_task_model.h"

#include <util/irep.h>

#include <unordered_map>
#include <vector>

namespace os_api
{
namespace osek
{

class osek_configt
{
public:
  static osek_configt from_oil_file(const std::string &path);

  [[nodiscard]] bool empty() const;
  [[nodiscard]] const std::vector<task_configurationt> &get_tasks() const;
  [[nodiscard]] const task_configurationt *find_task_by_id(
    std::size_t task_id) const;
  [[nodiscard]] const task_configurationt *find_task_by_function(
    const irep_idt &identifier) const;

private:
  void add_task(const task_configurationt &task);

  std::vector<task_configurationt> tasks;
  std::unordered_map<std::size_t, std::size_t> task_index_by_id;
  std::unordered_map<irep_idt, std::size_t, irep_id_hash>
    task_index_by_function;
};

} // namespace osek
} // namespace os_api

#endif // CPROVER_OS_API_OSEK_OSEK_CONFIG_H
