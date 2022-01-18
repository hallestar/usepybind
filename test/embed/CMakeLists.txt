add_executable(test_embbed case_embed.cpp)

set_property(TARGET test_embbed PROPERTY CXX_STANDARD 17)

set_target_properties(test_embbed PROPERTIES COMPILE_DEFINITIONS BUILDER_STATIC_DEFINE)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

link_directories(${CMAKE_BINARY_DIR})

target_link_libraries(test_embbed
        PUBLIC ${PLUGIN_NAME}
        PRIVATE pybind11::embed)

