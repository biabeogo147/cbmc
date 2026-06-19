**I. Introduction**
- Nêu bài toán chính: kiểm chứng chương trình C/embedded/OSEK có **scheduler, OS API, ISR/interleaving**.
- Vì sao khó: CBMC mạnh cho C/C++ bình thường, nhưng OSEK API như `ActivateTask`, `SetEvent`, `WaitEvent`, scheduler, ISR không nên bị xem như function call thường.
- Vấn đề hiện tại: nếu mô hình hóa interrupt/interleaving quá rộng thì sinh nhiều điểm chen ISR, tốn tài nguyên hoặc khó tái lập; nếu bỏ qua scheduler/API thì kết quả thiếu chính xác.
- Mục tiêu project: mở rộng/điều chỉnh flow CBMC để hiểu tốt hơn OS API/OSEK và materialize ISR/interleaving theo manifest.
- Đóng góp kỹ thuật:
  - OS API dispatcher cho OSEK API.
  - OSEK backend mô hình hóa task/event/scheduler từ OIL.
  - Pipeline phân tích ISR/interleaving, xuất manifest, rồi chèn `nondet` ISR call bằng tool `aib`.
  - Benchmark/evidence để xem pipeline chạy được đến đâu.

**II. Background**
- CBMC/BMC: CBMC biến chương trình C/C++ thành GOTO program, symbolic execution, rồi kiểm tra bằng SAT/SMT; nếu lỗi thì xuất counterexample trace. Xem flow kiến trúc ở [CBMC Architecture](https://diffblue.github.io/cbmc/cbmc-architecture.html).
- GOTO IR và các tool chính:
  - `goto-cc`: build GOTO binary/program.
  - `goto-instrument`: instrumentation/transformation.
  - `cbmc`: symbolic execution + verification.
- OSEK/VDX:
  - Task, priority, event, resource, scheduler.
  - OS API ảnh hưởng trực tiếp đến trạng thái runnable/current task.
  - OIL chứa metadata cấu hình hệ thống.
- Model checking cho OSEK:
  - Dẫn nhẹ thesis JAIST của Zhang Haitao về model checking OSEK/VDX, nhất là ý: scheduler deterministic và API làm thay đổi scheduling nên cần được mô hình hóa riêng. Nguồn: [JAIST thesis page](https://dspace.jaist.ac.jp/dspace/handle/10119/12964?locale=ja).
- ISR/interleaving:
  - ISR là luồng bất đồng bộ có thể đọc/ghi shared global state.
  - Verification phải xét khả năng ISR xảy ra tại các điểm liên quan, nhưng cần tránh chèn quá nhiều điểm không cần thiết.

**III. Method**
- Trình bày flow chính bằng các bước `B1, B2, B3...`, tự vẽ lại theo kiến trúc CBMC:
  - `B1`: Input project: source C, harness, OIL, danh sách ISR/task/event files.
  - `B2`: Build/load GOTO model bằng `goto-cc` hoặc `goto-instrument`.
  - `B3`: Trong symbolic execution, phát hiện OS API call.
  - `B4`: OS API dispatcher chuyển call sang OSEK backend.
  - `B5`: OSEK backend cập nhật scheduler/event/task state.
  - `B6`: Interleaving analysis duyệt ISR functions, tìm global variables ISR ghi.
  - `B7`: Duyệt foreground code, tìm dòng đọc/ghi các global đó.
  - `B8`: Xuất manifest JSON gồm file, line, function, variable, ISR liên quan.
  - `B9`: `aib` đọc manifest và chèn guarded call kiểu `if (nondet_bool()) isr(...);`.
  - `B10`: Compile source đã rewrite và chạy CBMC verification.
- Nhấn mạnh “thay đổi flow như thế nào”:
  - Thêm nhánh **OS API-aware symbolic execution** trong `goto-symex`.
  - Thêm **OSEK backend** cho scheduler/event semantics.
  - Thêm **manifest-guided interleaving pipeline** trước bước verify cuối.
- Nên có hình tự vẽ:
  - Original CBMC flow.
  - Modified flow của project.
  - Vị trí các module mới: dispatcher, OSEK backend, manifest exporter, `aib` injector.