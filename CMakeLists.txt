cmake_minimum_required(VERSION 3.10)
project(tabulardb)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_executable(tabular_db 
    main.c
    kv.h
    helpers.h
)

target_link_libraries(tabular_db PRIVATE ${READLINE_LIBRARY})

add_custom_target(valgrind
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tabular_db
    DEPENDS tabular_db
)
