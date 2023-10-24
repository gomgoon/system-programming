#include <stdio.h>
#include <stdlib.h>
#include "mmap-uid.h"

int main(void) {
    int fd;
    struct stat finfo;
    struct glob_id *id;

    // 파일을 열고 쓰기 및 읽기 권한으로 생성합니다.
    if ((fd = open(DB_FILE, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0) {
        perror("open() error");
        exit(1);
    }

    // 파일 크기를 구조체 `glob_id`의 크기로 조절합니다.
    if (ftruncate(fd, sizeof(struct glob_id)) < 0) {
        perror("ftruncate() error");
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

    // 카운터 값을 0으로 초기화합니다.
    glob_id_write(id, (long)0);

    exit(EXIT_SUCCESS);
}

