cmake_minimum_required(VERSION 3.16)
cmake_policy(VERSION 3.16)

set(DSU_H_MAJOR_VERSION 0)
set(DSU_H_MINOR_VERSION 0)
set(DSU_H_PATCH_VERSION 0)

set(DSU_H_DESCRIPTION "Dyanmic software updating solution contained within a library.")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    dsh.h
    VERSION ${DSU_H_MAJOR_VERSION}.${DSU_H_MINOR_VERSION}.${DSU_H_PATCH_VERSION}
    DESCRIPTION ${DSU_H_DESCRIPTION}
    LANGUAGES C
)

add_compile_options(-W -Wall -Wextra -Wpedantic -Werror)

set(DSU_DEBUG_SRC_PATH ${PROJECT_SOURCE_DIR}/src/dsu)
add_executable(dsu
    ${DSU_DEBUG_SRC_PATH}/server.c
    ${DSU_DEBUG_SRC_PATH}/socket.c
)
set_property(TARGET dsu PROPERTY C_STANDARD 11)
target_include_directories(dsu PRIVATE ${PROJECT_SOURCE_DIR}/include)
