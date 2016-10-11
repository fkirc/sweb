#include "../../../common/include/kernel/syscall-definitions.h"
#include "stdio.h"
#include <sys/syscall.h>

int main() {

    int local_var = 0;
    size_t vaddr = (size_t)&local_var;
    printf("vaddr: %x\n", (int)vaddr);

    printf("page offset: %x\n", (int)(vaddr & 0xFFF));
    printf("pti: %x\n", (int)(vaddr >> 12) & 0x1FF);
    printf("pdi: %x\n", (int)(vaddr >> 21) & 0x1FF);
    printf("pdpti: %x\n", (int)(vaddr >> 30) & 0x1FF);
    printf("pml4i: %x\n", (int)(vaddr >> 39) & 0x1FF);

    size_t physaddr = __syscall(sc_virt_phys_lookup, vaddr, 0, 0, 0, 0);
    printf("physaddr: %x\n", (int)physaddr);
    printf("physical page: %d\n", (int)physaddr / 4096);
}
