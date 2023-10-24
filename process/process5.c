#include <stdio.h>
#include <stdlib.h>

// 첫 번째 종료 핸들러
void my_exit1(void) {
    printf("first exit handler\n");
}

// 두 번째 종료 핸들러
void my_exit2(void) {
    printf("second exit handler\n");
}

int main(void) {
    // 종료 핸들러 등록
    if (atexit(my_exit2) != 0) {
        fprintf(stderr, "can't register my_exit2");
    }
    
    if (atexit(my_exit1) != 0) {
        fprintf(stderr, "can't register my_exit1");
    }

    // 이미 등록된 종료 핸들러를 다시 등록하는 경우
    if (atexit(my_exit1) != 0) {
        fprintf(stderr, "can't register my_exit1");
    }

    printf("main() is done\n");
    
    return 0;
}

