#include <stdio.h>
#include <stdlib.h>
#include "mmap-uid.h"

int main(void) {
    int fd;
    struct stat finfo;
    struct glob_id *id;

    // 파일을 읽기 및 쓰기 권한으로 엽니다.
    if ((fd = open(DB_FILE, O_RDWR)) < 0) {
        perror("open() error");
        exit(1);
    }

    // 파일 정보를 가져옵니다.
    if (fstat(fd, &finfo) < 0) {
        perror("fstat() error");
        exit(1);
    }

    // 파일을 메모리에 매핑합니다.
    id = (struct glob_id *)mmap(NULL, finfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (id == MAP_FAILED) {
        perror("mmap() error");
        exit(1);
    }

    printf("checking magic number...\n");

    // 매직 넘버를 확인합니다.
    if (glob_id_verify_magic(fd, id) < 0) {
        printf("invalid magic number, abort!\n");
        exit(EXIT_FAILURE);
    } else {
        // 카운터 값을 가져옵니다.
        printf("got id: %ld\n", id->val);

        // 카운터 값을 1 증가시킵니다.
        glob_id_write(id, id->val + 1);

        exit(EXIT_SUCCESS);
    }
}

