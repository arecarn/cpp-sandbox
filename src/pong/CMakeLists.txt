project(pong)

find_package(SFML 2.4 COMPONENTS system window graphics)

add_executable(pong
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pong.main.cpp)

add_subdirectory(src/components)

target_link_libraries(pong
    ${SFML_LIBRARIES}
    components
    )
