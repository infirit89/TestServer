#include "ps_assert.h"
#include "string.h"
#include "pascal.h"
#include "ps_response.h"
#include "ps_file.h"
#include "ps_log.h"
#include "ps_tests.h"

#include <stdio.h>

static const u16 port = 8080;
#define BUFFER_LENGTH 1024

static char http_response_body[BUFFER_LENGTH * 2];
static char http_css_response_body[BUFFER_LENGTH * 2];

static void handle_home_request(ps_request* request)
{
    ps_response* response = response_init(request->socket);
    response_set_content_type(response, "text/html");
    response_set_body(response, http_response_body, strlen(http_response_body));

    ps_respond(response);
}

static void handle_style_request(ps_request* request)
{
    ps_response* response2 = response_init(request->socket);
    response_set_content_type(response2, "text/css");
    response_set_body(response2, http_css_response_body, strlen(http_css_response_body));

    ps_respond(response2);
}

//u32 __stdcall read_input(void* lpParameter)
//{
//    char input[30];
//    while(1)
//    {
//        Sleep(100);
//
//        printf("Type your input\n");
//        fgets(input, sizeof(input), stdin);
//        input[strcspn(input, "\n")] = 0;
//
//        if(strcmp(input, "exit") == 0)
//            break;
//        else if(strcmp(input, "test") == 0)
//            printf("i cum\n");
//    }
//    return 0;
//}

int main(int argc, char** argv)
{
    int result = ps_init();
    PS_ASSERT(!result, "Can't start pascal");

    char* response_data = read_file("Assets/index.html");
    strcat(http_response_body, response_data);

    if(response_data)
        free(response_data);

    response_data = read_file("Assets/style.css");
    strcat(http_css_response_body, response_data);
    if(response_data)
        free(response_data);

    printf("%s\n", http_css_response_body);

    ps_server* server = init_server(PS_TCP);
    server_add_static_files(server, "Assets", ".css");

    server_add_route(server, "/", handle_home_request);
//    server_add_route(server, "/style.css", handle_style_request);

    server_listen(server, port, PS_DEFAULT_BACKLOG);

    shutdown_server(server);

    ps_shutdown();

    return 0;
}
