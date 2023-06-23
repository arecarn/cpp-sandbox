find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    # use ccache if it's available
    message(
        STATUS
        "ccache was found at ${CCACHE_PROGRAM} and will be used to cache compilation output"
    )
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
else()
    message(
        WARNING
        "ccache was NOT found and will NOT be used to cache compilation output"
    )
endif()
