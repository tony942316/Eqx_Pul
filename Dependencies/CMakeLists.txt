cmake_minimum_required(VERSION 3.28)

add_subdirectory(Equinox)

add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

set(GLFW_BUILD_DOCS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES Off CACHE BOOL "" FORCE)
add_subdirectory(glfw)

add_library(stbi STATIC)
target_sources(stbi PRIVATE stbi/stb_image.c)
target_include_directories(stbi PUBLIC stbi)

add_library(stbim STATIC)
target_sources(stbim
    PUBLIC FILE_SET CXX_MODULES FILES
    stbi/stbim.cpp)
target_compile_features(stbim PUBLIC cxx_std_20)
set_target_properties(stbim PROPERTIES
    CXX_STANDARE_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(stbim PRIVATE stbi)
