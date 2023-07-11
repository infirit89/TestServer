#include <stdio.h>
#include "ps_defs.h"
#include "ps_assert.h"
#include "string.h"
#include "pascal.h"
#include "ps_response.h"
#include "ps_file.h"
#include <winsock2.h>
#include <eventsys.h>

static const u16 port = 8080;
#define BUFFER_LENGTH 1024

static char receive_buffer[BUFFER_LENGTH];
static char http_response[BUFFER_LENGTH * 2] = "HTTP/1.1 200 OK\r\n\n";
static char http_response_body[BUFFER_LENGTH * 2];

static void handle_request(ps_request* request)
{
    //receive_data_from_client(request->client_socket, receive_buffer, BUFFER_LENGTH, 0);
    const char* method = request_method_to_str(request->method);
    printf("%s\n", method);
    printf("%s\n", request->target);
    printf("%s\n", request->buffer.data);

    ps_response* response = response_init(request->client_socket);
    response_set_body(response, http_response_body, strlen(http_response_body));

    ps_respond(response);
}

int main(int argc, char** argv)
{
    char* response_data = read_file("Assets/index.html");
    strcat(http_response_body, response_data);

    if(response_data)
        free(response_data);

    int result = ps_init();
    PS_ASSERT(!result, "Can't start pascal");

    ps_server* server = init_server(handle_request, PS_TCP);
    server_listen(server, port, PS_DEFAULT_BACKLOG);

    shutdown_server(server);

    result = ps_shutdown();
    PS_ASSERT(!result, "Can't shutdown pascal");

    return 0;
}
