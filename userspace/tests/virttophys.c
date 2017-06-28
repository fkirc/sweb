#include "stdio.h"
#include <sys/syscall.h>
#include "../../../common/include/kernel/syscall-definitions.h"


int main() {

    int local_var = 0;
    int* vaddr = &local_var;

    size_t physadd = __syscall(sc_virt_to_phys, (size_t)vaddr, 0, 0, 0, 0);

    size_t vadd = (size_t)vaddr;
    printf("page offset: %zx\n", vadd & 0xFFF);
    printf("pti: %zx\n", (vadd >> 12) & 0xFFF);
    printf("pdi: %zx\n", (vadd >> 21)  & 0xFFF);
    printf("pdpti: %zx\n", (vadd >> 30)  & 0xFFF);
    printf("pml4i: %zx\n", (vadd >> 39)  & 0xFFF);


    printf("Vaddr: %p\n", vaddr);
    printf("ppn: %d\n", (int)physadd / 4096);

}

