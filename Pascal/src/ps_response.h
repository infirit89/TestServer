//
// Created by OKAY on 7/8/2023.
//

#ifndef PASCAL_PS_RESPONSE_H
#define PASCAL_PS_RESPONSE_H

#include "ps_defs.h"

typedef enum ps_http_response_status
{
    // 100S
    PS_HTTP_CONTINUE = 100,
    PS_HTTP_SWITCHING_PROTOCOLS = 101,
    PS_HTTP_PROCESSING = 102,
    PS_HTTP_EARLY_HINTS = 103,

    // 200S
    PS_HTTP_SUCCESS = 200,
    PS_HTTP_CREATED = 201,
    PS_HTTP_ACCEPTED = 202,
    PS_HTTP_NON_AUTHORATIVE_INFORMATION = 203,
    PS_HTTP_NO_CONTENT = 204,
    PS_HTTP_RESET_CONTENT = 205,
    PS_HTTP_PARTIAL_CONTENT = 206,
    PS_HTTP_MULTI_STATUS = 207,
    PS_HTTP_ALREADY_REPORTED = 208,
    PS_HTTP_IM_USED = 226,

    // 300S
    PS_HTTP_MULTIPLE_CHOICES = 300,
    PS_HTTP_MOVED_PERMANENTLY = 301,
    PS_HTTP_FOUND = 302,
    PS_HTTP_SEE_OTHER = 303,
    PS_HTTP_NOT_MODIFIED = 304,
    PS_HTTP_USE_PROXY = 305,
    PS_HTTP_SWITCHING_PROXY = 306,
    PS_HTTP_TEMPORARY_REDIRECT = 307,
    PS_HTTP_PERMENANT_REDIRECT = 308,

    // 400s
    PS_HTTP_BAD_REQUEST = 400,
    PS_HTTP_UNAUTHORIZED = 401,
    PS_HTTP_PAYMENT_REQUIRED = 402,
    PS_HTTP_FORBIDDEN = 403,
    PS_HTTP_NOT_FOUND = 404,
    PS_HTTP_METHOD_NOT_ALLOWED = 405,
    PS_HTTP_NOT_ACCEPTABLE = 406,
    PS_HTTP_PROXY_AUTHENTICATION_REQUIRED = 407,
    PS_HTTP_REQUEST_TIMEOUT = 408,
    PS_HTTP_CONFLICT = 409,
    PS_HTTP_GONE = 410,
    PS_HTTP_LENGTH_REQUIRED = 411,
    PS_HTTP_PRECONDITION_FAILED = 412,
    PS_HTTP_PAYLOAD_TOO_LARGE = 413,
    PS_HTTP_URI_TOO_LONG = 414,
    PS_HTTP_UNSUPPORTED_MEDIA_TYPE = 415,
    PS_HTTP_RANGE_NOT_SATISFIABLE = 416,
    PS_HTTP_EXPECTATION_FAILED = 417,
    PS_HTTP_IM_A_TEAPOT = 418,
    PS_HTTP_MISDIRECTED_REQUEST = 421,
    PS_HTTP_UNPROCESSABLE_ENTITY = 422,
    PS_HTTP_LOCKED = 423,
    PS_HTTP_FAILED_DEPENDENCY = 424,
    PS_HTTP_TOO_EARLY = 425,
    PS_HTTP_UPGRADE_REQUIRED = 426,
    PS_HTTP_PRECONDITION_REQUIRED = 428,
    PS_HTTP_TOO_MANY_REQUESTS = 429,
    PS_HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
    PS_HTTP_UNAVAILABLE_FOR_LEGAL_REASONS = 451,

    // 500S
    PS_HTTP_INTERNAL_SERVER_ERROR = 500,
    PS_HTTP_NOT_IMPLEMENTED = 501,
    PS_HTTP_BAD_GATEWAY = 502,
    PS_HTTP_SERVICE_UNAVAILABLE = 503,
    PS_HTTP_GATEWAY_TIMEOUT = 504,
    PS_HTTP_VERSION_NOT_SUPPORTED = 505,
    PS_HTTP_VARIANT_ALSO_NEGOTIATES = 506,
    PS_HTTP_INSUFFICIENT_STORAGE = 507,
    PS_HTTP_LOOP_DETECTED = 508,
    PS_HTTP_NOT_EXTENDED = 510,
    PS_HTTP_NETWORK_AUTHENTICATION_REQUIRED = 511,
} ps_http_response_status;

typedef struct ps_response_header
{
    char* key;
    char* value;
    struct ps_response_header* next_header;
} ps_response_header;

typedef struct ps_response
{
    ps_socket client_socket;
    ps_http_response_status status;
    ps_response_header* base_header;
    char* body;
    u32 content_length;

} ps_response;

//const char* ps_http_response_status_to_str(ps_http_response_status status);
ps_response* response_init(ps_socket client_socket);
void response_shutdown(ps_response* response);
void response_set_content_type(ps_response* response, char* content_type);
void response_set_body(ps_response* response, char* body, u32 body_length);
void response_push_header(ps_response* response, char* key, char* value);
void ps_respond(ps_response* response);
void response_set_status(ps_response* response, ps_http_response_status status);

#endif //PASCAL_PS_RESPONSE_H
