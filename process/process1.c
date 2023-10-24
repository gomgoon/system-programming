#include <stdio.h>
#include <stdlib.h>

// 전역 변수 선언
int global_variable = 100;      // 초기화된 데이터 세그먼트에 저장
char global_array[1024];         // BSS 세그먼트에 할당

// 함수 선언
void func(int arg) {
    printf("stack segment near: %p\n", (void *)&arg); // 스택 세그먼트 주소 출력
}

int main(int argc, char **argv) {
    char *ptr;
    // 동적 메모리 할당
    ptr = (char *)malloc(sizeof(char)); // 힙 세그먼트에 메모리 할당
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n"); // 메모리 할당 실패시 오류 메시지 출력
        return 1;
    }

    func(100); // 함수 호출 (함수 호출 스택 프레임)
    printf("heap segment near: %p\n", (void *)ptr); // 힙 세그먼트 주소 출력
    printf("BSS segment near: %p\n", (void *)global_array); // BSS 세그먼트 주소 출력
    printf("initialized data segment near: %p\n", (void *)&global_variable); // 초기화된 데이터 세그먼트 주소 출력

    return 0;
}
