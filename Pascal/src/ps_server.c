//
// Created by georg on 6/14/2023.
//

#include "ps_server.h"
#include "ps_assert.h"
#include "ps_socket_utils.h"
#include "ps_response.h"
#include "ps_queue.h"

#include <winsock2.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <windows.h>

#define INITIAL_ROUTE_MAP_CAPACITY 5

static void _default_favicon_response(ps_request* request)
{
    ps_response* favicon_response = response_init(request->client_socket);
    ps_respond(favicon_response);
}

ps_server* init_server(ps_protocol protocol)
{
    int socket_type = SOCK_STREAM;
    int socket_protocol = IPPROTO_TCP;

    switch (protocol) {
        case PS_TCP:
            socket_type = SOCK_STREAM;
            socket_protocol = IPPROTO_TCP;
            break;
        case PS_UDP:
            socket_type = SOCK_DGRAM;
            socket_protocol = IPPROTO_UDP;
            break;
        default:
            PS_ASSERT(PS_FALSE, "Invalid protocol type");
            return NULL;
    }

    // TODO: maybe allow the user to select a family?
    ps_socket server_socket = socket(AF_INET, socket_type, socket_protocol);
    PS_ASSERT(server_socket, strerror(errno));

    ps_server* server = malloc(sizeof(ps_server));
    server->server_socket = server_socket;
//    server->request_callback = request_callback;
    sc_map_init_sv(&(server->route_map), INITIAL_ROUTE_MAP_CAPACITY, 0);
    server_add_route(server, "/favicon.ico", _default_favicon_response);

    return server;
}

static void _print_request_info(ps_request* request)
{
    const char* method = request_method_to_str(request->method);
    printf("%s\n", method);
    printf("%s\n", request->target);
    printf("%s\n", request->buffer.data);

}

void server_add_route(ps_server* server, const char* route, ps_request_callback callback)
{
    sc_map_put_sv(&(server->route_map), route, callback);
}

void start_request_response_loop(ps_server* server)
{
    while(TRUE)
    {
        ps_socket client = accept_client(server);
        if(client == PS_INVALID_SOCKET)
            continue;

        ps_request* request = init_request(server, client);
        buffer_init(&(request->buffer), PS_HTTP_REQUEST_INITIAL_BUF_SIZE);

        // receive the data from the client socket and parse baybeeeeeeeeee
        receive_from_socket(request->client_socket, &(request->buffer));
        parse_raw_request_data(request);

//        server->request_callback(request);

        ps_request_callback callback = sc_map_get_sv(&(server->route_map), request->target);
        if(sc_map_found(&server->route_map))
        {
            _print_request_info(request);
            callback(request);
        }

        shutdown_request(request);
    }
}

int server_listen(ps_server* server, u16 port, s32 backlog)
{
    server->server_port = port;
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    // TODO: make it possible to specify an address
    server_address.sin_addr.s_addr = INADDR_ANY;

    int bind_result = bind(server->server_socket, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    PS_ASSERT(!bind_result, "Can't bind the socket");
    if(bind_result)
        return bind_result;

    int listen_result = listen(server->server_socket, backlog ? backlog : PS_DEFAULT_BACKLOG);
    PS_ASSERT(!listen_result, "Listen failed");
    if(listen_result)
        return listen_result;

    start_request_response_loop(server);

    return 0;
}

ps_socket accept_client(ps_server* server)
{
    ps_socket client;
    client = accept(server->server_socket, NULL, NULL);
    PS_ASSERT(client, "Not able to get a new client");

    return client;
}

ps_request* init_request(ps_server* server, ps_socket client_socket)
{
    ps_request* request = (ps_request*)malloc(sizeof(ps_request));
    request->server = server;
    request->client_socket = client_socket;

    return request;
}

void shutdown_request(ps_request* request)
{
    PS_ASSERT(request, "Can't free a request that is null");

    close_socket(request->client_socket);

    buffer_free(&(request->buffer));
    free(request);
}

int close_socket(ps_socket socket)
{
    int close_result = closesocket(socket);
    PS_ASSERT(!close_result, "Couldn't close the client socket");
    return close_result;
}

int shutdown_server(ps_server* server)
{
    if(server != NULL)
        return -1;

    int close_result = close_socket(server->server_socket);

    sc_map_term_sv(&(server->route_map));

    free(server);
    return close_result;
}

static void _print_queue(ps_queue* queue)
{
    for (int i = 0; i < queue->size; ++i) {
        printf("%s\n", queue->data[i]);
    }
}

void server_add_static_files(ps_server* server, char* folder_path, ...)
{
    ps_queue queue;
    queue_init(&queue, 16);

    queue_enqueue(&queue, folder_path);

    while (!queue_is_empty(&queue))
    {
        char *current = queue_peek(&queue);
        queue_dequeue(&queue);

        WIN32_FIND_DATA find_data;
        char path[2048];
        sprintf(path, "%s\\*.*", current);

        HANDLE file_handle = FindFirstFile(path, &find_data);
        PS_ASSERT(file_handle != INVALID_HANDLE_VALUE, "Couldn't open the folder");

        do {
            if (strcmp(find_data.cFileName, ".") == 0 ||
                strcmp(find_data.cFileName, "..") == 0)
                continue;

            sprintf(path, "%s\\%s", current, find_data.cFileName);
            if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                printf("Directory: %s\n", path);
                queue_enqueue(&queue, path);
            } else
                printf("File: %s\n", find_data.cFileName);

            _print_queue(&queue);
        } while (FindNextFile(file_handle, &find_data));

        FindClose(file_handle);
    }


//    va_list extensions;

//    while ((dir_entity = readdir(assets_dir)) != NULL)
//    {
//
//
////        va_start(extensions, folder_path);
////        char* extension;
////        while ((extension = va_arg(extensions, char*)) != NULL)
//
////        va_end(extensions);
//    }

    queue_free(&queue);
}
