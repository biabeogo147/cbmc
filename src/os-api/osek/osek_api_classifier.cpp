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
  if(function_identifier == "SetEvent")
    return api_call_kindt::SET_EVENT;
  if(function_identifier == "ClearEvent")
    return api_call_kindt::CLEAR_EVENT;
  if(function_identifier == "GetEvent")
    return api_call_kindt::GET_EVENT;
  if(function_identifier == "WaitEvent")
    return api_call_kindt::WAIT_EVENT;
  return api_call_kindt::NONE;
}

} // namespace osek
} // namespace os_api
