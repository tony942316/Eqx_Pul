cmake_minimum_required(VERSION 3.28)

add_executable(ProvingGrounds)
target_sources(ProvingGrounds PRIVATE Main.cpp)
set_target_properties(ProvingGrounds PROPERTIES
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(ProvingGrounds PRIVATE GlfwMod EquinoxMod)
