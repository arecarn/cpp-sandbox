#include <gtest/gtest.h>
#include <pong.hpp>

TEST(PongTest, Static)
{
    EXPECT_EQ(std::string("Hello World!"), Pong::greet("World"));
}
