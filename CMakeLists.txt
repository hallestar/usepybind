cmake_minimum_required(VERSION 3.4...3.18)

project(trypybind)

find_package(
        Python3
        COMPONENTS
        Interpreter Development
        REQUIRED)

add_subdirectory(thirdparty/pybind11)

message("== Python3_FOUND: ${Python3_FOUND}")
message("== Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message("== Python3_Development.Module_FOUND: ${Python3_Development.Module_FOUND}")
message("== Python3_Development_FOUND: ${Python3_Development_FOUND}")
message("== Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message("== Python3_LIBRARY_DIRS: ${Python3_LIBRARY_DIRS}")
message("== Python3_LIBRARY: ${Python3_LIBRARY}")
message("== Python3_LIBRARIES: ${Python3_LIBRARIES}")

aux_source_directory(src SOURCE_FILES)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

pybind11_add_module(pybroker)

target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE pybind11::embed)

