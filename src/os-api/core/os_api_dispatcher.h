/// \file
/// Runtime dispatcher selecting the active OS API integration.

#ifndef CPROVER_OS_API_CORE_OS_API_DISPATCHER_H
#define CPROVER_OS_API_CORE_OS_API_DISPATCHER_H

#include "os_api_types.h"
#include "scheduler_state.h"

#include <os-api/osek/osek_config.h>

#include <util/expr.h>
#include <util/options.h>

#include <optional>

namespace os_api
{
namespace core
{

class os_api_dispatchert
{
public:
  explicit os_api_dispatchert(const optionst &options);

  [[nodiscard]] bool enabled() const;
  [[nodiscard]] api_kindt selected_api() const;
  [[nodiscard]] const osek::osek_configt *osek_config() const;

  std::optional<api_call_resultt> handle_function_call(
    const irep_idt &function_identifier,
    const exprt::operandst &arguments,
    scheduler_statet &scheduler_state) const;

private:
  api_kindt api_kind = api_kindt::NONE;
  std::optional<osek::osek_configt> osek_configuration;
};

} // namespace core
} // namespace os_api

#endif // CPROVER_OS_API_CORE_OS_API_DISPATCHER_H
