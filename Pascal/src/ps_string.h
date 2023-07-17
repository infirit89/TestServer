//
// Created by georg on 7/15/2023.
//

#ifndef PASCAL_PS_STRING_H
#define PASCAL_PS_STRING_H

#include "ps_defs.h"

// has to be freed by the user
char* ps_string_copy(char* str);
b8 ps_strings_equal(char* str1, char* str2);

#endif //PASCAL_PS_STRING_H
