#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "FIFO_FD"

int main(void) {
    char buf[100];
    int num, fd;
    int inputValue;

    // Check if FIFO already exists
    if (access(FIFO_NAME, F_OK) == -1) {
        if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
            perror("mknod error");
        }
    }

    printf("Client: 서버를 기다립니다.\n");

    fd = open(FIFO_NAME, O_RDWR);  // Use O_RDWR to keep it open for both reading and writing
    printf("Client: 서버가 준비되었습니다.\n");

    while (1) {
        printf("Client: 숫자를 입력하세요 (종료하려면 음수): ");
        scanf("%d", &inputValue);

        if (inputValue < 0) break;

        sprintf(buf, "%d", inputValue);
        write(fd, buf, strlen(buf));

        read(fd, buf, sizeof(buf));
        printf("Client: Server Response: %s\n", buf);
    }

    close(fd);
    return 0;
}

