################################################################################
# Interface Library
################################################################################
add_library(StorageIntf INTERFACE)
target_include_directories(StorageIntf INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(StorageIntf INTERFACE TodoList)

################################################################################
# Library
################################################################################
# add_library(Storage STATIC Storage.cpp)
# target_include_directories(Storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(Storage PUBLIC StorageIntf)

################################################################################
# Mock Library
################################################################################
add_library(StorageMock INTERFACE)
target_link_libraries(StorageMock INTERFACE StorageInf gtest gmock)
target_include_directories(StorageMock INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
