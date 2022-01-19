set(EXECUTABLE_NAME invoke_bench)
add_executable(${EXECUTABLE_NAME} invoke_bench.cpp)

set_target_properties(${EXECUTABLE_NAME}
        PROPERTIES CXX_STANDARD 17
        COMPILE_DEFINITIONS BUILDER_STATIC_DEFINE)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

link_directories(${CMAKE_BINARY_DIR})

target_link_libraries(${EXECUTABLE_NAME}
        PUBLIC benchmark::benchmark
        PUBLIC ${PLUGIN_NAME}
        PRIVATE pybind11::embed)
