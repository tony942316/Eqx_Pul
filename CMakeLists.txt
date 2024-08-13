cmake_minimum_required(VERSION 3.28)

project(glfwMod
    VERSION 0.1.0
    DESCRIPTION "glfw As C++20 Modules"
    LANGUAGES CXX)

set(GLFW_BUILD_DOCS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES Off CACHE BOOL "" FORCE)
add_subdirectory(Dependencies/glfw)

add_executable(Main)
target_sources(Main PRIVATE Main.cpp)
set_target_properties(Main PROPERTIES
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

