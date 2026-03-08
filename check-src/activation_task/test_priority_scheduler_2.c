#include <assert.h>

// ESBMC intrinsics
extern unsigned int __ESBMC_activation_task(const char *task_id, void (*func)(void));

// Shared state (giống kiểu ECU / embedded)
int brake_request = 0;     // 1 = có yêu cầu phanh
int safety_ok = 0;         // 1 = safety check đã pass
int brake_applied = 0;     // 1 = actuator đã apply phanh
int infotainment_tick = 0; // nhiễu nền (low priority)
int log_counter = 0;

// Low priority - chỉ tạo nhiễu và nhiều điểm interleaving
void infotainment(void)
{
  for (int i = 0; i < 5; ++i)
  {
    infotainment_tick++;
  }
  // Không được đụng safety_ok/brake_applied theo yêu cầu "domain separation"
  assert(safety_ok == 0 || safety_ok == 1);
}

// Medium priority - actuator chỉ được phép chạy khi safety_ok==1
void brake_actuator(void)
{
  // actuator KHÔNG được apply nếu chưa safety check
  assert(safety_ok == 1);

  // mô phỏng apply phanh
  brake_applied = 1;

  // sau khi apply thì phải có brake_request
  assert(brake_request == 1);
}

// High priority - safety check phải chạy trước actuator
void safety_check(void)
{
  // chờ có request phanh
  assert(brake_request == 1);

  // mô phỏng một chuỗi check
  safety_ok = 1;

  // nếu safety_ok=1 thì brake_applied có thể 0 hoặc 1 (tùy actuator đã chạy chưa)
  assert(brake_applied == 0 || brake_applied == 1);

  // nested activation: spawn logger (low priority)
  __ESBMC_activation_task("logger", /*low prio*/ infotainment);
}

// Controller - kích hoạt hệ thống
void controller(void)
{
  // phát sinh yêu cầu phanh
  brake_request = 1;

  // spawn nhiều task
  __ESBMC_activation_task("infotainment", infotainment);
  __ESBMC_activation_task("safety", safety_check);
  __ESBMC_activation_task("actuator", brake_actuator);

  // cuối cùng: nếu đã apply phanh thì safety_ok bắt buộc phải là 1
  if (brake_applied)
    assert(safety_ok == 1);
}

int main(void)
{
  __ESBMC_activation_task("controller", controller);
  return 0;
}