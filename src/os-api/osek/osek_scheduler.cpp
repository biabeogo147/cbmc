#include "osek_scheduler.h"

#include <util/arith_tools.h>
#include <util/std_expr.h>

namespace os_api
{
namespace osek
{

core::task_infot make_runtime_task(const task_configurationt &task)
{
  return {
    task.task_id,
    task.function_identifier,
    task.priority,
    task.schedule == schedule_typet::FULL,
    task.task_type == task_typet::EXTENDED,
    task.event_mask};
}

namespace
{

std::optional<std::size_t> resolve_numeric_id(const exprt &argument)
{
  const exprt *resolved_argument = &argument;
  while(resolved_argument->id() == ID_typecast)
    resolved_argument = &to_typecast_expr(*resolved_argument).op();

  if(resolved_argument->id() != ID_constant)
    return std::nullopt;

  auto numeric_value =
    numeric_cast<std::size_t>(to_constant_expr(*resolved_argument));
  if(numeric_value.has_value())
    return numeric_value;

  const auto raw_value = id2string(to_constant_expr(*resolved_argument).get_value());
  return numeric_castt<std::size_t>{}(string2integer(raw_value, 16));
}

} // namespace

std::optional<core::task_infot>
resolve_task_argument(const osek_configt &config, const exprt &argument)
{
  if(const auto task_id = resolve_numeric_id(argument))
  {
    const auto *task = config.find_task_by_id(*task_id);
    if(task != nullptr)
      return make_runtime_task(*task);
  }

  const exprt *resolved_argument = &argument;
  while(resolved_argument->id() == ID_typecast)
    resolved_argument = &to_typecast_expr(*resolved_argument).op();

  if(resolved_argument->id() == ID_symbol)
  {
    const auto *task = config.find_task_by_function(
      to_symbol_expr(*resolved_argument).get_identifier());
    if(task != nullptr)
      return make_runtime_task(*task);
  }

  return std::nullopt;
}

std::optional<std::size_t>
resolve_task_id_argument(const osek_configt &config, const exprt &argument)
{
  if(const auto task_id = resolve_numeric_id(argument))
    return task_id;

  const exprt *resolved_argument = &argument;
  while(resolved_argument->id() == ID_typecast)
    resolved_argument = &to_typecast_expr(*resolved_argument).op();

  if(resolved_argument->id() != ID_symbol)
    return std::nullopt;

  const auto *task =
    config.find_task_by_function(to_symbol_expr(*resolved_argument).get_identifier());
  if(task == nullptr)
    return std::nullopt;

  return task->task_id;
}

std::optional<std::uint64_t> resolve_event_mask_argument(const exprt &argument)
{
  const auto numeric = resolve_numeric_id(argument);
  if(!numeric.has_value())
    return std::nullopt;

  return static_cast<std::uint64_t>(*numeric);
}

} // namespace osek
} // namespace os_api
