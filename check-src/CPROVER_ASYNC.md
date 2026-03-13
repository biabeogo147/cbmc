# Luồng hoạt động chi tiết của `__CPROVER_ASYNC` trong CBMC

Tài liệu này mô tả chi tiết đường đi của chương trình khi dùng
`__CPROVER_ASYNC_N: ...`, đi theo thứ tự pipeline của CBMC: frontend
(typecheck + goto conversion) -> GOTO IR -> symbolic execution -> partial-order
constraints.

Ví dụ bám theo:

```c
__CPROVER_ASYNC_0: isr1(0);
task1();
task2();
assert(x == 5);
```

---

## 1) Frontend: từ label `__CPROVER_ASYNC_*` sang thread block trong GOTO IR

### 1.1 Vào `goto_convertt::convert(...)` -> `convert_label(...)`

Trong `src/ansi-c/goto-conversion/goto_convert.cpp`, khi gặp statement kiểu
label, dispatcher gọi `convert_label(...)`.

- Hàm: `goto_convertt::convert_label(const code_labelt &, goto_programt &, ...)`
- Mục tiêu: nhận diện label đặc biệt bắt đầu bằng `__CPROVER_ASYNC_`.
- Biến/đầu vào quan trọng tại đây:
    - `code`: node AST cho label (chứa `label` + `code` phía sau label).
    - `label`: `code.get_label()`.
    - `dest`: `goto_programt` đang được build cho hàm hiện tại.
    - `targets`: cấu trúc nội bộ để fix target/scope cho goto về sau.

Nhánh quan trọng:

- Nếu `label.starts_with(CPROVER_PREFIX "ASYNC_")`: thay vì coi là label bình
  thường, hàm gom phần thân sau label vào một `code_blockt thread_body`, rồi gọi
  `generate_thread_block(thread_body, dest, mode)`.
- Nếu không phải async label: convert bình thường và đăng ký label vào
  `targets.labels`.

### 1.2 `generate_thread_block(...)` sinh CFG mẫu cho việc spawn

- Hàm: `goto_convertt::generate_thread_block(const code_blockt &, goto_programt &, ...)`
- Mục tiêu: mã hóa async label thành pattern GOTO-IR chuẩn để một nhánh là
  thread mới, nhánh còn lại là thread hiện tại tiếp tục chạy.

Cấu trúc nó tạo ra:

1. `A: START_THREAD : C`
2. `B: GOTO Z`
3. `C: SKIP`
4. `D: {THREAD BODY}`
5. `E: END_THREAD`
6. `Z: SKIP`

Biến nội bộ chính trong hàm:

- `preamble`, `body`, `postamble`: các đoạn chương trình tạm để ghép lại.
- `c`: target tới điểm bắt đầu body của thread mới.
- `z`: target điểm tiếp tục của thread hiện tại sau khi bỏ qua body thread mới.

Ý nghĩa: `START_THREAD` tạo thread mới bắt đầu tại `c`; thread hiện tại đi theo
`GOTO z` để không chạy thân thread mới.

---

## 2) GOTO IR semantics mà các bước sau dựa vào

Trong `src/goto-programs/goto_program.h`:

- `START_THREAD`: spawn thread mới, target là điểm vào của thread mới.
- `END_THREAD`: kết thúc thread hiện tại.
- `ATOMIC_BEGIN`/`ATOMIC_END`: đánh dấu đoạn không cho interleaving chen vào.

Trong cùng file này, comment semantics của instruction nêu rõ cách hiểu control
flow của từng instruction type. Các phân tích/symex đều bám theo semantics này.

---

## 3) Typecheck liên quan `start_thread` AST node

Trong `src/ansi-c/c_typecheck_code.cpp`:

- Dispatcher `typecheck_code(...)` có nhánh `ID_start_thread`.
- `c_typecheck_baset::typecheck_start_thread(codet &code)` kiểm tra:
    - phải có đúng 1 operand (thân code chạy trong thread mới),
    - rồi typecheck operand đó như một đoạn code bình thường.

Lưu ý: với `__CPROVER_ASYNC_*` theo dạng label trong C source, đường chính là
`convert_label(...)`; nhánh `ID_start_thread` vẫn là điểm chuẩn cho AST node
`start_thread` nếu nó được tạo ở bước frontend khác.

---

## 4) Symex: thread được tạo và thực thi xen kẽ như thế nào

### 4.1 Điểm vào thực thi từng instruction: `execute_next_instruction(...)`

Trong `src/goto-symex/symex_main.cpp`, hàm
`goto_symext::execute_next_instruction(...)` đọc `instruction = *state.source.pc`
rồi switch theo `instruction.type()`.

Các case quan trọng:

- `START_THREAD` -> gọi `symex_start_thread(state)`
- `END_THREAD` -> đặt `state.reachable = false` (giống assume(false) cho thread)
- `ATOMIC_BEGIN` -> `symex_atomic_begin(state)`
- `ATOMIC_END` -> `symex_atomic_end(state)`

Biến trạng thái quan trọng tại đây:

- `state.source.pc`: instruction hiện tại của thread hiện tại.
- `state.source.thread_nr`: id thread hiện tại.
- `state.threads`: vector trạng thái của toàn bộ thread.
- `state.guard`: guard path condition của thread hiện tại.
- `state.reachable`: thread/path còn sống không.
- `state.atomic_section_id`: thread hiện tại đang ở atomic section nào.

### 4.2 `symex_start_thread(...)`: bản chất của thao tác spawn

Trong `src/goto-symex/symex_start_thread.cpp`:

- Kiểm tra path có reachable không.
- Cấm spawn trong atomic section (`state.atomic_section_id != 0` -> throw).
- Ghi event spawn vào equation (`target.spawn(...)`).
- Lấy target của `START_THREAD` từ `instruction.get_target()`.
- Tạo thread mới:
    - `new_thread_nr = state.threads.size()`
    - `state.threads.push_back(...)`
    - set `new_thread.pc = thread_target`
    - copy thông tin guard/call stack frame cơ bản.
- Clone các local cần thiết sang namespace của thread mới theo cơ chế rename
  SSA L0/L1/L2.
- Khởi tạo biến `thread_local` static lifetime cho thread mới.

Các biến quan trọng nhất trong hàm này:

- `instruction`: instruction `START_THREAD` hiện tại.
- `thread_target`: entry instruction của thread mới.
- `new_thread_nr`: chỉ số thread mới trong `state.threads`.
- `frame`: stack frame hiện tại (dùng để biết local nào cần copy).
- `state.level1`, `path_storage`, rename levels: cơ chế SSA cho biến per-thread.

### 4.3 Scheduler trong symex (với nhiều thread)

Trong `symex_threaded_step(...)` (`src/goto-symex/symex_main.cpp`):

- Gọi `symex_step(...)` để chạy 1 instruction của thread hiện tại.
- Nếu thread hiện tại đã hết call stack và còn thread khác (`thread_nr + 1 < size`)
  thì `switch_to_thread(...)` sang thread kế tiếp.

`switch_to_thread(...)` lưu/khôi phục:

- `pc`, `atomic_section_id`, `guard`, `function_id` giữa thread cũ/mới.

Điểm này cho thấy interleaving ở mức symex state được quản lý bằng vector
`state.threads` + per-thread program counter.

---

## 5) Atomic section ảnh hưởng interleaving như thế nào

Trong `src/goto-symex/symex_atomic_section.cpp`:

- `symex_atomic_begin(state)`:
    - cấm nesting atomic,
    - set `state.atomic_section_id = ++atomic_section_counter`,
    - reset tập đọc/ghi trong atomic,
    - emit event `target.atomic_begin(...)`.

- `symex_atomic_end(state)`:
    - kiểm tra có begin tương ứng,
    - phát các shared read/write gom trong atomic,
    - emit event `target.atomic_end(...)`,
    - reset `state.atomic_section_id = 0`.

Thông tin được tích lũy để ràng buộc ordering ở phase memory model về sau.

---

## 6) Sau symex: tạo ràng buộc interleaving (partial order + memory model)

### 6.1 Điểm gọi memory model

Trong `src/goto-checker/bmc_util.cpp`,
`postprocess_equation(...)` kiểm tra `equation.has_threads()`:

- Nếu có threads -> tạo memory model theo option `--mm` (`sc`/`tso`/`pso`),
- rồi áp model đó lên equation (`(*memory_model)(equation, ...)`).

### 6.2 `partial_order_concurrency.cpp` xây event và clock constraints

Trong `src/goto-symex/partial_order_concurrency.cpp`:

- `build_event_lists(...)` duyệt `equation.SSA_steps`, thu các event:
    - shared read,
    - shared write,
    - spawn.
- Mỗi event được numbering theo thread (`counter[thread_nr]`).
- `clock(...)` sinh symbolic clock cho event.
- `before(e1, e2, axioms)` tạo constraint thứ tự:
    - nếu cùng `atomic_section_id != 0` -> clock bằng nhau,
    - ngược lại -> clock `<`.

Các biến lõi ở đây:

- `equation.SSA_steps`: danh sách event SSA đã symex sinh ra.
- `address_map`: map từ địa chỉ shared object -> tập read/write event.
- `numbering`: event -> chỉ số thứ tự per-thread.
- `clock_type`: kiểu bitvector của đồng hồ logic.

---

## 7) Các phân tích tĩnh liên quan threading

### 7.1 `is_threaded` analysis

`src/analyses/is_threaded.cpp`:

- transformer đánh dấu `is_threaded = true` từ điểm xuất hiện
  `from->is_start_thread()`.
- dùng để over-approximate vùng code chạy trong bối cảnh đa luồng.

### 7.2 Reaching definitions

`src/analyses/reaching_definitions.cpp`:

- tại `START_THREAD`, gọi `transform_start_thread(...)`.
- transfer function này loại bỏ các định nghĩa không-shared (và không-dirty)
  trước khi merge qua bối cảnh đa luồng.

---

## 8) Mapping chi tiết cho ví dụ ISR của bạn

Với ví dụ:

```c
__CPROVER_ASYNC_0: isr1(0);
task1();
task2();
assert(x == 5);
```

### 8.1 Sau goto conversion ở `main`

Xấp xỉ skeleton instruction:

1. `START_THREAD -> C`
2. `GOTO Z`
3. `C: SKIP`
4. `FUNCTION_CALL isr1(0)`
5. `END_THREAD`
6. `Z: SKIP`
7. `FUNCTION_CALL task1()`
8. `FUNCTION_CALL task2()`
9. `ASSERT(x == 5)`

### 8.2 Trong symex

- Tại (1): `symex_start_thread` tạo thread mới `T1` với `pc = C`.
- Thread hiện tại `T0` đi theo (2)->(6)->(7)->(8)->(9).
- `T1` chạy `isr1` và kết thúc tại `END_THREAD`.
- Vì `isr1` có `__CPROVER_atomic_begin/end`, các read/write của ISR được gom
  trong một atomic section event group.

### 8.3 Khi tạo constraint

- Shared accesses của `x` giữa `T0` và `T1` trở thành read/write events.
- Spawn event + clock constraints quyết định thứ tự hợp lệ theo `--mm`.
- Atomic section trong `isr1` chặn interleaving chen vào giữa begin/end tại
  mức ordering constraints.

---

## 9) Tóm tắt "hàm nào gọi hàm nào" cho nhánh `__CPROVER_ASYNC`

1. Frontend convert:
    - `goto_convertt::convert(...)`
    - `goto_convertt::convert_label(...)`
    - `goto_convertt::generate_thread_block(...)`

2. Symex execute:
    - `goto_symext::execute_next_instruction(...)`
    - case `START_THREAD` -> `goto_symext::symex_start_thread(...)`
    - case `ATOMIC_BEGIN/END` -> `goto_symext::symex_atomic_begin/end(...)`

3. Equation postprocess:
    - `postprocess_equation(...)` trong `bmc_util.cpp`
    - memory model (`partial_order_concurrency` và biến thể SC/TSO/PSO)

Chuỗi này là đường dữ liệu chính từ source `__CPROVER_ASYNC_*` đến bài toán SAT/SMT
có xét interleavings.
