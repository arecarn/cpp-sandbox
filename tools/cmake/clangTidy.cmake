if(CMAKE_VERSION VERSION_GREATER 3.6)
    # Add clang-tidy if available
    option(CLANG_TIDY_FIX "Perform fixes for Clang-Tidy" OFF)
    find_program(
        CLANG_TIDY_EXE
        NAMES "clang-tidy"
        DOC "Path to clang-tidy executable"
        )

    if(CLANG_TIDY_EXE)

        set(CMAKE_CXX_CLANG_TIDY
            "${CLANG_TIDY_EXE}"
            "-header-filter=.*"
            "-checks=*,\
            -fuchsia*,\
            -llvm-header-guard,\
            "
            )
        if(CLANG_TIDY_FIX)
            list(APPEND CMAKE_CXX_CLANG_TIDY "-fix")
        endif()
    endif()
endif()
