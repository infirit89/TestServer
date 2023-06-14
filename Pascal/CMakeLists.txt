cmake_minimum_required(VERSION 3.22.1)
project(Pascal C)

set(CMAKE_C_STANDARD 11)

add_executable(Pascal src/main.c src/ps_defs.h src/ps_assert.h src/ps_server.h src/ps_server.c)

if(WIN32)
    target_link_libraries(Pascal wsock32 ws2_32)
endif ()