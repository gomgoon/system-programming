#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    printf("executing ls\n");

    // execl 함수를 사용하여 /bin/ls 프로그램 실행
    execl("/bin/ls", "ls", "-l", (char *)0);

    // execl 함수는 실행에 실패하면 아래 코드가 실행됨
    perror("execl() failed\n");

    return 0; // 프로그램 종료
}

