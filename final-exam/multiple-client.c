//client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUF_SIZE 1024 // 버퍼 크기 정의
#define PORT 2222 // 포트 번호 정의
#define IPADDR "127.0.0.1" // 접근할 서버 IP 주소 정의

int main(int argc, char *argv[])
{
    int clientFd, len; // 클라이언트 소켓 파일 디스크립터 clientFd 길이 len 변수 선언
    struct sockaddr_in client_addr; // 소켓 주소 구조체 선언
    char sendData[BUF_SIZE]; // 전송할 데이터 배열을 선언합니다.
    
    // 소켓을 생성합니다.
    if((clientFd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        // 소켓 생성 실패 시 메시지를 출력합니다.
        printf("클라이언트 측 소켓 생성에 실패하였습니다.\n");
        exit(0);
    }

    // 클라이언트 주소 구조체를 설정합니다.
    memset(&client_addr, 0x00, sizeof(client_addr));
    client_addr.sin_addr.s_addr = inet_addr(IPADDR);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT);

    // connect 함수를 통해 서버에 연결을 시도합니다.
    // 만약, return 값이 -1 (오류 처리)이라면, 제어문의 내부 코드를 실행합니다.
    if(connect(clientFd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
    {
        // 연결 실패 시 메시지를 출력하고 소켓을 닫습니다.
        printf("Can't connect\n"); 
        close(clientFd);
        return -1;
    }

    // 사용자로부터 메시지를 입력받습니다.
    printf("Enter message to send: ");
    fgets(sendData, BUF_SIZE, stdin);
    // 입력받은 메시지를 서버에 전송합니다.
    send(clientFd, sendData, strlen(sendData), 0);
    // 소켓을 닫습니다.
    close(clientFd);

    return 0;
}