/* ours.h */

// 필요한 헤더 파일을 포함
#include <stdio.h>
#include <sys/wait.h>

// 종료 상태를 출력하는 함수
void print_exit(int status) {
    if (WIFEXITED(status)) {
        // 정상 종료한 경우
        printf("normal, exit status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        // 시그널에 의해 종료된 경우
        printf("abnormal, signal number = %d\n", WTERMSIG(status));
    }
}

