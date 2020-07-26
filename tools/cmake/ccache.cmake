find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    # use ccache if it's available
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()
