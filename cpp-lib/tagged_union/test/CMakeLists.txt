add_executable(tagged_union_test
    ${CMAKE_CURRENT_SOURCE_DIR}/tagged_union_test.cpp
)

target_link_libraries(
    tagged_union_test
    gtest_main
    tagged_union_static
)

create_test(tagged_union_test)
