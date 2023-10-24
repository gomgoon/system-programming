#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;

    // 명령줄 인수를 반복하면서 출력
    for (i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    exit(EXIT_SUCCESS); // 프로그램 정상 종료
}

