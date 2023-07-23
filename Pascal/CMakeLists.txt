cmake_minimum_required(VERSION 3.22.1)
project(Pascal C)

set(CMAKE_C_STANDARD 11)

add_executable(Pascal 
                tests/server/ps_server_tests.c 
                src/core/ps_defs.h 
                src/core/ps_assert.h 
                src/server/ps_server.h 
                src/server/ps_server.c 
                src/core/pascal.h 
                src/core/pascal.c 
                src/utils/ps_file.h 
                src/utils/ps_file.c 
                src/utils/ps_buffer.h 
                src/utils/ps_buffer.c 
                src/server/ps_request.h 
                src/server/ps_request.c 
                src/server/ps_response.h 
                src/server/ps_response.c 
                src/utils/ps_socket_utils.h 
                src/utils/ps_socket_utils.c 
                vendor/sc/sc_map.h 
                vendor/sc/sc_map.c 
                src/utils/ps_queue.h 
                src/utils/ps_queue.c 
                tests/queue/ps_queue_tests.c 
                tests/queue/ps_queue_tests.h 
                src/core/ps_debugbreak.h 
                src/core/ps_debugbreak.h 
                src/core/ps_log.c 
                src/core/ps_log.h 
                src/core/ps_string.c 
                src/core/ps_string.h 
                src/utils/ps_content_type.h 
                src/utils/ps_content_type.c 
                vendor/vec/vec.c 
                vendor/vec/vec.h 
                vendor/vec/vec.h 
                tests/main.c 
                tests/server/ps_queue_server_tests.h 
                src/events/ps_event_manager.c 
                src/events/ps_event_manager.h 
                tests/event_manager/ps_event_manager_tests.c 
                tests/event_manager/ps_event_manager_tests.h 
                src/thread/ps_mutex.c 
                src/thread/ps_mutex.h 
                src/platform/platform.h 
                src/thread/ps_thread.c 
                src/thread/ps_thread.h 
                src/platform/platform.c 
                src/thread/ps_condition_variable.c 
                src/thread/ps_condition_variable.h 
                src/thread/ps_thread_pool.c 
                src/thread/ps_thread_pool.h 
                src/thread/ps_thread_pool.h)

target_include_directories(Pascal PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/vendor")

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