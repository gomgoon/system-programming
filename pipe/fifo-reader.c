#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "FIFO_FD"

int main(void) {
    char buf[100];
    int num, fd;

    /* FIFO 파일을 생성 (이미 존재한다면 무시) */
    if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
        perror("mknod error");
    }

    /* 라이터(데이터를 쓰는 프로세스)를 기다립니다. */
    /* 라이터가 FIFO 파일을 열 때까지 대기합니다. */
    printf("Reader: 라이터를 기다립니다.\n");

    /* FIFO 파일을 읽기 전용으로 엽니다. */
    fd = open(FIFO_NAME, O_RDONLY);

    printf("Reader: 라이터가 준비되었습니다.\n");

    /* FIFO를 통해 라이터로부터 전송된 데이터를 수신합니다. */
    do {
        if ((num = read(fd, buf, sizeof(buf))) == -1) {
            perror("read error");
        } else {
            buf[num] = '\0';
            printf("Reader: %d 바이트 읽음: %s", num, buf);
        }
    } while (num > 0);

    /* 프로그램 종료 */
    return 0;
}

