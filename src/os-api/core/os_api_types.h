/// \file
/// Shared result types for modular OS API integrations.

#ifndef CPROVER_OS_API_CORE_OS_API_TYPES_H
#define CPROVER_OS_API_CORE_OS_API_TYPES_H

#include <util/irep.h>

#include <optional>

namespace os_api
{
namespace core
{

enum class api_kindt
{
  NONE,
  OSEK
};

enum class next_step_kindt
{
  CONTINUE_CURRENT_THREAD,
  START_TASK_NOW,
  POP_TASK_AND_RESUME_CALLER,
  POP_TASK_AND_START_TASK
};

struct task_infot
{
  irep_idt function_identifier;
  int priority = 0;
  bool preemptive = true;
};

struct api_call_resultt
{
  next_step_kindt next_step = next_step_kindt::CONTINUE_CURRENT_THREAD;
  std::optional<task_infot> next_task;
};

} // namespace core
} // namespace os_api

#endif // CPROVER_OS_API_CORE_OS_API_TYPES_H
