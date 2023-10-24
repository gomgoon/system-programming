#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int pfd[2];

    // 파이프를 생성합니다.
    if (pipe(pfd) == -1) {
        perror("pipe error");
        exit(1);
    }

    // 자식 프로세스를 생성합니다.
    if (!fork()) {
        close(1); // stdout (화면 출력)를 닫습니다.
        dup(pfd[1]); // stdout (화면 출력)를 파이프 입력으로 연결합니다.
        close(pfd[0]);
        // 이제 ls 명령어의 결과가 파이프 입력으로 전달됩니다.
        execlp("ls", "ls", NULL);
    } else {
        close(0); // stdin (키보드 입력)를 닫습니다.
        dup(pfd[0]); // stdin을 파이프 출력으로 연결합니다.
        close(pfd[1]);
        // 파이프 출력이 wc 명령어의 입력으로 전달됩니다.
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}

