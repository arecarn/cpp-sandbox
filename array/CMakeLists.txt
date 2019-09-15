project(array)

add_library(array
    ${CMAKE_CURRENT_SOURCE_DIR}/src/array.cpp
)

target_include_directories(array
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(test_array
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_array.cpp
)

target_link_libraries(test_array
    gtest_main
    array
)
