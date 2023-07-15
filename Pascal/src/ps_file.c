//
// Created by OKAY on 6/21/2023.
//
#include "ps_file.h"
#include "ps_log.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* path)
{
    FILE* file_handle = fopen(path, "r");
    if(!file_handle)
    {
        PS_ERROR("Couldn't open the file");
        return NULL;
    }

    fseek(file_handle, 0, SEEK_END);
    long file_size = ftell(file_handle);
    if(file_size == -1)
    {
        PS_ERROR("Couldn't read from file");
        return NULL;
    }

    fseek(file_handle, 0, SEEK_SET);
    char* data = (char*) malloc(sizeof(char) * file_size);
    size_t result = fread(data, 1, file_size, file_handle);
//    if(result != file_size - 1)
//    {
//        printf("Error reading from file");
//        fclose(file_handle);
//        free(data);
//        return NULL;
//    }

    data[result] = '\0';
    fclose(file_handle);
    return data;
}

char* get_extension(char* file_path)
{
    char* extension = strrchr(file_path, '.');
    return extension;
}
