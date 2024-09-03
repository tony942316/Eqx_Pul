cmake_minimum_required(VERSION 3.28)

project(Eqx_Pul
    VERSION 0.1.0
    DESCRIPTION "C++20 Game Framework"
    LANGUAGES C CXX)

add_subdirectory(Dependencies/)
add_subdirectory(Pul/include/Eqx/Pul/)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(ProvingGrounds/)
endif()
