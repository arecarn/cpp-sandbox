project(pong)

find_package(SFML 2.4 COMPONENTS system window graphics)

if(SFML_LIBRARIES)
    ############################################################################
    # Executables
    ############################################################################
    add_executable(pong ${CMAKE_CURRENT_SOURCE_DIR}/src/pong.main.cpp)

    ############################################################################
    # Libraries
    ############################################################################
    add_subdirectory(src/components)
    target_link_libraries(pong ${SFML_LIBRARIES} components)
endif()
