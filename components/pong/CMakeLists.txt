project(pong)

find_package(SFML 2.4 COMPONENTS system window graphics)

add_executable(pong
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pong.cpp)

target_link_libraries(pong ${SFML_LIBRARIES})
message("${SFML_LIBRARIES}")

target_include_directories(pong PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
