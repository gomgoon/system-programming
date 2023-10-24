#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "ours.h" // 사용자 정의 헤더 파일을 포함

char *env_init[] = {"USER=unknown", "TERM=xterm", NULL};
char first[] = "=== first fork() child ===\n";
char second[] = "=== second fork() child ===\n";

int main(void) {
    pid_t pid;

    // 첫 번째 fork()
    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        // 자식 프로세스 (첫 번째 fork)
        write(STDOUT_FILENO, first, strlen(first));

        // execle 함수로 다른 프로그램 실행
        if (execle("./print-env", "print-env", "jong-hyouk", "lee", NULL, env_init) < 0) {
            perror("execle error");
        }
    }

    // 부모 프로세스
    // 자식 프로세스가 종료될 때까지 대기
    if (wait(NULL) < 0) {
        perror("wait error");
    }

    // 두 번째 fork()
    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        // 자식 프로세스 (두 번째 fork)
        write(STDOUT_FILENO, second, strlen(second));

        // execlp 함수로 다른 프로그램 실행
        if (execlp("./print-env", "print-env", "one argument", NULL) < 0) {
            perror("execlp error");
        }
    }

    exit(EXIT_SUCCESS);
}

