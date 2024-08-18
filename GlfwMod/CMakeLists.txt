cmake_minimum_required(VERSION 3.28)

add_library(GlfwMod STATIC)
target_sources(GlfwMod
    PUBLIC FILE_SET CXX_MODULES FILES
        GlfwMod.cpp
        Keyboard.cpp
        Mouse.cpp
        Renderer.cpp
        Shader.cpp
        Texture.cpp
        VertexArray.cpp
        Window.cpp)
target_compile_features(GlfwMod PUBLIC cxx_std_20)
set_target_properties(GlfwMod PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(GlfwMod PRIVATE glfw glad stbim EquinoxMod)
target_link_libraries(GlfwMod PUBLIC GMF)
