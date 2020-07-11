# Library
################################################################################
add_library(
    state_machine
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/state_machine.cpp
)
target_link_libraries(state_machine
    tagged_union
    ringbuffer
)
target_include_directories(
    state_machine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Test
################################################################################
add_executable(state_machine.test
    ${CMAKE_CURRENT_SOURCE_DIR}/state_machine.test.cpp
)
target_link_libraries(state_machine.test
    state_machine
    gtest_main
)
create_test(state_machine.test)
