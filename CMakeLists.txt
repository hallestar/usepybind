cmake_minimum_required(VERSION 3.11)

project(trypybind)

set(PYBIND11_FINDPYTHON ON)
set(THIRD_DIR ${CMAKE_SOURCE_DIR}/thirdparty)

find_package(Python3
             COMPONENTS
             Interpreter Development
             REQUIRED)

message("== CMAKE_PROJECT_NAME: ${CMAKE_PROJECT_NAME}")
message("== Python3_FOUND: ${Python3_FOUND}")
message("== Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message("== Python3_Development.Module_FOUND: ${Python3_Development.Module_FOUND}")
message("== Python3_Development_FOUND: ${Python3_Development_FOUND}")
message("== Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message("== Python3_LIBRARY_DIRS: ${Python3_LIBRARY_DIRS}")
message("== Python3_LIBRARY: ${Python3_LIBRARY}")
message("== Python3_LIBRARIES: ${Python3_LIBRARIES}")
message("== CMAKE_COMMAND: ${CMAKE_COMMAND}")

add_custom_target(3party)

add_subdirectory(${THIRD_DIR}/pybind11)

include_directories("src")

aux_source_directory(src/core SOURCE_FILES)

set(PLUGIN_NAME pybroker)

add_library(${PLUGIN_NAME}
            SHARED
            ${SOURCE_FILES})
#target_include_directories(${PLUGIN_NAME} PUBLIC ${CMAKE_BINARY_DIR}/)


set_target_properties(${PLUGIN_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${PLUGIN_NAME} PROPERTIES COMPILE_FLAGS "-DLDIMPL")

# 构建benchmark
include(FetchContent)

set(GOOGLETEST_GIT_URL https://github.com/google/googletest.git)
set(GOOGLETEST_GIG_TAG release-1.11.0)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
        )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
        )
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build"
        )
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include"
            )
endif()

add_custom_command(TARGET ${PLUGIN_NAME}
        PRE_BUILD
        WORKING_DIRECTORY ${THIRD_DIR}/benchmark
        COMMAND ${CMAKE_COMMAND} -E echo "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr"
        COMMAND ${CMAKE_COMMAND} -E make_directory "build"
        COMMAND ${CMAKE_COMMAND} -E chdir "build" "${CMAKE_COMMAND}" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} ../
        COMMAND ${CMAKE_COMMAND} --build "build" --config ${CMAKE_BUILD_TYPE}
        # copy
        COMMAND ${CMAKE_COMMAND} -E make_directory "lib"
        COMMAND ${CMAKE_COMMAND} -E copy build/src/*.a "lib")

add_subdirectory(thirdparty/benchmark)

link_directories(${THIRD_DIR}/benchmark/lib/)

target_link_libraries(${PLUGIN_NAME}
        PRIVATE pybind11::embed)

include(CMakePackageConfigHelpers)


install(TARGETS ${PLUGIN_NAME}
        EXPORT ${PLUGIN_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

install(EXPORT ${PLUGIN_NAME}Targets
        FILE ${PLUGIN_NAME}Targets.cmake
        NAMESPACE ${PLUGIN_NAME}::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PLUGIN_NAME}
        )

install(FILES src/core/pybroker.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#add_subdirectory(thirdparty)
add_subdirectory(test)


