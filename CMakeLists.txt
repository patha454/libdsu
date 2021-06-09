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

set(LIBDSU_SOURCE_DIR ${PROJECT_SOURCE_DIR}/libdsu/src)

add_library(dsu SHARED
    ${LIBDSU_SOURCE_DIR}/socket.c
)

target_compile_options(dsu PRIVATE -W -Wall -Wextra -Wpedantic -Werror)

set_target_properties(dsu PROPERTIES C_STANDARD 11)

target_include_directories(dsu
    PRIVATE
        ${LIBDSU_SOURCE_DIR}
    PUBLIC
        $<INSTALL_INTERFACE:libdsu/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libdsu/include>
)

include(GNUInstallDirs)

install(TARGETS dsu
    EXPORT libdsu
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT libdsu
    NAMESPACE
        libdsu::
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/libdsu
)

set(DSU_TEST_SERVER_SRC_DIR ${PROJECT_SOURCE_DIR}/test-server)
add_executable(test-server
    ${DSU_TEST_SERVER_SRC_DIR}/test-server.c
)
set_property(TARGET test-server PROPERTY C_STANDARD 11)
target_link_libraries(test-server PRIVATE dsu)

install(TARGETS test-server
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
