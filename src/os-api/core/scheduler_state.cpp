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
  known_tasks.clear();
  task_event_state.clear();
  waiting_tasks.clear();
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
  remember_task(task);
  waiting_tasks.erase(task.task_id);
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
  remember_task(task);
  waiting_tasks.erase(task.task_id);
  ready_tasks.push_back(task);
}

void scheduler_statet::reset_task_events(const std::size_t task_id)
{
  const auto task_it = known_tasks.find(task_id);
  if(task_it == known_tasks.end())
    return;

  task_event_statet &event_state = task_event_state[task_id];
  event_state.set_events = 0;
  event_state.wait_mask = 0;
  waiting_tasks.erase(task_id);
}

bool scheduler_statet::is_task_waiting(const std::size_t task_id) const
{
  return waiting_tasks.find(task_id) != waiting_tasks.end();
}

bool scheduler_statet::is_task_suspended(const std::size_t task_id) const
{
  if(is_task_waiting(task_id))
    return false;

  if(
    current_active_task.has_value() && current_active_task->task_id == task_id)
  {
    return false;
  }

  if(
    std::any_of(
      active_tasks.begin(),
      active_tasks.end(),
      [task_id](const task_infot &task) { return task.task_id == task_id; }))
  {
    return false;
  }

  return std::none_of(
    ready_tasks.begin(),
    ready_tasks.end(),
    [task_id](const task_infot &task) { return task.task_id == task_id; });
}

bool scheduler_statet::set_event_for_task(
  const std::size_t task_id,
  const std::uint64_t mask)
{
  const auto task_it = known_tasks.find(task_id);
  if(task_it == known_tasks.end())
    return false;

  if(!task_it->second.extended || is_task_suspended(task_id))
    return false;

  const auto effective_mask = mask & task_it->second.event_mask;
  if(effective_mask == 0)
    return false;

  task_event_statet &event_state = task_event_state[task_id];
  event_state.set_events |= effective_mask;

  if(
    is_task_waiting(task_id) && event_state.wait_mask != 0 &&
    (event_state.set_events & event_state.wait_mask) != 0)
  {
    event_state.wait_mask = 0;
    waiting_tasks.erase(task_id);
    enqueue_ready_task(task_it->second);
    return true;
  }

  return false;
}

bool scheduler_statet::clear_events_for_current_task(const std::uint64_t mask)
{
  if(!current_active_task.has_value())
    return false;

  if(!current_active_task->extended)
    return false;

  auto event_it = task_event_state.find(current_active_task->task_id);
  if(event_it == task_event_state.end())
    return false;

  event_it->second.set_events &= ~(mask & current_active_task->event_mask);
  return true;
}

std::optional<std::uint64_t>
scheduler_statet::get_set_events(const std::size_t task_id) const
{
  const auto task_it = known_tasks.find(task_id);
  if(task_it == known_tasks.end() || !task_it->second.extended)
    return std::nullopt;

  if(is_task_suspended(task_id))
    return std::nullopt;

  const auto event_it = task_event_state.find(task_id);
  if(event_it == task_event_state.end())
    return std::nullopt;

  return event_it->second.set_events;
}

bool scheduler_statet::wait_current_task_for_events(const std::uint64_t mask)
{
  if(!current_active_task.has_value())
    return false;

  if(!current_active_task->extended)
    return false;

  const std::size_t task_id = current_active_task->task_id;
  const auto effective_mask = mask & current_active_task->event_mask;
  if(effective_mask == 0)
    return false;

  task_event_statet &event_state = task_event_state[task_id];
  if((event_state.set_events & effective_mask) != 0)
    return false;

  event_state.wait_mask = effective_mask;
  waiting_tasks.insert(task_id);
  pop_active_task();
  return true;
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

void scheduler_statet::remember_task(const task_infot &task)
{
  known_tasks[task.task_id] = task;
  task_event_state.try_emplace(task.task_id);
}

} // namespace core
} // namespace os_api
