#include "stdio.h"
#include "types.h"

int global_var = 100;

int main() {

    size_t s_small = 0x12;
    size_t s_large = 0xFFFF0000000000AAULL;

    int x = 5;
    int y = -20;

    printf("stack: %p data: %p\n", &s_small, &global_var);
    printf("s_small signed and hexadezimal: %zd = %zx\n", s_small, s_small);
    printf("s_large pointer and hexadezimal: %p = %zx\n", (void*)s_large, s_large);
    printf("s_large unsigned and signed: %zu = %zd\n", s_large, s_large);
    printf("int positive: %d = %x\n", x, x);
    printf("int negative: %d = %u = %x\n", y, y, y);
}