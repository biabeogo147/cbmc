/// \file
/// Applies OSEK scheduling rules to scheduler state and produces symex actions.

#ifndef CPROVER_OS_API_OSEK_OSEK_API_HANDLERS_H
#define CPROVER_OS_API_OSEK_OSEK_API_HANDLERS_H

#include <os-api/core/os_api_types.h>
#include <os-api/core/scheduler_state.h>

#include "osek_api_classifier.h"
#include "osek_config.h"

#include <util/expr.h>

#include <optional>

namespace os_api
{
namespace osek
{

std::optional<core::api_call_resultt> handle_api_call(
  api_call_kindt kind,
  const exprt::operandst &arguments,
  const osek_configt &config,
  core::scheduler_statet &scheduler_state);

} // namespace osek
} // namespace os_api

#endif // CPROVER_OS_API_OSEK_OSEK_API_HANDLERS_H
