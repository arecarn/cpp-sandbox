################################################################################
# Iterate through the targets, extracting the sources, headers, and include
# directories.
################################################################################
function(
    _get_targets_sources_headers_and_include_dirs
    _targets
    _sources
    _headers
    _include_dirs
)
    foreach(target ${_targets})
        # Get absolute path of the source files of the target
        get_target_property(target_sources ${target} SOURCES)
        foreach(source_file ${target_sources})
            if(NOT IS_ABSOLUTE ${source_file})
                get_target_property(tgt_source_dir ${target} SOURCE_DIR)
                set(source_file "${tgt_source_dir}/${source_file}")
            endif()
            if(EXISTS ${source_file})
                list(APPEND sources ${source_file})
            endif()
        endforeach()

        # Get the header files
        get_target_property(target_include_dirs ${target} INCLUDE_DIRECTORIES)
        foreach(include_dir ${target_include_dirs})
            if(EXISTS ${include_dir})
                file(
                    GLOB_RECURSE header_files
                    ${include_dir}/*.h
                    ${include_dir}/*.hpp
                    ${include_dir}/*.hxx
                    ${include_dir}/*.hh
                    ${include_dir}/*.h++
                )
                list(APPEND include_dirs ${include_dir})
                list(APPEND headers ${header_files})
            endif()
        endforeach()
    endforeach()

    set(${_include_dirs} ${include_dirs} PARENT_SCOPE)
    set(${_headers} ${headers} PARENT_SCOPE)
    set(${_sources} ${sources} PARENT_SCOPE)
endfunction()

################################################################################
# Creates a CMake build targets with the given names that performs C/C++
# clang-tidy checking/fixing on the targets that were slated for linting by
# previous calls to the add_clang_lint_target() function.
################################################################################
function(create_clang_tidy_lint_targets)
    set(options)
    set(oneValueArgs FIX_TARGET_NAME CHECK_TARGET_NAME CONFIG_FILE_PATH)
    set(multiValueArgs TARGETS)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    # Check for clang-tidy
    find_program(clang_tidy NAMES clang-tidy)
    if(NOT clang_tidy)
        message(FATAL_ERROR "clang-tidy must be installed to perform linting")
    endif()

    _get_targets_sources_headers_and_include_dirs("${ARG_TARGETS}" lint_sources lint_headers lint_include_dirs)

    if(NOT ARG_TARGETS)
        # Dummy target that does nothing
        add_custom_target(${ARG_CHECK_TARGET_NAME})
        add_custom_target(${ARG_FIX_TARGET_NAME})
    else()
        # Create a regex filter out of the include dirs so that only the headers
        # located in these directories will be checked by clang-tidy
        string(REPLACE ";" "/*|" header_filter ${lint_include_dirs})
        string(APPEND header_filter "/*")
        # Explicitly add CMake's implicit includes to the clang-tidy call
        set(extra_args_before)
        foreach(implicit_dir ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
            set(extra_args_before
                "${extra_args_before} --extra-arg-before=-I${implicit_dir}"
            )
        endforeach()

        if(DEFINED ARG_CONFIG_FILE_PATH)
            set(CONFIG_FILE_PATH ${ARG_CONFIG_FILE_PATH})
        else()
            set(CONFIG_FILE_PATH ${CMAKE_SOURCE_DIR}/.clang-tidy)
        endif()

        # TODO add configuration to strip undesired flags from
        # compile_commands.json

        set(call_clang_tidy_common
            "${clang_tidy} --config=${CONFIG_FILE_PATH} --format-style=file --header-filter=${header_filter} --extra-arg=-Wno-error=unknown-warning-option ${extra_args_before}"
        )

        set(call_clang_tidy_check
            "${call_clang_tidy_common} ${lint_sources} ${lint_headers}"
        )

        add_custom_target(
            ${ARG_CHECK_TARGET_NAME}
            COMMAND ${call_clang_tidy_check}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM
            COMMENT "Checking C/C++ code using clang-tidy"
        )

        set(call_clang_tidy_fix
            ${call_clang_tidy_common}
            --fix
            --fix-errors
            ${lint_sources}
            ${lint_headers}
        )

        add_custom_target(
            ${ARG_FIX_TARGET_NAME}
            COMMAND ${call_clang_tidy_fix}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM
            COMMENT "Fixing C/C++ code using clang-tidy"
        )
    endif()
endfunction()

################################################################################
# Creates a CMake build targets with the given names that performs C/C++
# clang-format checking/fixing on the targets that were slated for linting by
# previous calls to the add_clang_lint_target() function.
################################################################################
function(create_clang_format_lint_targets)
    set(options)
    set(oneValueArgs FIX_TARGET_NAME CHECK_TARGET_NAME CONFIG_FILE_PATH)
    set(multiValueArgs TARGETS)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    # Check for clang-format
    find_program(clang_format NAMES clang-format)
    if(NOT clang_format)
        message(WARNING "clang-format must be installed to perform linting")
        return()
    endif()

    if(DEFINED ARG_CONFIG_FILE_PATH)
        if(
            (NOT EXISTS ${ARG_CONFIG_FILE_PATH})
            OR (
                EXISTS ${ARG_CONFIG_FILE_PATH}
                AND IS_SYMLINK ${ARG_CONFIG_FILE_PATH}
            )
        )
            execute_process(
                COMMAND
                    "${CMAKE_COMMAND}" "-E" "create_symlink"
                    "${ARG_CONFIG_FILE_PATH}" ".clang-format"
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND_ECHO "STDOUT"
            )

            if(NOT IS_SYMLINK "${CMAKE_SOURCE_DIR}/.clang-format")
                message(
                    FATAL_ERROR
                    "Couldn't create symlink to .clang-format configuration file."
                    " Check that CONFIG_FILE_PATH: ${ARG_CONFIG_FILE_PATH} is a valid path to a .clang-format file"
                )
            endif()
        else()
            message(
                WARNING
                "Couldn't create symlink to .clang-format configuration file, a file already exits there"
            )
        endif()
    endif()

    _get_targets_sources_headers_and_include_dirs("${ARG_TARGETS}" lint_sources lint_headers lint_include_dirs)

    if(NOT ARG_TARGETS)
        # Dummy target that does nothing
        add_custom_target(${ARG_CHECK_TARGET_NAME})
        add_custom_target(${ARG_FIX_TARGET_NAME})
    else()
        set(call_clang_format_common ${clang_format} --Werror --style=file)

        set(call_clang_format_check
            ${call_clang_format_common}
            --dry-run
            --ferror-limit=100
            ${lint_sources}
            ${lint_headers}
        )

        add_custom_target(
            ${ARG_CHECK_TARGET_NAME}
            COMMAND ${call_clang_format_check}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM
            COMMENT "Checking C/C++ code using clang-format"
        )

        set(call_clang_format_fix
            ${call_clang_format_common}
            -i
            ${lint_sources}
            ${lint_headers}
        )

        add_custom_target(
            ${ARG_FIX_TARGET_NAME}
            COMMAND ${call_clang_format_fix}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM
            COMMENT "Fixing C/C++ code using clang-format"
        )
    endif()
endfunction()
