option(CLANG_TIDY_FIX "Perform fixes for Clang-Tidy" OFF)

find_program(CLANG_TIDY NAMES clang-tidy DOC "Path to clang-tidy executable")

if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY};--extra-arg=-Wno-error=unknown-warning-option"
    )
    if(CLANG_TIDY_FIX)
        list(APPEND CMAKE_CXX_CLANG_TIDY "-fix")
    endif()
else()
    message(WARNING "clang-tidy Not Found!")
endif()
