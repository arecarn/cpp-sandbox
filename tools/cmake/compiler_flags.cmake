if(NOT CMAKE_PROJECT_NAME)
    message(
        FATAL_ERROR
        "This file should be included immediately following the project command."
    )
elseif(NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    return()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)

if(WARNINGS_AS_ERRORS)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Werror)
    string(JOIN " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Werror)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    string(JOIN " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    string(
        JOIN
        " "
        CMAKE_CXX_FLAGS
        ${CMAKE_CXX_FLAGS}
        -Wall
        -Wcast-align # warn for potential performance problem casts
        -Wcast-function-type
        -Wcast-qual
        -Wconversion # warn on type conversions that may lose data
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wextra # reasonable and standard
        -Wfloat-conversion
        -Wfloat-equal
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough
        -Winit-self
        -Wint-to-pointer-cast
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
        -Wmaybe-uninitialized
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
        -Wmissing-declarations
        -Wmultiple-inheritance
        -Wmultistatement-macros
        -Wnarrowing
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
        -Wnull-dereference # warn if a null dereference is detected
        -Wold-style-cast # warn for c-style casts
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        -Wparentheses
        -Wpedantic # warn if non-standard C++ is used
        -Wregister
        -Wreturn-local-addr
        -Wshadow # warn the user if a variable declaration shadows one from a parent context
        -Wsign-conversion # warn on sign conversions
        -Wsuggest-override
        -Wswitch-default
        -Wtrigraphs
        -Wuninitialized
        -Wunused # warn on anything being unused
        -Wuseless-cast # warn if you perform a cast to the same type
        -Wzero-as-null-pointer-constant
    )
endif()
