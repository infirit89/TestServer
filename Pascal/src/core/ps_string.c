//
// Created by georg on 7/15/2023.
//

#include "ps_string.h"

#include <stdlib.h>
#include <string.h>

char* ps_string_copy(char* str)
{
    char* copied_str = malloc(strlen(str) + 1);
    strcpy(copied_str, str);
    return copied_str;
}

u8 ps_strings_equal(char* str1, char* str2)
{
    return strcmp(str1, str2) == 0;
}
