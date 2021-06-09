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

add_subdirectory(libdsu)


#set(DSU_TEST_SERVER_SRC_DIR ${PROJECT_SOURCE_DIR}/src/test-server)
#add_executable(test-server
#    ${DSU_TEST_SERVER_SRC_DIR}/test-server.c
#)
#set_property(TARGET test-server PROPERTY C_STANDARD 11)
#target_link_libraries(test-server PRIVATE dsu)
