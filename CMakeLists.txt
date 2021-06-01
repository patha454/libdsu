cmake_minimum_required(VERSION 3.16)
cmake_policy(VERSION 3.16)

set(DSU_H_MAJOR_VERSION 0)
set(DSU_H_MINOR_VERSION 0)
set(DSU_H_PATCH_VERSION 0)

set(DSU_H_DESCRIPTION "Dyanmic software updating solution contained within a library.")

project(
    dsh.h
    VERSION ${DSU_H_MAJOR_VERSION}.${DSU_H_MINOR_VERSION}.${DSU_H_PATCH_VERSION}
    DESCRIPTION ${DSU_H_DESCRIPTION}
    LANGUAGES C
)

add_executable(dsu main.c)
