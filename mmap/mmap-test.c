#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define FILE "test.data"

// 파일을 생성하고 데이터를 작성하는 함수
void create_data(void) {
    int fd, i;
    printf("%s\n", __func__);
    fd = open(FILE, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    for (i = 0; i < 10; i++)
        write(fd, &i, sizeof(int));
    close(fd);
}

// 파일을 열어 데이터를 읽고 출력하는 함수
void display_data(void) {
    int fd = 0, data = 0, i;
    printf("%s\n", __func__);
    fd = open(FILE, O_RDONLY);
    for (i = 0; i < 10; i++) {
        if (read(fd, &data, sizeof(int)) == 4)
            printf("%4d", data);
    }
    puts("");
    close(fd);
}

// 파일을 열어 데이터를 변경하는 함수
void change_data(void) {
    int fd, data;
    fd = open(FILE, O_RDWR);
    read(fd, &data, sizeof(int));
    data += 100;
    write(fd, &data, sizeof(int));
    close(fd);
}

// 메모리 매핑을 사용하여 파일의 내용을 수정하는 함수
void mmap_data(void) {
    int *mapped = NULL;
    int fd;
    struct stat finfo;

    fd = open(FILE, O_RDWR);
    if (fstat(fd, &finfo) < 0) {
        perror("fstat() error");
        exit(1);
    }

    // 파일의 크기만큼 메모리 매핑 영역을 생성합니다.
    mapped = mmap(NULL, finfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap() error");
        exit(1);
    }

    // 메모리 매핑 영역에 데이터를 저장합니다.
    mapped[1] += 100;
    mapped[2] += 200;
    mapped[3] += 300;

    // msync() 함수를 사용하여 변경 내용을 파일에 씁니다.
    // MS_ASYNC 플래그를 사용하여 메모리 매핑 영역이 커널 버퍼 캐시와 동기화됩니다.
    msync(mapped, finfo.st_size, MS_ASYNC);

    // 메모리 매핑 영역을 해제합니다.
    munmap(mapped, finfo.st_size);

    close(fd);
}

int main(void) {
    create_data();
    display_data();
    change_data();
    display_data();
    mmap_data();
    display_data();
    return 0;
}

