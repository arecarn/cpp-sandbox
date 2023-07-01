find_program(
    GERSEMI
    NAMES gersemi
    DOC "Path to gersemi CMake formatting executable"
)

function(gersemi_add_format_cmake_targets)
    set(options)
    set(oneValueArgs FIX_TARGET_NAME CHECK_TARGET_NAME)
    set(multiValueArgs FILES)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )
    if(GERSEMI)
        add_custom_target(
            ${ARG_FIX_TARGET_NAME}
            COMMAND ${GERSEMI} -i ${ARGS_FILES}
            COMMENT "Formatting CMake source files"
        )

        add_custom_target(
            ${ARG_CHECK_TARGET_NAME}
            COMMAND ${GERSEMI} -c ${ARGS_FILES}
            COMMENT "Checking formatting of CMake source files"
        )
    else()
        message(WARNING "gersemi Not Found! CMake Format Targets Not Created.")
    endif()
endfunction()
