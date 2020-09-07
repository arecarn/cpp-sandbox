function(gersemi_add_format_cmake_targets)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs FILES)
    cmake_parse_arguments(
        ARGS
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    # Adding clang-format check and formatter if found
    find_program(GERSEMI "gersemi")
    if(GERSEMI)
        add_custom_target(
            format_cmake
            COMMAND ${GERSEMI} -i ${ARGS_FILES}
            COMMENT "Formatting CMake source files"
        )

        add_custom_target(
            format_check_cmake
            COMMAND ${GERSEMI} -c ${ARGS_FILES}
            COMMENT "Checking formatting of CMake source files"
        )
    endif()
endfunction()
