#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(void) {
    int *addr;
    
    // mmap을 사용하여 공유 메모리를 할당합니다.
    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    if (addr == MAP_FAILED) {
        perror("mmap() error");
        exit(1);
    }
    
    // 메모리에 값 42를 저장합니다.
    *addr = 42;
    
    switch (fork()) {
        case -1:
            perror("fork() error");
            break;
        
        // 자식 프로세스
        case 0:
            // 자식 프로세스가 메모리의 값을 읽고 출력합니다.
            printf("child: %d\n", *addr);
            // 메모리의 값을 증가시킵니다.
            (*addr)++;
            break;
        
        // 부모 프로세스
        default:
            // 부모 프로세스는 자식 프로세스가 종료될 때까지 대기합니다.
            if (wait(NULL) == -1) {
                perror("wait() error");
                exit(1);
            }
            // 메모리의 값을 읽고 출력합니다.
            printf("parent: %d\n", *addr);
    }
    
    exit(EXIT_SUCCESS);
}

