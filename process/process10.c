#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ours.h" // 사용자 정의 헤더 파일을 포함

int main(void) {
    pid_t pid;
    int status;

    // 첫 번째 자식 프로세스 생성
    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        exit(7); // 자식 프로세스 종료 (정상 종료)
    }

    // 첫 번째 자식 프로세스의 종료 상태 출력
    if (wait(&status) != pid) {
        perror("wait error");
    }
    print_exit(status); // 종료 상태 출력

    // 두 번째 자식 프로세스 생성
    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        abort(); // 자식 프로세스를 비정상적으로 종료 (시그널로)
    }

    // 두 번째 자식 프로세스의 종료 상태 출력
    if (wait(&status) != pid) {
        perror("wait error");
    }
    print_exit(status); // 종료 상태 출력

    // 세 번째 자식 프로세스 생성
    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        status /= 0; // 0으로 나누어 에러 유발 (비정상 종료)
    }

    // 세 번째 자식 프로세스의 종료 상태 출력
    if (wait(&status) != pid) {
        perror("wait error");
    }
    print_exit(status); // 종료 상태 출력

    exit(EXIT_SUCCESS); // 프로그램 정상 종료
}

