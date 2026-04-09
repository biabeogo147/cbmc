#include "osek_api_handlers.h"

#include "osek_scheduler.h"

#include <util/arith_tools.h>
#include <util/pointer_expr.h>
#include <util/std_expr.h>

namespace os_api
{
namespace osek
{

namespace
{

core::api_call_resultt maybe_dispatch_highest_ready_task(
  core::scheduler_statet &scheduler_state,
  const core::next_step_kindt next_step_kind)
{
  core::api_call_resultt result;
  result.next_step = next_step_kind;

  const auto next_task = scheduler_state.pop_highest_priority_ready_task();
  if(next_task.has_value())
  {
    scheduler_state.push_active_task(*next_task);
    result.next_task = next_task;
  }

  return result;
}

core::api_call_resultt schedule_after_reschedule_point(
  core::scheduler_statet &scheduler_state,
  const core::next_step_kindt resume_current_step_kind,
  const core::next_step_kindt start_ready_step_kind)
{
  core::api_call_resultt result;

  const auto highest_ready = scheduler_state.peek_highest_priority_ready_task();
  if(!highest_ready.has_value())
  {
    result.next_step = resume_current_step_kind;
    return result;
  }

  const auto &current_task = scheduler_state.current_task();
  if(
    current_task.has_value() &&
    highest_ready->priority <= current_task->priority)
  {
    result.next_step = resume_current_step_kind;
    return result;
  }

  return maybe_dispatch_highest_ready_task(
    scheduler_state, start_ready_step_kind);
}

} // namespace

std::optional<core::api_call_resultt> handle_api_call(
  const api_call_kindt kind,
  const exprt::operandst &arguments,
  const osek_configt &config,
  core::scheduler_statet &scheduler_state)
{
  core::api_call_resultt result;

  switch(kind)
  {
  case api_call_kindt::NONE:
    return std::nullopt;

  case api_call_kindt::ACTIVATE_TASK:
  {
    if(arguments.empty())
      return result;

    const auto task = resolve_task_argument(config, arguments.front());
    if(!task.has_value())
      return result;

    if(scheduler_state.is_task_suspended(task->task_id))
      scheduler_state.reset_task_events(task->task_id);

    scheduler_state.enqueue_ready_task(*task);

    const auto &current_task = scheduler_state.current_task();
    if(!current_task.has_value())
    {
      return maybe_dispatch_highest_ready_task(
        scheduler_state, core::next_step_kindt::START_TASK_NOW);
    }

    if(
      current_task->preemptive &&
      scheduler_state.has_higher_priority_ready_task_than(current_task->priority))
    {
      return maybe_dispatch_highest_ready_task(
        scheduler_state, core::next_step_kindt::START_TASK_NOW);
    }

    return result;
  }

  case api_call_kindt::TERMINATE_TASK:
  {
    scheduler_state.pop_active_task();
    return schedule_after_reschedule_point(
      scheduler_state,
      core::next_step_kindt::POP_TASK_AND_RESUME_CALLER,
      core::next_step_kindt::POP_TASK_AND_START_TASK);
  }

  case api_call_kindt::CHAIN_TASK:
  {
    if(arguments.empty())
      return result;

    const auto task = resolve_task_argument(config, arguments.front());
    if(!task.has_value())
      return result;

    scheduler_state.pop_active_task();

    if(scheduler_state.is_task_suspended(task->task_id))
      scheduler_state.reset_task_events(task->task_id);

    scheduler_state.enqueue_ready_task(*task);
    return schedule_after_reschedule_point(
      scheduler_state,
      core::next_step_kindt::POP_TASK_AND_RESUME_CALLER,
      core::next_step_kindt::POP_TASK_AND_START_TASK);
  }

  case api_call_kindt::SCHEDULE:
  {
    const auto &current_task = scheduler_state.current_task();
    if(
      current_task.has_value() && current_task->preemptive &&
      scheduler_state.has_higher_priority_ready_task_than(current_task->priority))
    {
      return maybe_dispatch_highest_ready_task(
        scheduler_state, core::next_step_kindt::START_TASK_NOW);
    }

    return result;
  }

  case api_call_kindt::SET_EVENT:
  {
    if(arguments.size() < 2)
      return result;

    const auto task_id = resolve_task_id_argument(config, arguments.front());
    const auto mask = resolve_event_mask_argument(arguments[1]);
    if(!task_id.has_value() || !mask.has_value())
      return result;

    const bool woke_waiting_task =
      scheduler_state.set_event_for_task(*task_id, *mask);
    if(!woke_waiting_task)
      return result;

    return schedule_after_reschedule_point(
      scheduler_state,
      core::next_step_kindt::CONTINUE_CURRENT_THREAD,
      core::next_step_kindt::START_TASK_NOW);
  }

  case api_call_kindt::CLEAR_EVENT:
  {
    if(arguments.empty())
      return result;

    const auto mask = resolve_event_mask_argument(arguments.front());
    if(!mask.has_value())
      return result;

    scheduler_state.clear_events_for_current_task(*mask);
    return result;
  }

  case api_call_kindt::GET_EVENT:
  {
    if(arguments.size() < 2)
      return result;

    const auto task_id = resolve_task_id_argument(config, arguments.front());
    if(!task_id.has_value())
      return result;

    const auto set_events = scheduler_state.get_set_events(*task_id);
    if(!set_events.has_value())
      return result;

    const exprt &event_out_pointer = arguments[1];
    if(event_out_pointer.type().id() != ID_pointer)
      return result;

    const typet &event_mask_type = to_pointer_type(event_out_pointer.type()).base_type();
    result.memory_writeback = core::memory_writebackt{
      dereference_exprt(event_out_pointer, event_mask_type),
      from_integer(*set_events, event_mask_type)};
    return result;
  }

  case api_call_kindt::WAIT_EVENT:
  {
    if(arguments.empty())
      return result;

    const auto mask = resolve_event_mask_argument(arguments.front());
    if(!mask.has_value())
      return result;

    if(!scheduler_state.wait_current_task_for_events(*mask))
      return result;

    const auto next_task = scheduler_state.pop_highest_priority_ready_task();
    if(next_task.has_value())
    {
      scheduler_state.push_active_task(*next_task);
      result.next_step = core::next_step_kindt::POP_TASK_AND_START_TASK;
      result.next_task = next_task;
    }
    else
      result.next_step = core::next_step_kindt::POP_TASK_AND_RESUME_CALLER;

    return result;
  }
  }

  return result;
}

} // namespace osek
} // namespace os_api
