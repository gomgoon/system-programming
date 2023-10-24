#include <stdio.h>
#include <stdlib.h>

// 환경 변수를 저장하는 배열
extern char **environ;

int main(void) {
    int i;

    // environ 배열을 반복하면서 환경 변수를 출력
    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    exit(EXIT_SUCCESS); // 프로그램 정상 종료
}

