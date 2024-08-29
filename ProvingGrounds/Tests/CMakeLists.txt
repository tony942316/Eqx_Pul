cmake_minimum_required(VERSION 3.28)

add_library(GlfwModTests STATIC)
target_sources(GlfwModTests
    PUBLIC FILE_SET CXX_MODULES FILES
        Tests.cpp
        Basic.cpp
        CQuad.cpp
        MVP.cpp
        Texture.cpp)
target_compile_features(GlfwModTests PUBLIC cxx_std_20)
target_link_libraries(GlfwModTests PRIVATE GlfwMod EquinoxMod)
target_compile_options(GlfwModTests PRIVATE -Wodr)
target_link_options(GlfwModTests PRIVATE -Wodr)

set_target_properties(GlfwModTests PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
