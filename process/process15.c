/* print-env.c */
#include <stdio.h>
#include <stdlib.h>

// environ 변수를 사용하기 위해 extern 선언
extern char **environ;

int main(int argc, char *argv[]) {
    int i;

    // 커맨드 라인 인수 출력
    for (i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    // 환경 변수 출력
    char **ptr;
    for (ptr = environ; *ptr != NULL; ptr++) {
        printf("%s\n", *ptr);
    }

    exit(EXIT_SUCCESS);
}

