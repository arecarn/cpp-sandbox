cmake_minimum_required(VERSION 3.10.2)

project(cpp-sandbox)


set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/tools/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/bin)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    # use ccache if it's available
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

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

add_subdirectory(src/array)
add_subdirectory(src/pong)
add_subdirectory(src/ringbuffer)
add_subdirectory(src/span)
add_subdirectory(src/state_machine)
add_subdirectory(src/tagged_union)
add_subdirectory(src/pod_variant)
add_subdirectory(src/yahsm)
