//server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>

#define BUF_LEN  1024 // 버퍼의 크기를 정의합니다.

void notice();
void *thread_multiple(void *arg);
void *thread_addition(void *arg);

int main(int argc, char *argv[])
{
    char client[20];
    char buf[BUF_LEN]; // 메시지를 저장할 버퍼를 선언합니다.
    char ipAddress[20]; // 클라이언트의 ipAddress를 저장할 배열을 선언합니다.
    struct sockaddr_in server_addr, client_addr; // 서버와 클라이언트의 소켓 주소 구조체를 선언합니다.
    
    int serverFd, clientFd; // 서버와 클라이언트의 소켓 파일 디스크립터를 선언합니다.
    int len, msgSize, result; // 길이와 msg의 크기를 저장할 변수를 선언합니다.
    int *numArray;
    void *thread_result;
    pthread_t tid;


    // 실행 시 인자를 체크하여 포트 번호를 입력받았는지 확인합니다.
    if(argc != 2)
    {
        // 사용법을 출력합니다.
        printf("Usage : /filename [PORT]\n"); 
        exit(0);
    }

    // server의 안내문을 출력합니다.
    notice();

    // 소켓을 생성합니다.
    if((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        // 소켓 생성 실패 시 메시지를 출력합니다.
        printf("서버 측 소켓 생성에 실패하였습니다.\n");
        exit(0);
    }

    // 서버 주소 구조체를 초기화하고 설정합니다.
    memset(&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 주소에서 오는 연결을 받습니다.
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1])); // 입력받은 포트 번호를 설정합니다.

    // bind 함수를 통해 소켓의 address binding을 시도합니다.
    if(bind(serverFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        // 바인딩 실패 시 메시지를 출력합니다.
        printf("Server: can not bind local address\n"); 
        exit(0);
    }

    // 연결 요청을 기다립니다.
    if(listen(serverFd, 5) < 0)
    {
        // 리슨 실패 시 메시지를 출력합니다.
        printf("Server: can not listen connect.\n"); 
        exit(0);
    }

    // 메인 루프입니다. 연결을 받고 메시지를 출력합니다.
    while(1)
    {
        // 클라이언트의 연결을 받습니다.
        len = sizeof(client_addr);
        clientFd = accept(serverFd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
        
        if(clientFd < 0)
        {
            // 연결 수락 실패 시 메시지를 출력합니다.
            printf("Server: accept failed\n");
            exit(0);
        }

        // 클라이언트의 IP 주소를 출력합니다.
        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ipAddress, sizeof(ipAddress));
        printf("Server: %s client connect.\n", ipAddress);
        
        // 클라이언트로부터 메시지를 받습니다.
        if((msgSize = recv(clientFd, buf, BUF_LEN - 1, 0)) == -1)
        {
            // 수신 실패 시 메시지를 출력합니다.
            printf("Server: recv failed\n"); 
            exit(0);
        }

        buf[msgSize] = '\0';

        numArray = (int*)malloc(3 * sizeof(int));
        if(sscanf(buf, "Send Number is %d %d %d", &numArray[0], &numArray[1], &numArray[2]) != 3) {
            printf("%s\n",buf);
            printf("Invalid data format received.\n");
            free(numArray);
            continue; // 올바른 데이터 형식이 아니므로, 다음 연결 대기로 넘어갑니다.
        }
        printf("received data is %d %d\n",numArray[0], numArray[1]);
        if(numArray[2] == 1)
            strcpy(client, "multiple client");
        else
            strcpy(client, "addition client");
        
        if(numArray[2] == 1)
        {
            pthread_create(&tid, NULL, thread_multiple, numArray); // 쓰레드 생성
            pthread_join(tid, &thread_result);
            result = *((int *)thread_result); // void *를 int *로 캐스팅한 후 값을 참조
            free(thread_result); // 쓰레드 함수에서 할당한 메모리 해제

            sprintf(buf, "Multiple Result is %d", result);
        }
        else
        {
            pthread_create(&tid, NULL, thread_addition, numArray); // 쓰레드 생성
            pthread_join(tid, &thread_result);
            result = *((int *)thread_result); // void *를 int *로 캐스팅한 후 값을 참조
            free(thread_result); // 쓰레드 함수에서 할당한 메모리 해제

            sprintf(buf, "Addition Result is %d", result);
        }
        send(clientFd, (char *)buf, msgSize, 0); // 받은 메시지를 클라이언트에게 다시 보냅니다.
        printf("Calculation result is sented!\n");

        close(clientFd); // 클라이언트의 소켓을 닫습니다.
        printf("Server: %s client closed.\n", ipAddress);
    }

    close(serverFd); // 서버의 소켓을 닫습니다.

    return 0;
}

void notice(){
    printf("=========================================\n");
    printf("=========================================\n");
    printf("===== 반갑습니다! calc-server입니다!=====\n");
    printf("===== 원하는 값을 입력해 주십시오!  =====\n");
    printf("=========================================\n");
    printf("=========================================\n");
}

void *thread_multiple(void *arg){
    printf("Thread start!\n");
    int *numArray = (int *)arg;
    int *result = malloc(sizeof(int));
    *result = numArray[0] * numArray[1];
    free(numArray);
    printf("Thread end! return val is %d\n", *result);
    return result;
}

void *thread_addition(void *arg){
    int *numArray = (int *)arg;
    int *result = malloc(sizeof(int));
    
    *result = numArray[0] + numArray[1];
    free(numArray);

    return result;
}