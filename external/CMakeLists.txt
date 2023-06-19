include(FetchContent)

set(dependencies googletest)

foreach(dependency ${dependencies})
    FetchContent_Declare(${dependency}
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${dependency}
    )
endforeach()

FetchContent_MakeAvailable(${dependencies})
