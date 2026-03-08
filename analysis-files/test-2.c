#include <assert.h>

int main() {
  int x = 10;
  int y = 20;
  int z = x + y;

  // This is false
  assert(z == 40);

  return 0;
}
