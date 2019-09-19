add_executable(test_array
    ${CMAKE_CURRENT_SOURCE_DIR}/test_array.cpp
)

target_include_directories(test_array
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(test_array
    gtest_main
)

create_test(test_array)
