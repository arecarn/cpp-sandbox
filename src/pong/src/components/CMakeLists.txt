add_library(component_test
    ${CMAKE_CURRENT_SOURCE_DIR}/components.cpp
)

add_library(components INTERFACE)
target_include_directories(components INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
