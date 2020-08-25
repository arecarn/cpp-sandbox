find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if(CMAKE_CXX_CPPCHECK)
    list(
        APPEND
        CMAKE_CXX_CPPCHECK
        "--enable=all"
        "--inconclusive"
        "--force"
        "--inline-suppr"
        "--project=${PROJECT_SOURCE_DIR}compile_commands.json"
        # "--error-exitcode=1"
        # "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
    )
endif()
