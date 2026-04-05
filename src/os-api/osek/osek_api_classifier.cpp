#include "osek_api_classifier.h"

namespace os_api
{
namespace osek
{

api_call_kindt classify_api_call(const irep_idt &function_identifier)
{
  if(function_identifier == "ActivateTask")
    return api_call_kindt::ACTIVATE_TASK;
  if(function_identifier == "TerminateTask")
    return api_call_kindt::TERMINATE_TASK;
  if(function_identifier == "ChainTask")
    return api_call_kindt::CHAIN_TASK;
  if(function_identifier == "Schedule")
    return api_call_kindt::SCHEDULE;
  return api_call_kindt::NONE;
}

} // namespace osek
} // namespace os_api
