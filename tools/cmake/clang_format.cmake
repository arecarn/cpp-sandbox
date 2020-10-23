find_program(
    CLANG_FORMAT
    NAMES clang-format
    DOC "Path to clang-tidy executable"
)

function(clang_format_add_format_targets)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs FORMAT_TARGET_NAME FORMAT_CHECK_TARGET_NAME FILES)
    cmake_parse_arguments(
        ARGS
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )
    if(CLANG_FORMAT)
        add_custom_target(
            ${ARGS_FORMAT_TARGET_NAME}
            COMMAND ${CLANG_FORMAT} -i -style=file ${ARGS_FILES}
            COMMENT "Formatting C and C++ source files"
        )

        add_custom_target(
            ${ARGS_FORMAT_CHECK_TARGET_NAME}
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
    else()
        message(WARNING "clang-format Not Found! Format Targets Not Created.")
    endif()
endfunction()
