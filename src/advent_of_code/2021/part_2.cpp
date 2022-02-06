#include <gtest/gtest.h>
#include <vector>

int solution(std::vector<int>& input)
{
    for (int i = 2; i < input.size(); ++i)
    {
        input[i - 2] = input[i] + input[i - 1] + input[i - 2]
    }
}

TEST(test, test)
{
}
