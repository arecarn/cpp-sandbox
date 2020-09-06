# library
################################################################################
add_library(tagged_union STATIC ${CMAKE_CURRENT_SOURCE_DIR}/tagged_union.cpp)
target_include_directories(tagged_union PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test
################################################################################
add_executable(
    tagged_union.test
    ${CMAKE_CURRENT_SOURCE_DIR}/tagged_union.test.cpp
)
target_link_libraries(tagged_union.test gtest_main tagged_union)
create_test(tagged_union.test)
