#include "os_api_dispatcher.h"

#include <util/exception_utils.h>

#include <os-api/osek/osek_api_classifier.h>
#include <os-api/osek/osek_api_handlers.h>

namespace os_api
{
namespace core
{

os_api_dispatchert::os_api_dispatchert(const optionst &options)
{
  if(!options.is_set("os-api"))
    return;

  const auto requested_api = options.get_option("os-api");
  if(requested_api == "osek")
  {
    const auto oil_path = options.get_option("osek-oil");
    if(oil_path.empty())
    {
      throw invalid_command_line_argument_exceptiont(
        "--os-api osek requires --osek-oil <file>", "--os-api");
    }

    api_kind = api_kindt::OSEK;
    osek_configuration = osek::osek_configt::from_oil_file(oil_path);
    return;
  }

  throw invalid_command_line_argument_exceptiont(
    "unsupported OS API integration '" + requested_api + "'", "--os-api");
}

bool os_api_dispatchert::enabled() const
{
  return api_kind != api_kindt::NONE;
}

api_kindt os_api_dispatchert::selected_api() const
{
  return api_kind;
}

const osek::osek_configt *os_api_dispatchert::osek_config() const
{
  if(!osek_configuration.has_value())
    return nullptr;
  return &(*osek_configuration);
}

std::optional<api_call_resultt> os_api_dispatchert::handle_function_call(
  const irep_idt &function_identifier,
  const exprt::operandst &arguments,
  scheduler_statet &scheduler_state) const
{
  if(api_kind != api_kindt::OSEK || !osek_configuration.has_value())
    return std::nullopt;

  const auto kind = osek::classify_api_call(function_identifier);
  return osek::handle_api_call(
    kind, arguments, *osek_configuration, scheduler_state);
}

} // namespace core
} // namespace os_api
