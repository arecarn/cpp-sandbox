################################################################################
# Library
################################################################################
add_library(fixed_vector INTERFACE)
target_link_libraries(fixed_vector INTERFACE array span)
target_include_directories(fixed_vector INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_set_default_compiler_warnings(fixed_vector)

################################################################################
# Test
################################################################################
add_executable(fixed_vector.test ${CMAKE_CURRENT_SOURCE_DIR}/fixed_vector.test.cpp)
target_link_libraries(fixed_vector.test fixed_vector gtest_main)
create_test(fixed_vector.test)
