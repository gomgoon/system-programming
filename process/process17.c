#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "ours.h" // 사용자 정의 헤더 파일을 포함

// 실행할 쉘 명령어
char *cmd = "grep hurryon /etc/passwd | cut -f 5 -d:";

int main(void) {
    int status;

    // system() 함수를 사용하여 쉘 명령어 실행
    if ((status = system(cmd)) == -1) {
        perror("system() error");
    }

    // 실행 결과의 종료 상태 출력
    print_exit(status);

    exit(EXIT_SUCCESS);
}

