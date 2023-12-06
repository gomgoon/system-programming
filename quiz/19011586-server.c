/* 19011586-server.c */
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
        // FIFO에서 데이터 읽기
        if ((num = read(fd, buf, sizeof(buf))) == -1) {
            perror("read error");  // 읽기 에러 발생 시 메시지 출력
            break;  // 에러 발생 시 무한루프 종료
        }
        buf[num] = '\0';  // 문자열의 끝을 표시
        // 문자열로 받은 데이터를 정수로 변환
        sscanf(buf, "%d", &receivedNumber);
        // 받은 숫자에 1을 더함
        result = receivedNumber + 1;
        // 결과 출력
        printf("%d+1 = %d\n", receivedNumber, result);
        // 결과를 문자열로 변환하여 버퍼에 저장
        sprintf(buf, "%d", result);
        // 변환한 문자열을 FIFO로 전송
        write(fd, buf, strlen(buf));
        // 1초 동안 대기
        sleep(1);
    }

    // FIFO 파일 닫기
    close(fd);
    // FIFO 파일 삭제
    unlink(FIFO_NAME);
    return 0;
}

