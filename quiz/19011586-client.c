/* 19011596-client.c */

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
    int currentValue = 1;  // 클라이언트가 시작할 때 사용할 숫자 값을 설정

    // FIFO 파일이 이미 존재하는지 확인
    if (access(FIFO_NAME, F_OK) == -1) {
        // FIFO 파일이 존재하지 않을 경우 생성
        if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
            perror("mknod error");  // 에러 메시지 출력
        }
    }

    // FIFO 파일을 읽기/쓰기 모드로 열기
    fd = open(FIFO_NAME, O_RDWR);

    while (1) {
        // 현재 숫자 값을 문자열로 변환하여 버퍼에 저장
        sprintf(buf, "%d", currentValue);
        // 변환된 문자열을 FIFO에 쓰기
        write(fd, buf, strlen(buf));

        // 서버로부터 응답 받기
        read(fd, buf, sizeof(buf));
        // 받은 응답을 정수로 변환
        sscanf(buf, "%d", &currentValue);
        // 변환된 정수 값을 출력
        printf("%d\n", currentValue);

        // 1초 동안 대기
        sleep(1);
    }

    // FIFO 파일 닫기
    close(fd);
    return 0;
}

