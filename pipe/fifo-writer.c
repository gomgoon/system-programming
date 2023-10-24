#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#define FIFO_NAME "FIFO_FD"

int main(void) {
    char buf[100];
    int num, fd;

    /* FIFO 파일을 생성 (이미 존재한다면 무시) */
    if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
        perror("mknod error");
    }

    /* 리더(데이터를 읽는 프로세스)를 기다립니다. */
    /* 리더가 FIFO 파일을 열 때까지 대기합니다. */
    printf("Writer: 리더를 기다립니다.\n");

    /* FIFO 파일을 쓰기 전용으로 엽니다. */
    fd = open(FIFO_NAME, O_WRONLY);

    printf("Writer: 리더가 준비되었습니다.\n");
    printf("Writer: 입력하세요: ");

    /* 사용자 입력 데이터를 FIFO를 통해 리더로 전송합니다. */
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        /* 데이터를 FIFO에 씁니다. */
        if ((num = write(fd, buf, strlen(buf))) == -1) {
            perror("write error");
        } else {
            printf("Writer: %d 바이트를 썼습니다.\n", num);
        }
    }

    /* 프로그램 종료 */
    return 0;
}

