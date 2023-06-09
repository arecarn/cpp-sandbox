################################################################################
# Interface Library
################################################################################
add_library(PersistenceIntf INTERFACE)
target_include_directories(PersistenceIntf INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(PersistenceIntf INTERFACE TodoList)

################################################################################
# Library
################################################################################
# add_library(Persistence STATIC Persistence.cpp)
# target_include_directories(Persistence PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(Persistence PUBLIC PersistenceIntf)

################################################################################
# Mock Library
################################################################################
add_library(PersistenceMock INTERFACE)
target_link_libraries(PersistenceMock INTERFACE PersistenceInf gtest gmock)
target_include_directories(PersistenceMock INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
