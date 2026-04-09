/// \file
/// OSEK-specific helpers that translate OIL metadata into runtime tasks.

#ifndef CPROVER_OS_API_OSEK_OSEK_SCHEDULER_H
#define CPROVER_OS_API_OSEK_OSEK_SCHEDULER_H

#include <os-api/core/os_api_types.h>

#include "osek_config.h"

#include <util/expr.h>

#include <optional>

namespace os_api
{
namespace osek
{

core::task_infot make_runtime_task(const task_configurationt &task);

std::optional<core::task_infot>
resolve_task_argument(const osek_configt &config, const exprt &argument);

std::optional<std::size_t>
resolve_task_id_argument(const osek_configt &config, const exprt &argument);

std::optional<std::uint64_t> resolve_event_mask_argument(const exprt &argument);

} // namespace osek
} // namespace os_api

#endif // CPROVER_OS_API_OSEK_OSEK_SCHEDULER_H
