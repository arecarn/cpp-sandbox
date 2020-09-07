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

include(ccache)
include(cppcheck)
include(clang_tidy)

include(clang_format)
file(
    GLOB_RECURSE C_AND_CPP_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.[ch]pp"
    "${PROJECT_SOURCE_DIR}/src/*.[ch]"
)
clang_format_add_format_cpp_targets(FILES "${C_AND_CPP_SOURCE_FILES}")

include(gersemi)
file(
    GLOB_RECURSE CMAKE_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/CMakeLists.txt"
    "${PROJECT_SOURCE_DIR}/src/*.cmake"
    "${PROJECT_SOURCE_DIR}/tools/*.cmake"
)
gersemi_add_format_cmake_targets(FILES "${CMAKE_SOURCE_FILES}")

add_custom_target(format ALL DEPENDS format_cpp format_cmake)
add_custom_target(format_check DEPENDS format_check_cpp format_check_cmake)

include(get_google_test)
get_google_test()

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
add_subdirectory(src/questions)
