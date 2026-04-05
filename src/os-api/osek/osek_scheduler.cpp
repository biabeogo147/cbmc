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
    task.function_identifier,
    task.priority,
    task.schedule == schedule_typet::FULL};
}

std::optional<core::task_infot>
resolve_task_argument(const osek_configt &config, const exprt &argument)
{
  const exprt *resolved_argument = &argument;
  while(resolved_argument->id() == ID_typecast)
    resolved_argument = &to_typecast_expr(*resolved_argument).op();

  if(resolved_argument->id() == ID_constant)
  {
    auto numeric_task_id =
      numeric_cast<std::size_t>(to_constant_expr(*resolved_argument));
    if(!numeric_task_id.has_value())
    {
      const auto raw_value =
        id2string(to_constant_expr(*resolved_argument).get_value());
      const auto fallback_value =
        numeric_castt<std::size_t>{}(string2integer(raw_value, 16));
      if(fallback_value.has_value())
        numeric_task_id = fallback_value;
    }

    if(numeric_task_id.has_value())
    {
      const auto *task = config.find_task_by_id(*numeric_task_id);
      if(task != nullptr)
        return make_runtime_task(*task);
    }
  }

  if(resolved_argument->id() == ID_symbol)
  {
    const auto *task = config.find_task_by_function(
      to_symbol_expr(*resolved_argument).get_identifier());
    if(task != nullptr)
      return make_runtime_task(*task);
  }

  return std::nullopt;
}

} // namespace osek
} // namespace os_api
