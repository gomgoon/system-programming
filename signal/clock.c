#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

/* 시간이 변경될 때마다 호출되는 시그널 핸들러 함수 */
void clock_tick(int signo) {
    printf("\r%ld", time(NULL)); /* 이전 시간을 현재 시간으로 덮어씁니다. */
    alarm(1); /* 1초마다 alarm 재설정 */
}

int main(void) {
    /* 표준 출력의 버퍼링을 비활성화하여 실시간 업데이트를 지원합니다. */
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    
    /* ANSI 이스케이프 시퀀스를 사용하여 화면을 지웁니다. */
    printf("\e[2J\e[H"); /* 홈으로 이동하고 화면 지우기 */

    /* SIGALRM 시그널을 처리하는 핸들러를 등록합니다. */
    if (signal(SIGALRM, clock_tick) == SIG_ERR)
        perror("SIGALRM 시그널을 처리할 수 없음");

    clock_tick(1); /* 초기 시간을 표시합니다. */
    alarm(1); /* 1초마다 alarm 설정 */

    for (;;) {
        pause(); /* 시그널을 대기합니다. */
    }

    exit(EXIT_SUCCESS);
}

