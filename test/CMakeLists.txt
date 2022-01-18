macro(add_executable_case executable_name source_files)
    message("== add executable case: [${executable_name}]")
    add_executable(${executable_name} ${source_files})

    set_target_properties(${executable_name}
                          PROPERTIES CXX_STANDARD 17
                          COMPILE_DEFINITIONS BUILDER_STATIC_DEFINE)

    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    link_directories(${CMAKE_BINARY_DIR})

    target_link_libraries(${executable_name}
                          PUBLIC ${PLUGIN_NAME}
                          PRIVATE pybind11::embed)

endmacro(add_executable_case)

add_subdirectory(embed)
add_subdirectory(littleone)
add_subdirectory(invoke_bench)
