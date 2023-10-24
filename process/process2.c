#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int pid; // 정수형 변수 선언

    // getpid() 함수를 사용하여 현재 프로세스의 PID(프로세스 식별자)를 가져옴
    pid = getpid();

    // 현재 프로세스의 PID를 출력
    printf("this process's pid: %d\n", pid);

    return 0; // 프로그램 종료
}

