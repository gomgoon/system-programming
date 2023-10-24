#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define DEF_PAGER "/bin/more"
#define MAXLINE 1024

int main(int argc, char *argv[]) {
    int n, fd[2];
    char *pager, *argv0;
    char line[MAXLINE];
    FILE *fp;
    pid_t pid;

    if (argc != 2) {
        perror("Usage: filter1 FILE");
        exit(1);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("fopen error");
        exit(1);
    }

    if (pipe(fd) < 0) {
        perror("pipe error");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    }

    // 부모 프로세스
    if (pid > 0) {
        close(fd[0]); // 파이프의 읽기 닫기

        // 부모 프로세스는 파일에서 데이터를 읽어서 파이프로 쓰기
        while (fgets(line, MAXLINE, fp) != NULL) {
            n = strlen(line);
            if (write(fd[1], line, n) != n) {
                perror("write error");
                exit(1);
            }
        }

        if (ferror(fp)) {
            perror("fgets error");
            exit(1);
        }

        close(fd[1]); // 파이프의 쓰기 닫기 (파이프를 통해 다른 프로세스로 더 이상 데이터를 보내지 않음)

        if (waitpid(pid, NULL, 0) < 0) {
            perror("waitpid error");
            exit(1);
        }
    }

    return 0;
}

