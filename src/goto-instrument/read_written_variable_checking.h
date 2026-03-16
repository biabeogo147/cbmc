#ifndef CPROVER_GOTO_INSTRUMENT_READ_WRITTEN_VARIABLE_H
#define CPROVER_GOTO_INSTRUMENT_READ_WRITTEN_VARIABLE_H

#include <goto-programs/goto_model.h>
#include <util/message.h>
#include <string>
#include <vector>

// Hàm phân tích và in ra các biến bị ghi (write) trong ISR
void show_read_written_variables(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::vector<std::string> &function_name);

inline void show_read_written_variables(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::string &function_name)
{
  show_read_written_variables(
    goto_model,
    message_handler,
    std::vector<std::string>{function_name});
}

#endif