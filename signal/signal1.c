#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* 시그널 핸들러 함수 */
static void sig_usr(int signo) {
    if (signo == SIGUSR1)
        printf("SIGUSR1 시그널을 받음\n");
    else if (signo == SIGUSR2)
        printf("SIGUSR2 시그널을 받음\n");
}

int main(void) {
    /* SIGUSR1 및 SIGUSR2 시그널을 처리하는 핸들러를 등록합니다. */
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        perror("SIGUSR1 시그널을 처리할 수 없음");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        perror("SIGUSR2 시그널을 처리할 수 없음");

    /* 무한 루프에서 시그널을 기다립니다. */
    for (;;) {
        sleep(60);
    }

    return 0;
}

