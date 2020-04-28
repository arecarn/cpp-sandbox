add_library(
    template_static
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/template.cpp
)

target_include_directories(
    template_static
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
