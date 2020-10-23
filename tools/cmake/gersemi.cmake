find_program(
    GERSEMI
    NAMES gersemi
    DOC "Path to gersemi CMake formatting executable"
)

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
    else()
        message(WARNING "gersemi Not Found! CMake Format Targets Not Created.")
    endif()
endfunction()
