**I. Introduction** (Dựa vào tài liệu Introduction.pdf)
- Nêu bài toán chính: kiểm chứng chương trình C/embedded/OSEK có **scheduler, OS API, ISR/interleaving**.
- Vì sao khó: CBMC mạnh cho C/C++ bình thường, nhưng OSEK API như `ActivateTask`, `SetEvent`, `WaitEvent`, scheduler, ISR không nên bị xem như function call thường.
- Vấn đề hiện tại: nếu mô hình hóa interrupt/interleaving quá rộng thì sinh nhiều điểm chen ISR, tốn tài nguyên hoặc khó tái lập; nếu bỏ qua scheduler/API thì kết quả thiếu chính xác.
- Mục tiêu project: mở rộng/điều chỉnh flow CBMC để hiểu tốt hơn OS API/OSEK và materialize ISR/interleaving theo manifest.
- Đóng góp kỹ thuật:
  + Tích hợp option OS OSEK vào CBMC.
  + Pipeline handle ISR/interleaving tối ưu hơn.
  + Benchmark/evidence để xem pipeline chạy được đến đâu.

**II. Background** (Dựa vào tài liệu Background.pdf)
- Giới thiệu OSEK/VDK Application, nói về đặc điểm (API và Scheduler).
- Giới thiệu Model Checking là gì. Thế nào là Bounded Model Checking.
- CBMC/BMC: CBMC biến chương trình C/C++ thành GOTO program, symbolic execution, rồi kiểm tra bằng SAT/SMT; nếu lỗi thì xuất counterexample trace. Xem flow kiến trúc ở https://diffblue.github.io/cbmc/cbmc-architecture.html.
- Model checking cho OSEK.
- ISR/interleaving:
  - ISR là luồng bất đồng bộ có thể đọc/ghi shared global state.
  - Verification phải xét khả năng ISR xảy ra tại các điểm liên quan, nhưng cần tránh chèn quá nhiều điểm không cần thiết.
- 3 phương pháp giải quyết phổ biến (Dựa vào tài liệu và source code của mình):
  + Spin based.
  + SMT based (Cách làm của mình tương đương phương pháp này, nhưng vẫn có nhiều điểm khác, hãy chỉ ra điểm khác):
    Trong tài liệu: model được lấy từ phương pháp spin.
    Source code của mình: model tự xây ra riêng (dựa trên đặc điểm của OSEK). Tích hợp OSEK vào CBMC.
  + Sequentialization based.

**III. Method**
- CBMC gốc làm những gì (Sử dụng __CPROVER_ASYNC -> behavior như thế nào).
- Source code của mình mô hinh hóa và cải tiển như thế nào.
- Trình bày flow chính bằng các bước `B1, B2, B3...`, tự vẽ lại theo kiến trúc CBMC:
  + `B1`: Input project: source C, harness, OIL, danh sách ISR/task/event files.
  + `B2`: Build/load GOTO model bằng `goto-cc` hoặc `goto-instrument`.
  + `B3`: Trong symbolic execution, phát hiện OS API call.
  + `B4`: OS API dispatcher chuyển call sang OSEK backend.
  + `B5`: OSEK backend cập nhật scheduler/event/task state.
  + `B6`: Interleaving analysis duyệt ISR functions, tìm global variables ISR ghi.
  + `B7`: Duyệt foreground code, tìm dòng đọc/ghi các global đó.
  + `B8`: Xuất manifest JSON gồm file, line, function, variable, ISR liên quan.
  + `B9`: `aib` đọc manifest và chèn guarded call kiểu `if (nondet_bool()) isr(...);`.
  + `B10`: Compile source đã rewrite và chạy CBMC verification.
- Nhấn mạnh “thay đổi flow như thế nào”.
- Nên có hình tự vẽ:
  + Original CBMC flow.
  + Modified flow của project.
  + Vị trí các module mới: dispatcher, OSEK backend, manifest exporter, `aib` injector.