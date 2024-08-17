cmake_minimum_required(VERSION 3.28)

message(STATUS "glfwMod: Proving Grounds")

add_executable(ProvingGrounds)
target_sources(ProvingGrounds PRIVATE Main.cpp)
target_compile_features(ProvingGrounds PRIVATE cxx_std_20)
set_target_properties(ProvingGrounds PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(ProvingGrounds PRIVATE GlfwMod EquinoxMod)

add_custom_command(TARGET ProvingGrounds PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources
        $<TARGET_FILE_DIR:ProvingGrounds>
    COMMENT "Copying Resources!")

add_custom_command(TARGET ProvingGrounds PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Genxpr: $<TARGET_FILE_DIR:ProvingGrounds>"
    COMMENT "Printing Generator Expression")
