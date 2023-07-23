//
// Created by georg on 6/14/2023.
//

#include "ps_server.h"
#include "core/ps_assert.h"
#include "utils/ps_socket_utils.h"
#include "ps_response.h"
#include "utils/ps_queue.h"
#include "core/ps_string.h"
#include "utils/ps_file.h"
#include "utils/ps_content_type.h"
#include "utils/ps_buffer.h"
#include "ps_request.h"
#include "sc/sc_map.h"

#include "thread/ps_thread_pool.h"

#include <winsock2.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <fileapi.h>
#include <stdio.h>

#define INITIAL_ROUTE_MAP_CAPACITY 5

struct ps_server
{
    ps_socket server_socket;
//    ps_request_callback request_callback;
    int server_port;
    struct sc_map_32v route_map;
    struct sc_map_32v static_files;
    ps_thread_pool* thread_pool;
};


static void _default_favicon_response(ps_request* request)
{
    ps_response* favicon_response = response_init(request->socket);
    ps_respond(favicon_response);
}

ps_server* init_server(ps_protocol protocol, u32 thread_count)
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
    server->thread_pool = ps_thread_pool_create(thread_count);
//    server->request_callback = request_callback;
    sc_map_init_32v(&(server->route_map), INITIAL_ROUTE_MAP_CAPACITY, 0);
    server_add_route(server, "/favicon.ico", _default_favicon_response);

    sc_map_init_32v(&(server->static_files), INITIAL_ROUTE_MAP_CAPACITY, 0);

    return server;
}

static void _print_request_info(ps_request* request)
{
    const char* method = request_method_to_str(request->method);
    PS_TRACE("%s", method);
    PS_TRACE("%s", request->target);
    PS_TRACE("%s", request->buffer.data);
}


static void _dispatch_request(ps_request* request)
{
    uint32_t route_target_hash = sc_murmurhash(request->target);
    ps_request_callback callback = sc_map_get_32v(&(request->server->route_map), route_target_hash);

    if(sc_map_found(&request->server->route_map))
    {
        _print_request_info(request);
        callback(request);
    }
}

typedef struct server_thread_data
{
    ps_server* server;
    ps_socket client_socket;
} server_thread_data;

static void _handle_request(void* arg)
{
    server_thread_data* data = arg;
    ps_server* server = data->server;
    ps_socket client_socket = data->client_socket;

    free(data);

    ps_request* request = init_request(server, client_socket);
    buffer_init(&(request->buffer), PS_HTTP_REQUEST_INITIAL_BUF_SIZE);

    // receive the data from the client socket and parse baybeeeeeeeeee
    receive_from_socket(request->socket, &(request->buffer));
    parse_raw_request_data(request);

    _dispatch_request(request);

    shutdown_request(request);
}

void server_add_route(ps_server* server, const char* route, ps_request_callback callback)
{
    uint32_t route_target_hash = sc_murmurhash(route);
    sc_map_put_32v(&(server->route_map), route_target_hash, callback);
}

void start_request_response_loop(ps_server* server)
{
    while(TRUE)
    {
        ps_socket client = accept_client(server);
        if(client == PS_INVALID_SOCKET)
            continue;

        server_thread_data* data = malloc(sizeof(server_thread_data));
        data->server = server;
        data->client_socket = client;

        ps_thread_pool_add_work(server->thread_pool, _handle_request, data);
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

int shutdown_server(ps_server* server)
{
    if(!server)
        return -1;

    int close_result = close_socket(server->server_socket);

    sc_map_term_32v(&(server->route_map));

    char* file_data;
    sc_map_foreach_value(&(server->static_files), file_data)
    {
        free(file_data);
    }

    sc_map_term_32v(&(server->static_files));

    ps_thread_pool_destroy(server->thread_pool);

    free(server);
    return close_result;
}

static void _print_queue(ps_queue_str* queue)
{
    for (int i = 0; i < queue->size; ++i) {
        PS_TRACE("%s", queue->data[i]);
    }
}

static void _handle_static_file(ps_request* request)
{
    // the request target without the / (didnt have a goddamn clue how to name it)
    char* request_target = "";

    if(strlen(request->target) > 1)
        request_target = request->target + 1;

    uint32_t request_target_hash = sc_murmurhash(request_target);
    char* static_file_data = sc_map_get_32v(&(request->server->static_files), request_target_hash);
    if(!sc_map_found(&(request->server->static_files)))
        return;

    ps_response* response = response_init(request->socket);
    char* file_extension = get_extension(request_target);

    char* content_type;
    if(try_get_content_type(file_extension, &content_type))
        response_set_content_type(response, content_type);

    response_set_body(response, static_file_data, strlen(static_file_data));

    ps_respond(response);
}


 // i had to implement a fucking queue just for this;
 // so many things went wrong; but now i can add static files baybeeeeeeeeeeeeeeeeeeeee
void _server_add_static_files(ps_server* server, char* folder_path, ...)
{
    ps_queue_str queue;
    queue_init(&queue, 16);

    // heap allocated path
    char* ha_path = ps_string_copy(folder_path);
    queue_enqueue(&queue, ha_path);
    char route_target[2048];

    while (!queue_is_empty(&queue))
    {
        char *current = queue_peek(&queue);
        queue_dequeue(&queue);

        WIN32_FIND_DATA find_data;
        char path[2048];
        sprintf(path, "%s/*.*", current);

        const char folder_delimiter = '/';

        HANDLE file_handle = FindFirstFile(path, &find_data);
        PS_ASSERT(file_handle != INVALID_HANDLE_VALUE, "Couldn't open the folder");

        do {
            if (strcmp(find_data.cFileName, ".") == 0 ||
                strcmp(find_data.cFileName, "..") == 0)
                continue;

            sprintf(path, "%s/%s", current, find_data.cFileName);
            if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                ha_path = ps_string_copy(path);
                queue_enqueue(&queue, ha_path);
            }
            else
            {
                PS_TRACE(find_data.cFileName);
                va_list extensions;

                va_start(extensions, folder_path);

                char* extension;
                while((extension = va_arg(extensions, char*)) != NULL)
                {
                    char* file_extension = get_extension(find_data.cFileName);
                    if(!file_extension)
                        continue;

                    if(ps_strings_equal(file_extension, extension))
                    {
                        char* relative_path = strchr(path, folder_delimiter) + 1;

                        PS_TRACE(relative_path);
                        PS_TRACE(path);

                        char* style_data = read_file(path);

                        uint32_t relative_path_hash = sc_murmurhash(relative_path);
                        sc_map_put_32v(&(server->static_files), relative_path_hash, style_data);
                        sprintf(route_target, "/%s", relative_path);
                        server_add_route(server, route_target, _handle_static_file);
                    }
                }

                va_end(extensions);
            }

        } while (FindNextFile(file_handle, &find_data));

        FindClose(file_handle);

        free(current);
    }

    queue_free(&queue);
}
