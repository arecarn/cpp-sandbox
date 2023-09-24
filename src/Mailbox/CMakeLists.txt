################################################################################
# Library
################################################################################
add_library(Mailbox INTERFACE)
target_include_directories(Mailbox INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

################################################################################
# Test
#################################################################################
add_executable(MailboxTest ${CMAKE_CURRENT_SOURCE_DIR}/MailboxTest.cpp)
target_link_libraries(MailboxTest Mailbox gtest_main gmock)
create_test(MailboxTest)
