cmake_minimum_required(VERSION 3.22.1)
project(Pascal C)

set(CMAKE_C_STANDARD 11)

add_executable(Pascal src/main.c src/ps_defs.h src/ps_assert.h src/ps_server.h src/ps_server.c src/pascal.h src/pascal.c src/ps_file.h src/ps_file.c src/ps_buffer.h src/ps_buffer.c src/ps_request.h src/ps_request.c src/ps_response.h src/ps_response.c src/ps_socket_utils.h src/ps_socket_utils.c src/sc/sc_map.h src/sc/sc_map.c src/ps_queue.h src/ps_queue.c src/ps_tests.c src/ps_tests.h  src/ps_debugbreak.h src/ps_debugbreak.h src/ps_log.c src/ps_log.h)

if(WIN32)
    target_link_libraries(Pascal PRIVATE wsock32 ws2_32)
endif ()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DPS_DEBUG) 
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DPS_RELEASE)
endif()

file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/Assets)
file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})