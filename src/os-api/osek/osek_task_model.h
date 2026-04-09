/// \file
/// OSEK task metadata loaded from OIL configuration.

#ifndef CPROVER_OS_API_OSEK_OSEK_TASK_MODEL_H
#define CPROVER_OS_API_OSEK_OSEK_TASK_MODEL_H

#include <util/irep.h>

#include <cstddef>
#include <cstdint>

namespace os_api
{
namespace osek
{

enum class schedule_typet
{
  FULL,
  NON
};

enum class task_typet
{
  BASIC,
  EXTENDED
};

struct task_configurationt
{
  std::size_t task_id = 0;
  irep_idt task_name;
  irep_idt function_identifier;
  int priority = 0;
  schedule_typet schedule = schedule_typet::FULL;
  task_typet task_type = task_typet::BASIC;
  std::uint64_t event_mask = 0;
  bool autostart = false;
};

} // namespace osek
} // namespace os_api

#endif // CPROVER_OS_API_OSEK_OSEK_TASK_MODEL_H
