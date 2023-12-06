// 학번: 19011586
// 이름: 정욱현
//multiple-client.c
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
    int result; // 결과 값을 저장할 변수 선언
    int firstNumber, secondNumber, identifier; // 연산에 사용될 변수 2개, 식별에 사용될 변수 1개를 선언
    int clientFd, len; // 클라이언트 소켓 파일 디스크립터 clientFd 길이 len 변수 선언
    struct sockaddr_in client_addr; // 소켓 주소 구조체 선언
    char sendData[BUF_SIZE]; // 전송할 데이터 배열을 선언
    char recvData[BUF_SIZE]; // 수신할 데이터 배열을 선언

    // 버퍼 초기화
    memset(recvData, 0, BUF_SIZE);
    memset(sendData, 0, BUF_SIZE);
    
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
    // 클라이언트로부터 값을 2개 입력받습니다.
    printf("Enter Number to send: ");
    scanf("%d %d", &firstNumber, &secondNumber);
    // client의 실행 파일 이름을 통해서 client의 식별자를 선정합니다.
    if(strcmp(argv[0], "./multiple-client") == 0) // 곱 연산 클라이언트의 경우 identifier는 1입니다.
    {   
        identifier = 1; 
    }
    else{ // 합 연산 클라이언트의 경우 identifier는 0입니다.
        identifier = 0;
    }
    sprintf(sendData, "Send Number is %d %d %d\n", firstNumber, secondNumber, identifier); // 입력 받은 데이터를 포함한 문자열을 저장합니다.
    
    send(clientFd, sendData, strlen(sendData), 0); // 입력받은 메시지를 서버에 전송합니다.
    
    recv(clientFd, recvData, BUF_SIZE, 0); // 서버로부터 데이터를 전송 받습니다.
    if(identifier == 1) // 식별자가 1이라면 곱 연산의 결과물을 저장합니다.
    {
        sscanf(recvData, "Multiple Result is %d", &result);
    }
    else // 식별자가 0이라면 합 연산의 결과물을 저장합니다.
    {
        sscanf(recvData, "Addition Result is %d", &result);
    }
    printf("%s\n",recvData); // 서버로 부터 전달 받은 문자열을 출력합니다.
    
    // 소켓을 닫습니다.
    close(clientFd);

    return 0;
}