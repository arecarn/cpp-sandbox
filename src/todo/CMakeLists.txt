include(FetchContent)
FetchContent_Declare(uuid_v4
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/uuid_v4
)
set(dependencies "")
list(APPEND dependencies uuid_v4)

FetchContent_MakeAvailable(${dependencies})

add_subdirectory(TodoApp)
add_subdirectory(Persistence)
add_subdirectory(Time)
add_subdirectory(Todo)
add_subdirectory(TodoList)
