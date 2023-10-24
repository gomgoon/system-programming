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
    int receivedNumber, result;

    // Check if FIFO already exists
    if (access(FIFO_NAME, F_OK) == -1) {
        if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
            perror("mknod error");
        }
    }

    printf("Server: 클라이언트를 기다립니다.\n");

    fd = open(FIFO_NAME, O_RDWR);  // Use O_RDWR to keep it open for both reading and writing
    printf("Server: 클라이언트가 준비되었습니다.\n");

    while (1) {
        if ((num = read(fd, buf, sizeof(buf))) == -1) {
            perror("read error");
            break;
        }
        buf[num] = '\0';
        sscanf(buf, "%d", &receivedNumber);
        result = receivedNumber + 1;
        printf("Server: Received %d, Sending %d\n", receivedNumber, result);
        sprintf(buf, "%d", result);
        write(fd, buf, strlen(buf));
	sleep(1);
    }

    close(fd);
    unlink(FIFO_NAME);
    return 0;
}

