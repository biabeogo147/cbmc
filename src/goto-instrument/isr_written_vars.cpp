#include "isr_written_vars.h"
#include "rw_set.h"
#include <pointer-analysis/value_set_analysis.h>
#include <iostream>

void show_isr_written_vars(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::string &isr_name)
{
  namespacet ns(goto_model.symbol_table);
  value_set_analysist value_sets(ns);
  irep_idt target_isr = isr_name;

  // --- PHẦN 1: TÌM CÁC BIẾN BỊ GHI BỞI ISR (Code cũ của bạn) ---
  std::set<irep_idt> isr_modified_vars;
  auto f_it = goto_model.goto_functions.function_map.find(target_isr);

  if(f_it != goto_model.goto_functions.function_map.end()) {
    std::cout << "[POR] --- PHÂN TÍCH ISR: " << target_isr << " ---\n";
    forall_goto_program_instructions(it, f_it->second.body) {
      rw_set_loct rw_set(ns, value_sets, target_isr, it, message_handler);
      for(const auto &entry : rw_set.w_entries) {
        std::string var_name = id2string(entry.first);
        if (var_name.find("$") == std::string::npos) {
          isr_modified_vars.insert(entry.first);
          std::cout << " -> Ghi vào biến: " << var_name << "\n";
        }
      }
    }
  }

  // --- PHẦN 2: PHÂN TÍCH CÁC LUỒNG CHÍNH ĐỂ TÌM BIẾN ĐƯỢC SỬ DỤNG ---
  std::cout << "\n[POR] --- PHÂN TÍCH LUỒNG CHÍNH ---\n";

  // Duyệt qua toàn bộ các hàm có trong chương trình
  for(const auto &func_pair : goto_model.goto_functions.function_map) {
    irep_idt func_name = func_pair.first;
    const goto_functionst::goto_functiont &func = func_pair.second;
    std::string name_str = id2string(func_name);

    // Bỏ qua ISR, bỏ qua các hàm nội bộ của CPROVER và các hàm không có body
    if(!func.body_available() || name_str.find("__CPROVER") == 0 || name_str == isr_name) {
      continue;
    }

    std::cout << "Hàm: " << name_str << "\n";

    // Duyệt qua từng lệnh của hàm luồng chính
    forall_goto_program_instructions(it, func.body) {
      rw_set_loct rw_set(ns, value_sets, func_name, it, message_handler);

      // Bỏ qua nếu lệnh này không đọc cũng không ghi biến nào
      if(rw_set.empty()) continue;

      // Lấy số dòng code C tương ứng của lệnh này
      std::string line_num = id2string(it->source_location().get_line());
      if(line_num.empty()) continue; // Bỏ qua các lệnh trung gian do trình dịch tự sinh

      bool has_printed_line = false;

      // Kiểm tra các biến được ĐỌC (Read)
      for(const auto &entry : rw_set.r_entries) {
        std::string var = id2string(entry.first);
        if(var.find("$") == std::string::npos) { // Lọc biến rác
          if(!has_printed_line) { std::cout << "  [Dòng " << line_num << "] "; has_printed_line = true; }
          std::cout << "Đọc(" << var << ") ";
        }
      }

      // Kiểm tra các biến được GHI (Write)
      for(const auto &entry : rw_set.w_entries) {
        std::string var = id2string(entry.first);
        if(var.find("$") == std::string::npos) { // Lọc biến rác
          if(!has_printed_line) { std::cout << "  [Dòng " << line_num << "] "; has_printed_line = true; }
          std::cout << "Ghi(" << var << ") ";
        }
      }

      if(has_printed_line) std::cout << "\n";
    }
  }
}