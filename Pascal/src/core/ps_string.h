//
// Created by georg on 7/15/2023.
//

#ifndef PASCAL_PS_STRING_H
#define PASCAL_PS_STRING_H

#include "ps_defs.h"

// TODO:
//typedef struct ps_string
//{
//    char* data;
//    u32 size;
//    u32 capatity;
//
//} ps_string;

// has to be freed by the user
char* ps_string_copy(char* str);
u8 ps_strings_equal(char* str1, char* str2);

#endif //PASCAL_PS_STRING_H
