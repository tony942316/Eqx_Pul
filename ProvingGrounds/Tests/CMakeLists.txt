cmake_minimum_required(VERSION 3.28)

add_library(Tests STATIC)
target_sources(Tests
    PUBLIC FILE_SET CXX_MODULES FILES
        Tests.cpp
        Basic.cpp
        BreakOut.cpp
        CQuad.cpp
        MVP.cpp
        Texture.cpp
	Text.cpp
        TxQuad.cpp)
target_compile_features(Tests PUBLIC cxx_std_20)
target_link_libraries(Tests PRIVATE Eqx_Pul Eqx_Lib Eqx_TPL)

set_target_properties(Tests PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
