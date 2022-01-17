cmake_minimum_required(VERSION 3.4...3.18)

project(trypybind)

set(PYBIND11_FINDPYTHON ON)

find_package(
        Python3
        COMPONENTS
        Interpreter Development
        REQUIRED)

add_subdirectory(thirdparty/pybind11)

message("== CMAKE_PROJECT_NAME: ${CMAKE_PROJECT_NAME}")
message("== Python3_FOUND: ${Python3_FOUND}")
message("== Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message("== Python3_Development.Module_FOUND: ${Python3_Development.Module_FOUND}")
message("== Python3_Development_FOUND: ${Python3_Development_FOUND}")
message("== Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message("== Python3_LIBRARY_DIRS: ${Python3_LIBRARY_DIRS}")
message("== Python3_LIBRARY: ${Python3_LIBRARY}")
message("== Python3_LIBRARIES: ${Python3_LIBRARIES}")

include_directories("src")

aux_source_directory(src/core SOURCE_FILES)

set(PLUGIN_NAME pybroker)

#pybind11_add_module(${PLUGIN_NAME} ${SOURCE_FILES})
add_library(${PLUGIN_NAME}
        SHARED
        ${SOURCE_FILES})
#target_include_directories(${PLUGIN_NAME} PUBLIC ${CMAKE_BINARY_DIR}/)


#set_property(TARGET ${PLUGIN_NAME} PROPERTY CXX_STANDARD 17)
set_target_properties(${PLUGIN_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${PLUGIN_NAME} PROPERTIES COMPILE_FLAGS "-DEFIMPL")

target_link_libraries(${PLUGIN_NAME}
        PRIVATE pybind11::embed)

add_subdirectory(test)



