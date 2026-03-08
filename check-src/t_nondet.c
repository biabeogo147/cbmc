#include <assert.h>

// ESBMC cung cấp các hàm nondet này
int __VERIFIER_nondet_int(void);

int main() {
    int x = __VERIFIER_nondet_int();

    // giả sử điều kiện đầu vào
    if (x >= 0 && x <= 10) {
        // property đúng
        assert(x + 1 >= 1);

        // property sai (để thấy ESBMC tìm counterexample)
        assert(x != 5);
    }
    return 0;
}
