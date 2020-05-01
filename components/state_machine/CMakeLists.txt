add_library(
    state_machine_static
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/state_machine.cpp
)

target_include_directories(
    state_machine_static
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
