#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ours.h" // 사용자 정의 헤더 파일을 포함

int main(void) {
    pid_t pid;
    int i;

    // 5번의 반복으로 자식 프로세스 생성
    for (i = 0; i < 5; i++) {
        if ((pid = fork()) < 0) {
            perror("fork error");
        } else if (pid == 0) {
            // 자식 프로세스인 경우
            printf("child %d: %d\n", i, getpid());
            exit(EXIT_SUCCESS); // 자식 프로세스 종료
        }
        // 부모 프로세스는 반복하면서 자식 프로세스 생성
    }

    // 자식 프로세스들이 생성되는 동안 잠시 대기
    sleep(30);

    printf("bye from parent\n");
    exit(EXIT_SUCCESS); // 부모 프로세스 종료
}

