################################################################################
# Interface Library
################################################################################
add_library(TimeIntf INTERFACE)
target_include_directories(TimeIntf INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Library
################################################################################
add_library(Time STATIC Time.cpp)
target_include_directories(Time PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Time TimeIntf)

################################################################################
# Mock Library
################################################################################
add_library(TimeMock INTERFACE)
target_link_libraries(TimeMock INTERFACE gtest gmock)
target_include_directories(TimeMock INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
