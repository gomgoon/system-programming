#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int pfd[2];
    char buf[30];

    // 파이프를 생성합니다.
    if (pipe(pfd) == -1) {
        perror("pipe error");
        exit(1);
    }

    // 자식 프로세스를 생성합니다.
    if (!fork()) {
        printf("자식 프로세스(PID: %d): 파이프로 쓰기 중\n", getpid());

        // 파이프에 데이터를 씁니다.
        write(pfd[1], "pipe!", 5);

        // 자식 프로세스 종료
        exit(0);
    } else {
        printf("부모 프로세스(PID: %d): 파이프로부터 읽기 중\n", getpid());

        // 파이프로부터 데이터를 읽어옵니다.
        read(pfd[0], buf, 5);

        printf("부모 프로세스(PID: %d): %s\n", getpid(), buf);

        // 자식 프로세스 종료를 기다립니다.
        wait(NULL);
    }

    return 0;
}

