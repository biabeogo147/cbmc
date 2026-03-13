#ifndef CPROVER_GOTO_INSTRUMENT_ISR_WRITTEN_VARS_H
#define CPROVER_GOTO_INSTRUMENT_ISR_WRITTEN_VARS_H

#include <goto-programs/goto_model.h>
#include <util/message.h>
#include <string>
#include <vector>

// Hàm phân tích và in ra các biến bị ghi (write) trong ISR
void show_isr_written_vars(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::vector<std::string> &isr_names);

inline void show_isr_written_vars(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::string &isr_name)
{
  show_isr_written_vars(
    goto_model,
    message_handler,
    std::vector<std::string>{isr_name});
}

#endif