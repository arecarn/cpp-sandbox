cmake_minimum_required(VERSION 3.10.2)

project(cpp-sandbox)
add_subdirectory(external)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/tools/cmake)
include(compiler_flags)


################################################################################
# CMake Settings
################################################################################
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/tools/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/bin)

################################################################################
# CMake Modules Includes
################################################################################
include(ccache)
include(sanitizers)

################################################################################
# Doxygen Documentation Target
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
# cppcheck Static Analysis Target
################################################################################
list(APPEND CPPCHECK_OTHER_ARGS
    "--force"
    "--enable=all"
    "--inconclusive"
    "--force"
    "--inline-suppr"
    "--project=${PROJECT_SOURCE_DIR}/compile_commands.json"
)
set(APPEND CPPCHECK_EXCLUDES
    "${CMAKE_SOURCE_DIR}/excludes"
)
find_package(Cppcheck)

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
add_subdirectory(src)

################################################################################
# clang-format C/C++ formatting
################################################################################
include(target_utils)
get_all_targets(lint_targets "${CMAKE_CURRENT_SOURCE_DIR}/src")

include(clang_lint)
create_clang_tidy_lint_targets(
    TARGETS ${lint_targets}
    CHECK_TARGET_NAME clang_tidy_check
    FIX_TARGET_NAME clang_tidy_fix
)
create_clang_format_lint_targets(
    TARGETS ${lint_targets}
    CHECK_TARGET_NAME clang_format_check
    FIX_TARGET_NAME clang_format_fix
)

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
    "${PROJECT_SOURCE_DIR}/src/CMakeLists.txt"
)
gersemi_add_format_cmake_targets(
    FIX_TARGET_NAME "format_cmake_fix"
    CHECK_TARGET_NAME "format_cmake_check"
    FILES "${CMAKE_SOURCE_FILES}"
)

################################################################################
# Custom Targets
################################################################################
add_custom_target(format_fix ALL DEPENDS clang_format_fix format_cmake_fix)
add_custom_target(format_check DEPENDS clang_format_check format_cmake_check)

