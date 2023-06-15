#include <stdio.h>
#include "ps_defs.h"
#include "ps_assert.h"
#include "string.h"
#include "pascal.h"
#include <winsock2.h>

const u16 port = 8001;
#define BUFFER_LENGTH 1024

int main(int argc, char** argv)
{
    FILE* htmlData = fopen("Assets/index.html", "r");
    char responseData[BUFFER_LENGTH];
    fgets(responseData, BUFFER_LENGTH, htmlData);
    char httpResponse[BUFFER_LENGTH * 2] = "HTTP/1.1 200 OK\r\n\n";
    strcat(httpResponse, responseData);

    int result = ps_init();
    PS_ASSERT(!result, "Can't start pascal");

    ps_server server_data;
    init_server(&server_data, PS_TCP);
    start_listen(&server_data, port, PS_DEFAULT_BACKLOG);

    char recieveBuffer[BUFFER_LENGTH];

    while(TRUE)
    {
        u32 clientSocket = accept(server_data.server_socket,  NULL, NULL);
        PS_ASSERT(clientSocket, "Not able to get a new client socket");
        printf("sending\n");
        int totalBytes = 0;
        int recieveResult = recv(clientSocket, recieveBuffer, BUFFER_LENGTH, 0);
        printf("%s\n", recieveBuffer);

        int sendRes = send(clientSocket, httpResponse, strlen(httpResponse), 0);
        closesocket(clientSocket);
    }

    result = ps_shutdown();
    PS_ASSERT(!result, "Can't shutdown pascal");

    return 0;
}


