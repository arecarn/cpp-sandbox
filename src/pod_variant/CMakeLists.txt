################################################################################
# Library
################################################################################
add_library(pod_variant INTERFACE)
target_include_directories(pod_variant INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_set_default_compiler_warnings(pod_variant)

################################################################################
# Test
################################################################################
add_executable(
    pod_variant.test
    ${CMAKE_CURRENT_SOURCE_DIR}/pod_variant.test.cpp
)
target_link_libraries(pod_variant.test pod_variant gtest_main)
create_test(pod_variant.test)
