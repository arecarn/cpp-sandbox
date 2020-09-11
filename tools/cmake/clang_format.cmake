function(clang_format_add_format_cpp_targets)
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
    find_program(CLANG_FORMAT clang-format)
    if(CLANG_FORMAT)
        add_custom_target(
            format_cpp
            COMMAND ${CLANG_FORMAT} -i -style=file ${ARGS_FILES}
            COMMENT "Formatting C and C++ source files"
        )

        add_custom_target(
            format_check_cpp
            COMMAND
                ${CLANG_FORMAT} -style=file -output-replacements-xml
                ${ARGS_FILES}
                # print output
                | tee ${CMAKE_BINARY_DIR}/check_format_file.txt | grep -c
                "replacement " | tr -d "[:cntrl:]" && echo
                " replacements necessary"
            # WARNING: fix to stop with error if there are problems
            COMMAND
                ! grep -c "replacement "
                ${CMAKE_BINARY_DIR}/check_format_file.txt > /dev/null
            COMMENT "Checking formatting of C and C++ source files"
        )
    endif()
endfunction()
