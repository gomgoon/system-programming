#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(void) {
    int len = 1024 * 1024; // 1MB
    void *addr = mmap((void *)0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

    if (addr == MAP_FAILED) {
        perror("mmap() error");
        exit(1);
    }

    int *buf = (int *)addr; /* mmap'd 영역을 int 포인터로 변환 */
    buf[3] = 7;
    buf[2] = buf[3];
    
    printf("mmap returned %p, which seems readable and writable\n", addr);
    printf("data in memory: %d\n", buf[0]);
    printf("data in memory: %d\n", buf[1]);
    printf("data in memory: %d\n", buf[2]);
    printf("data in memory: %d\n", buf[3]);
    printf("data in memory: %d\n", buf[4]);

    munmap(addr, len); // 가상 메모리에서 물리 메모리 매핑을 제거

    return 0;
}

