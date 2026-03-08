#include <assert.h>

int main() {
  int x = 10;
  int y = 20;
  int z = x + y;

  // This should always hold
  assert(z == 30);

  return 0;
}