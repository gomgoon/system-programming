#include <stdlib.h>
#include <unistd.h>
#include "ours.h" // 사용자 정의 헤더 파일을 포함

void print_c(char *str) {
    char *ptr;
    int c;

    // 출력 버퍼를 비워서 즉시 출력되도록 설정
    setbuf(stdout, NULL);

    // 문자열을 순회하면서 출력
    for (ptr = str; (c = *ptr++) != 0; ) {
        putc(c, stdout);
    }
}

int main(void) {
    pid_t pid;

    // 자식 프로세스 생성
    if ((pid = fork()) < 0) {
        perror("fork() error");
    } else if (pid == 0) {
        // 자식 프로세스에서 문자열 출력
        print_c("output from child\n");
    } else {
        // 부모 프로세스에서 문자열 출력
        print_c("output from parent\n");
    }

    exit(EXIT_SUCCESS);
}

