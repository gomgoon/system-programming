#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int status;

    // fork() 함수를 사용하여 자식 프로세스를 생성
    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        // 자식 프로세스인 경우
        printf("hi from child\n");
        exit(7);
    } else {
        // 부모 프로세스인 경우

        // 부모는 자식 프로세스의 종료를 기다림
        if (wait(&status) != pid) {
            perror("wait error");
        }
        printf("hi from parent\n");

        // 자식 프로세스가 정상 종료했을 경우
        if (WIFEXITED(status)) {
            printf("normal, exit status = %d\n", WEXITSTATUS(status));
        }
        // 자식 프로세스가 시그널에 의해 종료되었을 경우
        else if (WIFSIGNALED(status)) {
            printf("abnormal, signal number = %d\n", WTERMSIG(status));
        }
    }

    exit(EXIT_SUCCESS);
}

