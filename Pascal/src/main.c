#include <stdio.h>
#include "ps_defs.h"
#include "ps_assert.h"
#include "string.h"
#include "pascal.h"
#include "ps_file.h"
#include <winsock2.h>
#include <eventsys.h>

static const u16 port = 8001;
#define BUFFER_LENGTH 1024

static char receive_buffer[BUFFER_LENGTH];
static char http_response[BUFFER_LENGTH * 2] = "HTTP/1.1 200 OK\r\n\n";

static void handle_request(ps_request* request)
{
    //receive_data_from_client(request->client_socket, receive_buffer, BUFFER_LENGTH, 0);
    printf("%s\n", request->buffer.data);
    send_data_to_client(request->client_socket, http_response, strlen(http_response), 0);
}

int main(int argc, char** argv)
{
//    char* response_data = read_file("Assets/index.html");
//    strcat(http_response, response_data);

//    if(response_data)
//        free(response_data);

    int result = ps_init();
    PS_ASSERT(!result, "Can't start pascal");

    ps_server* server = init_server(handle_request, PS_TCP);
    server_listen(server, port, PS_DEFAULT_BACKLOG);

    shutdown_server(server);

    result = ps_shutdown();
    PS_ASSERT(!result, "Can't shutdown pascal");

    return 0;
}
