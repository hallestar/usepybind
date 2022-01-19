macro(add_executable_case EXECUTABLE_NAME SOURCE_FILES)
    message("== add executable case: [${EXECUTABLE_NAME}]")
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

    set_target_properties(${EXECUTABLE_NAME}
                          PROPERTIES CXX_STANDARD 17
                          COMPILE_DEFINITIONS BUILDER_STATIC_DEFINE)

    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    link_directories(${CMAKE_BINARY_DIR})

    target_link_libraries(${EXECUTABLE_NAME}
                          PUBLIC ${PLUGIN_NAME}
                          PRIVATE pybind11::embed)

endmacro(add_executable_case)

add_subdirectory(embed)
add_subdirectory(littleone)
add_subdirectory(invoke_bench)
