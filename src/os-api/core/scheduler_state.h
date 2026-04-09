/// \file
/// Symbolic scheduler bookkeeping shared between OS API integrations.

#ifndef CPROVER_OS_API_CORE_SCHEDULER_STATE_H
#define CPROVER_OS_API_CORE_SCHEDULER_STATE_H

#include "os_api_types.h"

#include <optional>
#include <unordered_map>
#include <unordered_set>
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
  [[nodiscard]] bool is_task_waiting(std::size_t task_id) const;
  [[nodiscard]] bool is_task_suspended(std::size_t task_id) const;

  bool set_event_for_task(std::size_t task_id, std::uint64_t mask);
  bool clear_events_for_current_task(std::uint64_t mask);
  [[nodiscard]] std::optional<std::uint64_t>
  get_set_events(std::size_t task_id) const;
  bool wait_current_task_for_events(std::uint64_t mask);

  [[nodiscard]] bool ready_queue_empty() const;
  [[nodiscard]] std::optional<task_infot> peek_highest_priority_ready_task()
    const;
  [[nodiscard]] bool has_higher_priority_ready_task_than(int priority) const;
  [[nodiscard]] std::optional<task_infot> pop_highest_priority_ready_task();

private:
  struct task_event_statet
  {
    std::uint64_t set_events = 0;
    std::uint64_t wait_mask = 0;
  };

  void remember_task(const task_infot &task);

  std::vector<task_infot> ready_tasks;
  std::vector<task_infot> active_tasks;
  std::optional<task_infot> current_active_task;
  std::unordered_map<std::size_t, task_infot> known_tasks;
  std::unordered_map<std::size_t, task_event_statet> task_event_state;
  std::unordered_set<std::size_t> waiting_tasks;
};

} // namespace core
} // namespace os_api

#endif // CPROVER_OS_API_CORE_SCHEDULER_STATE_H
