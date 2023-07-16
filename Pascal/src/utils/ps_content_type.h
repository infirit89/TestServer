//
// Created by georg on 7/16/2023.
//

#ifndef PASCAL_PS_CONTENT_TYPE_H
#define PASCAL_PS_CONTENT_TYPE_H

#include "../sc/sc_map.h"

// NOTE: this should only be used by the ps_server
// i didnt put it there because it was getting a bit cluttered
extern struct sc_map_str extension_content_type_map;

// text/html
// text/css
// application/javascript

#define EXTENSION_CONTNENT_MAP_CAPACITY 3

#define EXTENSION_HTML          ".html"
#define EXTENSION_CSS           ".css"
#define EXTENSION_JAVASCRIPT    ".js"

extern void init_extension_content_type_map();

extern bool try_get_content_type(const char* extension, char** content_type);

extern void term_extension_content_type_map();

#endif //PASCAL_PS_CONTENT_TYPE_H
