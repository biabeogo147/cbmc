#include "isr_written_vars.h"

#include <util/std_code.h>
#include <util/std_expr.h>
#include <util/std_types.h>

#include <pointer-analysis/value_set_analysis.h>

#include "rw_set.h"

#include <fstream>
#include <iostream>
#include <map>
#include <set>

void show_isr_written_vars(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::vector<std::string> &isr_names)
{
  namespacet ns(goto_model.symbol_table);
  value_set_analysist value_sets(ns);

  // --- CẤU TRÚC LƯU TRỮ CHO FILE JSON ---
  // Lưu danh sách biến mà mỗi ISR tác động (Set giúp lọc trùng lặp)
  std::map<std::string, std::set<std::string>> json_write_vars;
  // Lưu danh sách các dòng đã chèn ngắt (Set giúp tự động sắp xếp tăng dần và không trùng)
  std::map<std::string, std::set<int>> json_added_lines;

  // Map lưu trữ: Tên ISR -> Danh sách các biến bị ISR đó GHI (Write)
  std::map<irep_idt, std::set<irep_idt>> isr_write_map;

  std::cout << "\n[POR] --- BƯỚC 1: TẠO BẢN ĐỒ BIẾN TỪ CÁC ISR ---\n";
  for(const auto &isr_name : isr_names)
  {
    const irep_idt target_isr = isr_name;
    const auto f_it = goto_model.goto_functions.function_map.find(target_isr);

    if(f_it == goto_model.goto_functions.function_map.end())
    {
      std::cout << " [Cảnh báo] Không tìm thấy hàm ISR: " << isr_name << "\n";
      continue;
    }

    std::cout << "Phân tích ISR: " << isr_name << "\n";
    for(auto it = f_it->second.body.instructions.begin();
        it != f_it->second.body.instructions.end();
        ++it)
    {
      rw_set_loct rw_set(ns, value_sets, target_isr, it, message_handler);
      for(const auto &entry : rw_set.w_entries)
      {
        std::string var_name = id2string(entry.first);
        if(var_name.find('$') == std::string::npos)
        {
          isr_write_map[target_isr].insert(entry.first);
          json_write_vars[isr_name].insert(var_name); // Lưu vào dữ liệu JSON
          std::cout << " -> Ghi biến: " << var_name << "\n";
        }
      }
    }
  }

  std::cout << "\n[POR] --- BƯỚC 2 & 3: QUÉT LUỒNG CHÍNH VÀ CHÈN NGẮT ---\n";

  for(auto &func_pair : goto_model.goto_functions.function_map)
  {
    const irep_idt func_name = func_pair.first;
    auto &func = func_pair.second;
    const std::string name_str = id2string(func_name);

    // Bỏ qua các hàm nội bộ và các hàm ISR
    bool is_an_isr = false;
    for(const auto &isr : isr_names)
    {
      if(name_str == isr)
      {
        is_an_isr = true;
      }
    }

    if(!func.body_available() || name_str.find("__CPROVER") == 0 || is_an_isr)
    {
      continue;
    }

    std::cout << "Quét hàm: " << name_str << "\n";

    // Sử dụng iterator cơ bản thay vì macro để dễ dàng thao tác chèn lệnh
    for(auto it = func.body.instructions.begin();
        it != func.body.instructions.end();)
    {
      rw_set_loct rw_set(ns, value_sets, func_name, it, message_handler);
      std::vector<irep_idt> isrs_to_inject; // Danh sách ISR cần chèn trước lệnh này

      // Kiểm tra xem lệnh này có chạm vào biến của ISR nào không
      for(const auto &map_pair : isr_write_map)
      {
        const irep_idt current_isr = map_pair.first;
        const auto &modified_vars = map_pair.second;
        bool conflict = false;

        for(const auto &entry : rw_set.r_entries)
        {
          if(modified_vars.count(entry.first))
          {
            conflict = true;
          }
        }

        for(const auto &entry : rw_set.w_entries)
        {
          if(modified_vars.count(entry.first))
          {
            conflict = true;
          }
        }

        if(conflict)
        {
          isrs_to_inject.push_back(current_isr);
        }
      }

      // TIẾN HÀNH CHÈN LỆNH
      if(!isrs_to_inject.empty())
      {
        const std::string line_num = id2string(it->source_location().get_line());

        for(const auto &isr_to_call : isrs_to_inject)
        {
          std::string isr_str = id2string(isr_to_call);

          std::cout << " -> Chèn gọi " << id2string(isr_to_call)
                    << " trước dòng " << line_num << "\n";
          json_added_lines[isr_str].insert(std::stoi(line_num)); // Lưu vào dữ liệu JSON

          const symbolt *isr_sym = nullptr;
          if(ns.lookup(isr_to_call, isr_sym))
          {
            std::cout << " [Cảnh báo] Không tìm thấy symbol ISR: "
                      << id2string(isr_to_call) << "\n";
            continue;
          }

          const source_locationt &loc = it->source_location();
          code_function_callt call_code(
            nil_exprt(), isr_sym->symbol_expr(), code_function_callt::argumentst{});
          call_code.add_source_location() = loc;

          goto_programt new_code;

          // 1. Nhánh GOTO (if !nondet)
          const auto branch = new_code.add_instruction(GOTO);
          branch->condition_nonconst() =
            not_exprt(side_effect_expr_nondett(bool_typet(), loc));
          branch->source_location_nonconst() = loc;

          // 2. Lệnh CALL ISR
          new_code.add(goto_programt::make_function_call(call_code, loc));

          // 3. Lệnh SKIP (đích đến của GOTO)
          const auto skip = new_code.add(goto_programt::make_skip(loc));
          branch->targets.push_back(skip);

          // Chèn 3 lệnh vào trước lệnh hiện tại (it)
          func.body.insert_before_swap(it, new_code);

          // Quan trọng: Sau khi insert_before_swap, 'it' sẽ trỏ vào lệnh GOTO vừa chèn.
          // Ta phải đẩy 'it' đi qua 3 lệnh vừa tạo để nó trỏ lại vào lệnh gốc ban đầu.
          std::advance(it, 3);
        }
      }

      // Chuyển sang lệnh gốc tiếp theo
      ++it;
    }

    // Cập nhật lại các đích nhảy (jump targets) bên trong hàm sau khi bị thay đổi cấu trúc
    func.body.update();
  }

  // --- PHẦN 4: XUẤT FILE JSON ---
  std::ofstream json_file("interleaving_adding.json");
  if(json_file.is_open()) {
    json_file << "[\n";
    bool first_isr = true;
    for(const auto &isr_name : isr_names) {
      if(!first_isr) json_file << ",\n";
      first_isr = false;

      json_file << "  {\n";
      json_file << "    \"name\": \"" << isr_name << "\",\n";

      // Ghi danh sách biến (write_var)
      json_file << "    \"write_var\": [";
      bool first_var = true;
      for(const auto &var : json_write_vars[isr_name]) {
        if(!first_var) json_file << ", ";
        json_file << "\"" << var << "\"";
        first_var = false;
      }
      json_file << "],\n";

      // Ghi danh sách dòng đã chèn (line_added_block)
      json_file << "    \"line_added_block\": [";
      bool first_line = true;
      for(int line : json_added_lines[isr_name]) {
        if(!first_line) json_file << ", ";
        json_file << line;
        first_line = false;
      }
      json_file << "]\n";
      json_file << "  }";
    }
    json_file << "\n]\n";
    json_file.close();
    std::cout << "\n[POR] Đã lưu thông tin ngắt vào file: interleaving_adding.json\n";
  } else {
    std::cout << "\n[Lỗi] Không thể tạo file interleaving_adding.json\n";
  }
}