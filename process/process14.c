#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    pid = fork(); // 자식 프로세스 생성

    switch (pid) {
        case -1:
            perror("fork() failed\n"); // fork 실패 시 오류 출력
            break;
        case 0: // 자식 프로세스
            printf("child: execl() executing ls beginning\n");
            execl("/bin/ls", "ls", "-l", (char *)0); // /bin/ls -l 실행
            perror("execl() failed\n"); // execl 실행 실패 시 오류 출력
            break;
        default: // 부모 프로세스
            wait((int *)0); // 부모는 자식 프로세스가 종료될 때까지 기다림
            printf("parent: execl() executing ls completed\n");
            exit(0); // 부모 프로세스 종료
    }

    return 0; // 프로그램 종료
}

