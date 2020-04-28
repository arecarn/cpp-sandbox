add_library(
    tagged_union_static
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tagged_union.cpp
)

target_include_directories(
    tagged_union_static
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
