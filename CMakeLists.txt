cmake_minimum_required(VERSION 3.10.2)
project(cpp-libs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/tools/cmake)

include(clangTidy)
include(clangFormat)
file(GLOB_RECURSE
    CXX_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.[ch]pp"
    "${PROJECT_SOURCE_DIR}/src/*.[ch]"
)
addClangFormatTargets(FILES "${CXX_SOURCE_FILES}")

include(getGoogleTest)
getGoogleTest()

enable_testing()

macro(create_test target)
    add_test(NAME ${target} COMMAND ${target})
endmacro()

add_subdirectory(test/array)
add_subdirectory(test/ringbuffer)
