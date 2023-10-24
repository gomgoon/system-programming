#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    int fd;
    struct stat finfo;
    void *fmap;
    char *match;

    if (argc != 3) {
        perror("Usage: mmap-search STRING filename");
        exit(1);
    }

    if ((fd = open(argv[2], O_RDONLY)) < 0) {
        perror("open() error");
        exit(1);
    }

    if (fstat(fd, &finfo) < 0) {
        perror("fstat() error");
        exit(1);
    }

    // 파일 데이터를 메모리에 한 번에 읽어옵니다.
    fmap = mmap(NULL, finfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    
    // mmap된 영역에서 argv[1] 문자열을 검색합니다.
    match = strstr((char *)fmap, argv[1]);

    if (match == NULL) {
        printf("string %s not found in %s\n", argv[1], argv[2]);
    } else {
        printf("string %s found in %s\n", argv[1], argv[2]);
    }

    exit(match == NULL ? EXIT_FAILURE : EXIT_SUCCESS);
}

