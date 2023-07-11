//
// Created by OKAY on 7/8/2023.
//

#include "ps_response.h"
#include "ps_assert.h"
#include "ps_buffer.h"
#include "ps_socket_utils.h"

#include <stdlib.h>
#include <stdarg.h>

const char* response_text[] =
{
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
     // 100s
    "Continue", "Switching Protocols", "Processing", "Early Hints",
    "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
     // 200s
    "OK", "Created", "Accepted", "Non-Authoritative Information", "No Content",
    "Reset Content", "Partial Content", "Multi-Status", "Already Reported", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "IM Used", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
     // 300s
    "Multiple Choices", "Moved Permanently", "Found", "See Other", "Not Modified",
    "Use Proxy", "Switch Proxy", "Temporary Redirect", "Permanent Redirect", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
     // 400s
    "Bad Request", "Unauthorized", "Payment Required", "Forbidden", "Not Found",
    "Method Not Allowed", "Not Acceptable", "Proxy Authentication Required", "Request Timeout",
    "Conflict","Gone", "Length Required", "Precondition Failed", "Payload Too Large",
    "URI Too Long", "Unsupported Media Type", "Range Not Satisfiable", "Expectation Failed",
    "I'm a teapot", "","",
    "Misdirected Request", "Unprocessable Entity", "Locked", "Failed Dependency",
    "Too Early", "Upgrade Required", "",
    "Precondition Required", "Too Many Requests","",
    "Request Header Fields Too Large", "", "", "", "", "", "",
    "", "","", "", "", "", "", "", "", "",
    "", "","", "Unavailable For Legal Reasons", "", "", "",
    "", "", "", "", "","", "", "", "", "",
    "", "", "", "", "","", "", "", "", "",
    "", "", "", "", "","", "", "", "", "",
    "", "", "", "", "","", "", "", "", "",
    "", "", "", "", "",
     // 500s
    "Internal Server Error", "Not Implemented", "Bad Gateway", "Service Unavailable",
    "Gateway Timeout", "HTTP Version Not Supported", "Variant Also Negotiates",
    "Insufficient Storage", "Loop Detected", "",
    "Not Extended", "Network Authentication Required", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", ""
};

ps_response* response_init(ps_socket client_socket)
{
    ps_response* response = (ps_response*)calloc(1, sizeof(ps_response));
    response->status = PS_HTTP_SUCCESS;
    response->client_socket = client_socket;
    return response;
}

void response_set_body(ps_response* response, char* body, u32 body_length)
{
    PS_ASSERT(response, "Response is null");
    response->body = body;
    response->content_length = body_length;
}

void response_set_status(ps_response* response, ps_http_response_status status)
{
    response->status = status;
}

void response_push_header(ps_response* response, char* key, char* value)
{
    PS_ASSERT(response, "Response is null");
    ps_response_header* header = (ps_response_header*)malloc(sizeof(ps_response_header));
    header->key = key;
    header->value = value;
    header->next_header = response->base_header;
    response->base_header = header;
}

static void _serialize_formatted(ps_buffer* buffer, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    s32 bytes = vsnprintf(buffer->data + buffer->size, buffer->capacity - buffer->size, format, args);
    buffer->size += bytes;

    va_end(args);
}

static void _serialize_response_headers(ps_buffer* buffer, ps_response* response)
{
    // put the status code and text into the reponse buffer
    _serialize_formatted(buffer, "HTTP/1.1 %i %s\r\n", response->status, response_text[response->status]);

    // put the content length into the response buffer
    _serialize_formatted(buffer, "Content-Length: %i\r\n", response->content_length);

    // serialize all the other fucking headers
    ps_response_header* header = response->base_header;
    while(header)
    {
        _serialize_formatted(buffer, "%s: %s\r\n", header->key, header->value);
        header = header->next_header;
    }

    // put a new line for good looks
    _serialize_formatted(buffer, "\r\n");
}

void ps_respond(ps_response* response)
{
    ps_buffer buffer;
    buffer_init(&buffer, PS_HTTP_REQUEST_INITIAL_BUF_SIZE);

    _serialize_response_headers(&buffer, response);
    if(response->body)
        buffer_push_data(&buffer, response->body, response->content_length);

    printf("%s\n", buffer.data);

    write_to_socket(response->client_socket, &buffer);

    buffer_free(&buffer);
    response_shutdown(response);
}

void response_shutdown(ps_response* response)
{
    PS_ASSERT(response, "Response is null");

    ps_response_header* header = response->base_header;
    while(header)
    {
        ps_response_header* temp = header;
        header = header->next_header;
        free(temp);
    }

    free(response);
}

void response_set_content_type(ps_response* response, char* content_type)
{
    response_push_header(response, "Content-Type", content_type);
}

