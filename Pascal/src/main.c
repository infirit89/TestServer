#include <stdio.h>


#include "ps_defs.h"
#include "ps_assert.h"

const u16 port = 8001;
#define BUFFER_LENGTH 1024

int main(int argc, char** argv)
{
    perror("test");

//    FILE* htmlData = fopen("Assets/index.html", "r");
//    char responseData[BUFFER_LENGTH];
//    fgets(responseData, BUFFER_LENGTH, htmlData);
//    char httpResponse[BUFFER_LENGTH * 2] = "HTTP/1.1 200 OK\r\n\n";
//    strcat(httpResponse, responseData);
//
//    WSADATA data;
//    int result = WSAStartup(MAKEWORD(2, 2), &data);
//    PS_ASSERT(!result, "Cant initialize winsock2");
//
//    SOCKET socketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//    PS_ASSERT(socketId != INVALID_SOCKET, "Can't initialize server socket");
//
//    struct sockaddr_in serverAddress;
//    memset(&serverAddress, 0, sizeof(struct sockaddr_in));
//    serverAddress.sin_family = AF_INET;
//    serverAddress.sin_addr.s_addr = INADDR_ANY;
//    serverAddress.sin_port = htons(port);
//
//    int bindResult = bind(socketId, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr));
//    PS_ASSERT(!bindResult, "Can't bind the socket");
//
//    int listenResult = listen(socketId, 5);
//    PS_ASSERT(!listenResult, "Listen failed");
//
//    struct timeval tv;
//    tv.tv_sec = 1;
//    tv.tv_usec = 0;
//
//    char recieveBuffer[BUFFER_LENGTH];
//    SOCKET clientSocket;
//    while(TRUE)
//    {
//        clientSocket = accept(socketId,  NULL, NULL);
//        PS_ASSERT(clientSocket != INVALID_SOCKET, "Not able to get a new client socket");
//        printf("sending\n");
//        int totalBytes = 0;
//        int recieveResult = recv(clientSocket, recieveBuffer, BUFFER_LENGTH, 0);
//        printf("%s\n", recieveBuffer);
//
//        int sendRes = send(clientSocket, httpResponse, strlen(httpResponse), 0);
//        closesocket(clientSocket);
//    }
//
//    WSACleanup();

    system("pause");
    return 0;
}


