#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd;               // 파일 디스크립터
    struct stat finfo;    // 파일 정보 구조체
    void *buf;            // 버퍼

    if (argc != 2) {
        perror("Usage: mmap-cat filename");
        exit(1);
    }

    // 읽기 전용 권한으로 파일을 엽니다.
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror("open() error");
        exit(1);
    }

    // 파일 정보를 fstat()을 사용하여 가져옵니다.
    if (fstat(fd, &finfo) < 0) {
        perror("fstat() error");
        exit(1);
    }

    // mmap() 함수를 사용하여 파일을 메모리에 매핑합니다.
    // 파일 데이터를 버퍼에 저장합니다.
    buf = mmap(NULL, finfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf == MAP_FAILED) {
        perror("mmap() error");
        exit(1);
    }

    // 파일 데이터를 쓰기(출력)합니다.
    if (write(STDOUT_FILENO, buf, finfo.st_size) != finfo.st_size) {
        perror("write() error");
        exit(1);
    }

    munmap(buf, finfo.st_size);
    close(fd);

    exit(EXIT_SUCCESS);
}

