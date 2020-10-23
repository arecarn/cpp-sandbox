project(cpp-sandbox)

################################################################################
# CMake Settings
################################################################################
cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/tools/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/bin)


################################################################################
# C++ Settings
################################################################################
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

################################################################################
# CMake Modules Includes
################################################################################
include(ccache)
include(sanitizers)
include(compiler_warnings)

################################################################################
#  Doxygen Documentation Target
################################################################################
find_package(Doxygen)
if(DOXYGEN_FOUND)
    doxygen_add_docs(
        doxygen
        ${PROJECT_SOURCE_DIR}/src
        COMMENT "Generating Doxygen Documentation"
    )
endif()

################################################################################
# Clang Format Source Formatting Target
################################################################################
include(clang_format)
file(
    GLOB_RECURSE C_AND_CPP_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.[ch]pp"
    "${PROJECT_SOURCE_DIR}/src/*.[ch]"
)
clang_format_add_format_cpp_targets(FILES "${C_AND_CPP_SOURCE_FILES}")

################################################################################
# Gesermi CMake Formatting Target
################################################################################
include(gersemi)
list(APPEND CMAKE_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/CMakeLists.txt
)
file(
    GLOB_RECURSE CMAKE_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cmake"
    "${PROJECT_SOURCE_DIR}/tools/*.cmake"
)
gersemi_add_format_cmake_targets(FILES "${CMAKE_SOURCE_FILES}")

################################################################################
# Custom Targets
################################################################################
add_custom_target(format ALL DEPENDS format_cpp format_cmake)
add_custom_target(format_check DEPENDS format_check_cpp format_check_cmake)

################################################################################
# Testing Settings
################################################################################
enable_testing()
macro(create_test target)
    add_test(NAME ${target} COMMAND ${target})
endmacro()

################################################################################
# Subdirectories
################################################################################
add_subdirectory(external)
add_subdirectory(src)
