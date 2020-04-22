add_library(ringbuffer INTERFACE)

target_include_directories(
    ringbuffer
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
