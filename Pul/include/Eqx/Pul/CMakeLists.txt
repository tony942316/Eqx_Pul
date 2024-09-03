cmake_minimum_required(VERSION 3.28)

add_library(Eqx_Pul STATIC)
target_sources(Eqx_Pul
    PUBLIC FILE_SET CXX_MODULES FILES
        Eqx_Pul.cpp
        CQuad.cpp
        Keyboard.cpp
        Mouse.cpp
        Renderer.cpp
        Shader.cpp
        Texture.cpp
        TxQuad.cpp
        VertexArray.cpp
        Window.cpp)
target_compile_features(Eqx_Pul PUBLIC cxx_std_20)
set_target_properties(Eqx_Pul PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Eqx_Pul PRIVATE Eqx_TPL Eqx_Lib)
