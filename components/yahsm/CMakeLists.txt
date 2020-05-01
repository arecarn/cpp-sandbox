add_library(
    yahsm
    INTERFACE
)

target_include_directories(
    yahsm
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
