#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(void) {
    int pfd[2]; // 파이프 디스크립터
    char buf[30];

    /* 두 개의 파이프를 생성합니다. */
    if (pipe(pfd) == -1) {
        perror("pipe error");
        exit(1);
    }

    /* pfd[1]은 쓰기용입니다. */
    printf("파일 디스크립터 #%d로 쓰기 중\n", pfd[1]);
    write(pfd[1], "pipe!", 5);

    /* pfd[0]은 읽기용입니다. */
    printf("파일 디스크립터 #%d로부터 읽기 중\n", pfd[0]);
    read(pfd[0], buf, 5);

    printf("%s\n", buf);

    return 0;
}

