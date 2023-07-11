//
// Created by OKAY on 7/6/2023.
//

#include "ps_request.h"
#include "string.h"

#include <stdlib.h>

#define METHOD_GET "GET"
#define METHOD_POST "POST"
#define METHOD_UPDATE "UPDATE"
#define METHOD_DELETE "DELETE"

const char* request_method_to_str(ps_request_method method)
{
    switch (method) {
        case PS_GET:    return METHOD_GET;
        case PS_POST:   return METHOD_POST;
        case PS_UPDATE: return METHOD_UPDATE;
        case PS_DELETE: return METHOD_DELETE;
    }
    
    return "";
}

void parse_raw_request_data(ps_request* request)
{
    const char* delimeter = " ";

    char* temp_buffer = (char*)malloc(request->buffer.length);
    strcpy(temp_buffer, request->buffer.data);

    char* context = NULL;

    // parse the data
    char* method = strtok_s(temp_buffer, delimeter, &context);

    if(strcmp(method, METHOD_GET) == 0)
        request->method = PS_GET;
    else if(strcmp(method, METHOD_POST) == 0)
        request->method = PS_POST;
    else if(strcmp(method, METHOD_UPDATE) == 0)
        request->method = PS_UPDATE;
    else if(strcmp(method, METHOD_DELETE) == 0)
        request->method = PS_DELETE;

    //char* context2 = NULL;
    char* target = strtok_s(context, delimeter, &context);
    request->target = target;

    // NOTE: there's an error when freeing but im pretty sure this may cause a memory leek
    //free(data);
}
