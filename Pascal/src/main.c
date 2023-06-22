#include <stdio.h>
#include "ps_defs.h"
#include "ps_assert.h"
#include "string.h"
#include "pascal.h"
#include "ps_file.h"
#include <winsock2.h>

const u16 port = 8001;
#define BUFFER_LENGTH 1024

int main(int argc, char** argv)
{
//    FILE* htmlData = fopen("Assets/index.html", "r");
//    char responseData[BUFFER_LENGTH];
//    fgets(responseData, BUFFER_LENGTH, htmlData);
    char* response_data = read_file("Assets/index.html");
    char httpResponse[BUFFER_LENGTH * 2] = "HTTP/1.1 200 OK\r\n\n";
    strcat(httpResponse, response_data);

    if(response_data)
        free(response_data);

    int result = ps_init();
    PS_ASSERT(!result, "Can't start pascal");

    ps_server server_data;
    init_server(&server_data, PS_TCP);
    start_listen(&server_data, port, PS_DEFAULT_BACKLOG);

    char recieve_buffer[BUFFER_LENGTH];

    while(TRUE)
    {
        ps_socket client = accept_client(&server_data);
        receive_data_from_client(client, recieve_buffer, BUFFER_LENGTH, 0);
        printf("%s\n", recieve_buffer);
        send_data_to_client(client, httpResponse, strlen(httpResponse), 0);
        close_socket(client);
    }

    shutdown_server(&server_data);

    result = ps_shutdown();
    PS_ASSERT(!result, "Can't shutdown pascal");

    return 0;
}
