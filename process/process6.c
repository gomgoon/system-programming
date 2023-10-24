#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    pid_t pid;

    // 현재 프로세스의 PID 출력
    printf("before fork(): %d\n", getpid());

    // fork() 함수를 사용하여 자식 프로세스를 생성
    if ((pid = fork()) < 0) {
        perror("error in fork()\n"); // fork() 호출 오류 처리
    } else if (pid == 0) {
        // 자식 프로세스인 경우
        printf("hi! it's a child (%d -> %d)\n", getppid(), getpid());
    } else {
        // 부모 프로세스인 경우
        printf("hi! it's a parent (%d)\n", getpid());
    }

    // 부모와 자식 프로세스 모두에서 실행
    printf("after fork(): who called this? %d\n", getpid());

    exit(EXIT_SUCCESS); // 프로그램 정상 종료
}

