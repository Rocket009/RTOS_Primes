cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
set(CMAKE_C_STANDARD 99) 

set(
    SOURCES
    src/main.c
    src/file_io_stubs.c
    src/console.c
    src/config/default/freertos_hooks.c
    src/third_party/rtos/FreeRTOS/Source/list.c
    src/third_party/rtos/FreeRTOS/Source/stream_buffer.c
    src/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_3.c
    src/third_party/rtos/FreeRTOS/Source/queue.c
    src/third_party/rtos/FreeRTOS/Source/timers.c
    src/third_party/rtos/FreeRTOS/Source/FreeRTOS_tasks.c
    src/third_party/rtos/FreeRTOS/Source/event_groups.c
    src/third_party/rtos/FreeRTOS/Source/croutine.c
)

set(
    SOURCE_FILES
    ./src/
    ./src/config/default/
    ./src/config/default/peripheral
    ./src/config/default/library
    ./src/config/default/stdio
    ./src/third_party/rtos/FreeRTOS/Source/include/
)


set(POSIX 1)
set(CMAKE_TOOLCHAIN_FILE posix.cmake)

project(
    ACU_POSIX
    LANGUAGES C CXX ASM
)

add_compile_options(-pedantic -Werror)
add_compile_options(-Wno-error=format-truncation) # suppress warning for snprintf truncation which only occurs in linux builds

add_executable(
    posix_build
    ${SOURCES}
    src/portable/Posix/utils/wait_for_event.c
    src/portable/Posix/port.c
    src/tasks_posix.c
    src/sim_app.c
    src/tasks.c
)

target_include_directories(
    posix_build
    PUBLIC
    ${SOURCE_FILES}
    ./src/portable/Posix
    ./src/portable/Posix/utils
    ./src/include
)

target_link_libraries(
    posix_build 
    PUBLIC
    m 
)

string(CONCAT output_file "../binaries/PosixRTOS" )





