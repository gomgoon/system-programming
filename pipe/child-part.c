// 부모 프로세스에서 파이프로 데이터를 전달하고, 자식 프로세스를 실행하는 부분
if (pid > 0) {
    // ... (앞 부분 생략)

    // 파이프의 쓰기 닫기 (더 이상 데이터를 파이프로 보내지 않음)
    close(fd[1]);

    // 자식 프로세스의 종료를 기다림
    if (waitpid(pid, NULL, 0) < 0) {
        perror("waitpid error");
        exit(1);
    }
}
// 자식 프로세스에서 다른 프로세스를 실행하고 파이프의 데이터를 사용하는 부분
else {
    // 파이프의 쓰기 닫기 (자식 프로세스에서는 파이프를 쓰지 않음)
    close(fd[1]);

    // 파이프의 읽기 닫기 (표준 입력(stdin)으로 사용하기 위해 파이프의 읽기를 stdin으로 연결)
    if (fd[0] != STDIN_FILENO) {
        // dup2()를 사용하여 파이프의 읽기(fd[0])를 표준 입력(STDIN_FILENO)으로 연결
        if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
            perror("dup2 error");
        close(fd[0]); // 더 이상 파이프의 읽기가 필요하지 않으므로 닫음
    }

    // execl()을 사용하여 다른 프로세스(보통 페이저 프로그램)를 실행
    if ((pager = getenv("PAGER")) == NULL)
        pager = DEF_PAGER;
    if ((argv0 = strrchr(pager, '/')) != NULL)
        argv0++; // 가장 오른쪽의 슬래시 다음으로 이동
    else
        argv0 = pager; // 페이저 문자열에서 슬래시가 없는 경우
    // execl()을 사용하여 페이저 프로그램을 실행하여 파일을 화면에 출력
    if (execl(pager, argv0, (char *)0) < 0)
        perror("execl error");
}

exit(EXIT_SUCCESS);
}

