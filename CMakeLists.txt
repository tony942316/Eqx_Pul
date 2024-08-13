cmake_minimum_required(VERSION 3.28)

project(GlfwMod
    VERSION 0.1.0
    DESCRIPTION "glfw As C++20 Modules"
    LANGUAGES CXX)

add_subdirectory(Dependencies)
add_subdirectory(GlfwMod)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(ProvingGrounds)
endif()
