#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ours.h" // 사용자 정의 헤더 파일을 포함

int n_system(const char *cmd) {
    pid_t pid;
    int status;

    if (cmd == NULL)
        return 1; // 신호 관리 없음

    if ((pid = fork()) < 0)
        status = -1; // fork() 오류
    else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd, NULL);
        _exit(127); // execl() 오류
    } else {
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1; // 일반적인 오류
                break;
            }
        }
    }

    return status;
}

char *cmd = "grep hurryon /etc/passwd | cut -f 5 -d:";

int main(void) {
    int status;

    // n_system() 함수를 사용하여 쉘 명령어 실행
    if ((status = n_system(cmd)) == -1)
        perror("n_system() error");

    // 실행 결과의 종료 상태 출력
    print_exit(status);

    exit(EXIT_SUCCESS);
}

