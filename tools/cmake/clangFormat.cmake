function(addClangFormatTargets)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs FILES)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    message("${ARGS_FILES}")

    # Adding clang-format check and formatter if found
    find_program(CLANG_FORMAT "clang-format")
    if(CLANG_FORMAT)
        add_custom_target(
            format
            COMMAND ${CLANG_FORMAT} -i -style=file ${ARGS_FILES}
            COMMENT "Auto formatting of all source files"
            )
    endif()
endfunction()
