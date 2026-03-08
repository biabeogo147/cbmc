#include <assert.h>

int main() {
  int x = 0;
  // ESBMC sẽ báo lỗi vì assert sai
  assert(x == 1);
  return 0;
}
