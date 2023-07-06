cmake_minimum_required(VERSION 3.22.1)
project(Pascal C)

set(CMAKE_C_STANDARD 11)

add_executable(Pascal src/main.c src/ps_defs.h src/ps_assert.h src/ps_server.h src/ps_server.c src/pascal.h src/pascal.c src/ps_file.h src/ps_file.c src/ps_buffer.h src/ps_buffer.c)

if(WIN32)
    target_link_libraries(Pascal PRIVATE wsock32 ws2_32)
endif ()

if(CMAKE_BUILD_TYPE STREQUAL "Debug") 	
    add_definitions(-DPS_DEBUG) 
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DPS_RELEASE)
endif()

file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})