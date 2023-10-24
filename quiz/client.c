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
    int fd;
    int currentValue = 1;  // 시작값 설정

    // Check if FIFO already exists
    if (access(FIFO_NAME, F_OK) == -1) {
        if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
            perror("mknod error");
        }
    }

    printf("Client: 서버를 기다립니다.\n");
    fd = open(FIFO_NAME, O_RDWR);
    printf("Client: 서버가 준비되었습니다.\n");

    while (1) {
        sprintf(buf, "%d", currentValue);
        write(fd, buf, strlen(buf));

        read(fd, buf, sizeof(buf));
        sscanf(buf, "%d", &currentValue);
        printf("Client: Server Response: %d\n", currentValue);

        sleep(1);
    }

    close(fd);
    return 0;
}

