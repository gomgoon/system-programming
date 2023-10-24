#include "mmap-list.h"

int main(void) {
    struct list *l = NULL;
    pid_t pid;
    
    // 메모리에 리스트 초기화
    if (list_init(1000) < 0) {
        perror("list_init error");
        exit(1);
    }
    
    // 리스트에 3개의 항목 추가
    if ((l = list_add(l, 42)) == NULL
        || (l = list_add(l, 17)) == NULL
        || (l = list_add(l, 13)) == NULL) {
        perror("list_add error");
        exit(1);
    }
    
    // 리스트의 항목 출력
    list_visit("common", l);
    
    // 이제 fork()를 사용합니다.
    if ((pid = fork()) < 0) {
        perror("fork() error");
        exit(1);
    }
    
    /* 부모 프로세스 */
    if (pid > 0) {
        // 리스트에 항목 추가
        l = list_add(l, 7);
        // 리스트의 항목 출력
        list_visit("parent", l);
    }
    
    /* 자식 프로세스 */
    else {
        // 리스트에 항목 추가
        l = list_add(l, 5);
        // 리스트의 항목 출력
        list_visit("child", l);
    }
    
    exit(EXIT_SUCCESS);
}

