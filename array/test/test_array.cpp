#include <array.hpp>

#include <gtest/gtest.h>
#include <iostream>

TEST(ArrayTest, Static)
{
    array<int, 3> pizza;


    for (auto i : pizza)
    {
        std::cout << "hello world\n";
    }
}
