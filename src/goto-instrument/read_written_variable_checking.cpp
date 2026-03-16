#include "read_written_variable_checking.h"

#include <util/std_code.h>

#include <pointer-analysis/value_set_analysis.h>

#include "rw_set.h"

#include <fstream>
#include <iostream>
#include <map>
#include <set>

void show_read_written_variables(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const std::vector<std::string> &function_name)
{
  namespacet ns(goto_model.symbol_table);
  value_set_analysist value_sets(ns);

  // --- CẤU TRÚC LƯU TRỮ CHO FILE JSON ---
  // Lưu danh sách biến mà mỗi Function tác động (Set giúp lọc trùng lặp)
  std::map<std::string, std::set<std::string>> json_write_vars;
  // Lưu danh sách các dòng đã chèn ngắt (Set giúp tự động sắp xếp tăng dần và không trùng)
  std::map<std::string, std::set<int>> json_added_lines;

  // Map lưu trữ: Tên Function -> Danh sách các biến bị Function đó GHI (Write)
  std::map<irep_idt, std::set<irep_idt>> function_write_map;

  std::cout << "\n[POR] --- BƯỚC 1: TẠO BẢN ĐỒ BIẾN TỪ CÁC Function ---\n";
  for(const auto &interleaving_function_name : function_name)
  {
    const irep_idt target_interleaving_function = interleaving_function_name;
    const auto f_it = goto_model.goto_functions.function_map.find(target_interleaving_function);

    if(f_it == goto_model.goto_functions.function_map.end())
    {
      std::cout << " [Cảnh báo] Không tìm thấy hàm Function: " << interleaving_function_name << "\n";
      continue;
    }

    std::cout << "Phân tích Function: " << interleaving_function_name << "\n";
    for(auto it = f_it->second.body.instructions.begin();
        it != f_it->second.body.instructions.end();
        ++it)
    {
      rw_set_loct rw_set(ns, value_sets, target_interleaving_function, it, message_handler);
      for(const auto &entry : rw_set.w_entries)
      {
        std::string var_name = id2string(entry.first);
        if(var_name.find('$') == std::string::npos)
        {
          function_write_map[target_interleaving_function].insert(entry.first);
          json_write_vars[interleaving_function_name].insert(var_name); // Lưu vào dữ liệu JSON
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

    // Bỏ qua các hàm nội bộ và các hàm Function
    bool is_an_interleaving_function = false;
    for(const auto &interleaving_function : function_name)
    {
      if(name_str == interleaving_function)
      {
        is_an_interleaving_function = true;
      }
    }

    if(!func.body_available() || name_str.find("__CPROVER") == 0 || is_an_interleaving_function)
    {
      continue;
    }

    std::cout << "Quét hàm: " << name_str << "\n";

    // Sử dụng iterator cơ bản thay vì macro để dễ dàng thao tác chèn lệnh
    for(auto it = func.body.instructions.begin();
        it != func.body.instructions.end();)
    {
      rw_set_loct rw_set(ns, value_sets, func_name, it, message_handler);
      std::vector<irep_idt> interleaving_functions_to_inject; // Danh sách Function cần chèn trước lệnh này

      // Kiểm tra xem lệnh này có chạm vào biến của Function nào không
      for(const auto &map_pair : function_write_map)
      {
        const irep_idt current_interleaving_function = map_pair.first;
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
          interleaving_functions_to_inject.push_back(current_interleaving_function);
        }
      }

      // TIẾN HÀNH CHÈN LỆNH
      if(!interleaving_functions_to_inject.empty())
      {
        const std::string line_num = id2string(it->source_location().get_line());

        for(const auto &interleaving_function_to_call : interleaving_functions_to_inject)
        {
          std::string interleaving_function_str = id2string(interleaving_function_to_call);

          std::cout << " -> Chèn gọi " << id2string(interleaving_function_to_call)
                    << " trước dòng " << line_num << "\n";
          json_added_lines[interleaving_function_str].insert(std::stoi(line_num)); // Lưu vào dữ liệu JSON

          const symbolt *interleaving_function_sym = nullptr;
          if(ns.lookup(interleaving_function_to_call, interleaving_function_sym))
          {
            std::cout << " [Cảnh báo] Không tìm thấy symbol Function: "
                      << id2string(interleaving_function_to_call) << "\n";
          }
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
    bool first_interleaving_function = true;
    for(const auto &interleaving_function_name : function_name) {
      if(!first_interleaving_function) json_file << ",\n";
      first_interleaving_function = false;

      json_file << "  {\n";
      json_file << "    \"name\": \"" << interleaving_function_name << "\",\n";

      // Ghi danh sách biến (write_var)
      json_file << "    \"write_var\": [";
      bool first_var = true;
      for(const auto &var : json_write_vars[interleaving_function_name]) {
        if(!first_var) json_file << ", ";
        json_file << "\"" << var << "\"";
        first_var = false;
      }
      json_file << "],\n";

      // Ghi danh sách dòng đã chèn (line_added_block)
      json_file << "    \"line_added_block\": [";
      bool first_line = true;
      for(int line : json_added_lines[interleaving_function_name]) {
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