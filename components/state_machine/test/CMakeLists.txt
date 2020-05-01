add_executable(state_machine_test
    ${CMAKE_CURRENT_SOURCE_DIR}/state_machine_test.cpp
)

target_link_libraries(
    state_machine_test
    gtest_main
    state_machine_static
)

create_test(state_machine_test)
