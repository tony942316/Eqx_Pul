cmake_minimum_required(VERSION 3.28)

add_subdirectory(Equinox)

add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

set(GLFW_BUILD_DOCS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES Off CACHE BOOL "" FORCE)
add_subdirectory(glfw)

add_custom_target("CT_glm"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/glm.pcm")

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/glm.pcm"
    COMMENT "Build glm Header Unit"
    COMMAND clang++ -std=c++20
        $<TARGET_PROPERTY:GMF,INTERFACE_COMPILE_OPTIONS>
        -I${CMAKE_CURRENT_SOURCE_DIR}/glm/glm
        -xc++-system-header --precompile glm.hpp gtc/matrix_transform.hpp gtc/type_ptr.hpp
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/glm/glm/glm.hpp"
    COMMAND_EXPAND_LISTS)

add_library(HUglm INTERFACE)
add_dependencies(HUglm CT_glm)
target_include_directories(HUglm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm)
target_compile_options(HUglm INTERFACE
    -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/glm.pcm
    -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/matrix_transform.pcm
    -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/type_ptr.pcm)

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
target_link_libraries(stbim PUBLIC GMF)
