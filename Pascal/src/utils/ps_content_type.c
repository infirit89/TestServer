//
// Created by georg on 7/16/2023.
//

#include "ps_content_type.h"

struct sc_map_str extension_content_type_map;

void init_extension_content_type_map()
{
    sc_map_init_str(&extension_content_type_map, EXTENSION_CONTNENT_MAP_CAPACITY, 0);
    sc_map_put_str(&extension_content_type_map, EXTENSION_HTML, "text/html");
    sc_map_put_str(&extension_content_type_map, EXTENSION_CSS, "text/css");
    sc_map_put_str(&extension_content_type_map, EXTENSION_JAVASCRIPT, "application/javascript");
}

bool try_get_content_type(const char* extension, char** content_type)
{
    *content_type = (char*)sc_map_get_str(&extension_content_type_map, extension);
    return sc_map_found(&extension_content_type_map);
}

extern void term_extension_content_type_map()
{
    sc_map_term_str(&extension_content_type_map);
}