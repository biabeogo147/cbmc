#include "scheduler_state.h"

#include <algorithm>

namespace os_api
{
namespace core
{

void scheduler_statet::reset()
{
  ready_tasks.clear();
  active_tasks.clear();
  current_active_task.reset();
}

bool scheduler_statet::has_active_task() const
{
  return current_active_task.has_value();
}

const std::optional<task_infot> &scheduler_statet::current_task() const
{
  return current_active_task;
}

void scheduler_statet::push_active_task(const task_infot &task)
{
  active_tasks.push_back(task);
  current_active_task = active_tasks.back();
}

void scheduler_statet::pop_active_task()
{
  if(active_tasks.empty())
  {
    current_active_task.reset();
    return;
  }

  active_tasks.pop_back();
  if(active_tasks.empty())
    current_active_task.reset();
  else
    current_active_task = active_tasks.back();
}

void scheduler_statet::enqueue_ready_task(const task_infot &task)
{
  ready_tasks.push_back(task);
}

bool scheduler_statet::ready_queue_empty() const
{
  return ready_tasks.empty();
}

std::optional<task_infot>
scheduler_statet::peek_highest_priority_ready_task() const
{
  if(ready_tasks.empty())
    return std::nullopt;

  const auto it = std::max_element(
    ready_tasks.begin(),
    ready_tasks.end(),
    [](const task_infot &lhs, const task_infot &rhs) {
      return lhs.priority < rhs.priority;
    });

  return *it;
}

bool scheduler_statet::has_higher_priority_ready_task_than(int priority) const
{
  return std::any_of(
    ready_tasks.begin(),
    ready_tasks.end(),
    [priority](const task_infot &task) { return task.priority > priority; });
}

std::optional<task_infot> scheduler_statet::pop_highest_priority_ready_task()
{
  if(ready_tasks.empty())
    return std::nullopt;

  const auto it = std::max_element(
    ready_tasks.begin(),
    ready_tasks.end(),
    [](const task_infot &lhs, const task_infot &rhs) {
      return lhs.priority < rhs.priority;
    });

  task_infot selected = *it;
  ready_tasks.erase(it);
  return selected;
}

} // namespace core
} // namespace os_api
