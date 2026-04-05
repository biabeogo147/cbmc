/// \file
/// Symbolic scheduler bookkeeping shared between OS API integrations.

#ifndef CPROVER_OS_API_CORE_SCHEDULER_STATE_H
#define CPROVER_OS_API_CORE_SCHEDULER_STATE_H

#include "os_api_types.h"

#include <optional>
#include <vector>

namespace os_api
{
namespace core
{

class scheduler_statet
{
public:
  void reset();

  [[nodiscard]] bool has_active_task() const;
  [[nodiscard]] const std::optional<task_infot> &current_task() const;

  void push_active_task(const task_infot &task);
  void pop_active_task();
  void enqueue_ready_task(const task_infot &task);

  [[nodiscard]] bool ready_queue_empty() const;
  [[nodiscard]] std::optional<task_infot> peek_highest_priority_ready_task()
    const;
  [[nodiscard]] bool has_higher_priority_ready_task_than(int priority) const;
  [[nodiscard]] std::optional<task_infot> pop_highest_priority_ready_task();

private:
  std::vector<task_infot> ready_tasks;
  std::vector<task_infot> active_tasks;
  std::optional<task_infot> current_active_task;
};

} // namespace core
} // namespace os_api

#endif // CPROVER_OS_API_CORE_SCHEDULER_STATE_H
