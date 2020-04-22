add_executable(test_array
    ${CMAKE_CURRENT_SOURCE_DIR}/test_array.cpp
)

target_link_libraries(test_array
    array
    gtest_main
)

create_test(test_array)
