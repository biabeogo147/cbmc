/// \file
/// Classifies symbolic function calls that belong to the OSEK API surface.

#ifndef CPROVER_OS_API_OSEK_OSEK_API_CLASSIFIER_H
#define CPROVER_OS_API_OSEK_OSEK_API_CLASSIFIER_H

#include <util/irep.h>

namespace os_api
{
namespace osek
{

enum class api_call_kindt
{
  NONE,
  ACTIVATE_TASK,
  TERMINATE_TASK,
  CHAIN_TASK,
  SCHEDULE
};

api_call_kindt classify_api_call(const irep_idt &function_identifier);

} // namespace osek
} // namespace os_api

#endif // CPROVER_OS_API_OSEK_OSEK_API_CLASSIFIER_H
