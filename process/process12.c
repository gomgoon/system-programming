#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ours.h" // 사용자 정의 헤더 파일을 포함

char buf[] = "write to stdout\n";

int main(void) {
    pid_t pid;

    // 문자열을 표준 출력에 출력
    if (write(STDOUT_FILENO, buf, strlen(buf)) != strlen(buf)) {
        perror("write error");
    }

    printf("printf by %d: before fork\n", getpid());

    // fork() 함수를 사용하여 자식 프로세스 생성
    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        // 자식 프로세스인 경우
        printf("printf by %d: hi from child!\n", getpid());
    } else {
        // 부모 프로세스인 경우
        printf("printf by %d: hi from parent!\n", getpid());
    }

    printf("printf by %d: bye\n", getpid());

    exit(EXIT_SUCCESS); // 프로그램 정상 종료
}

