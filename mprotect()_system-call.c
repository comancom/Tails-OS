#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

int main() {
    size_t page_size = sysconf(_SC_PAGESIZE);
    void *mem = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    strcpy((char *)mem, "Tails Test");
    printf("Before mprotect: %s\n", (char *)mem);

    if (mprotect(mem, page_size, PROT_READ) == -1) {
        perror("mprotect");
        return 1;
    }

    printf("After mprotect: %s\n", (char *)mem);
    munmap(mem, page_size);
    return 0;
}
