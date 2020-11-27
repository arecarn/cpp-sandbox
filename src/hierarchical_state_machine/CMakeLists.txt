################################################################################
# Library
################################################################################
add_library(hierarchical_state_machine STATIC ${CMAKE_CURRENT_SOURCE_DIR}/hierarchical_state_machine.cpp)
target_include_directories(hierarchical_state_machine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_set_default_compiler_warnings(hierarchical_state_machine)

################################################################################
# Test
################################################################################
add_executable(
    hierarchical_state_machine.test
    ${CMAKE_CURRENT_SOURCE_DIR}/hierarchical_state_machine.test.cpp
)
target_link_libraries(hierarchical_state_machine.test gtest_main hierarchical_state_machine)
create_test(hierarchical_state_machine.test)
