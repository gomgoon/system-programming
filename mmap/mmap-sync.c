#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>

#define FILE "msync.data"

int main(void) {
    size_t w = 0;
    int fd;
    int pagesize;
    const char *text = "This code creates a file, creates a memory map, stores data into the file, and writes the data to the disk using msync()";

    // 페이지 크기를 확인하기 위해 `sysconf(_SC_PAGE_SIZE)`를 사용합니다.
    if ((pagesize = sysconf(_SC_PAGE_SIZE)) < 0) {
        perror("sysconf() error");
        exit(1);
    }

    // 파일을 생성하고 읽기/쓰기 권한으로 엽니다.
    fd = open(FILE, (O_CREAT | O_TRUNC | O_RDWR), (S_IRUSR | S_IWUSR));
    if (fd < 0) {
        perror("open() error");
        exit(1);
    }

    // 파일 오프셋을 파일의 시작 위치에서 페이지 크기만큼 이동시킵니다.
    // 즉, 파일 오프셋을 페이지 크기로 설정합니다.
    off_t lastoffset = lseek(fd, pagesize, SEEK_SET);

    // 파일에 한 바이트 데이터를 씁니다.
    w = write(fd, " ", 1);
    if (w != 1) {
        perror("write() error");
        exit(1);
    }

    void *address;
    off_t my_offset = 0;

    // 페이지 크기를 가지는 메모리 매핑 영역을 생성합니다.
    address = mmap(NULL, pagesize, PROT_WRITE, MAP_SHARED, fd, my_offset);
    if (address == MAP_FAILED) {
        perror("mmap() error");
        exit(1);
    }

    // 데이터를 메모리 매핑 영역에 복사합니다.
    strncpy((char *)address, text, strlen(text));

    // `msync()` 함수를 사용하여 변경 내용을 디스크에 씁니다.
    if (msync(address, pagesize, MS_SYNC) < 0) {
        perror("msync() error");
        exit(1);
    } else {
        printf("%s\n", "msync() completed successfully.");
    }

    // 메모리 매핑 영역을 해제합니다.
    munmap(address, pagesize);
    close(fd);

    return 0;
}

