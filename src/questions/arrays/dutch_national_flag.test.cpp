#include <array>
#include <gtest/gtest.h>
#include <iostream>

template <typename T>
void dutch_national_flag(std::vector<T>& arr, size_t pivot_index)
{
    const auto pivot = arr[pivot_index];
    auto b = arr.begin();
    auto e = arr.end() - 1;

    auto f = [](auto b, auto e, T pivot) -> auto
    {
        while (b < e)
        {
            if (*b > pivot)
            {

                if (*e <= pivot)
                {
                    std::swap(*b, *e);
                }
                e--;
            }
            else
            {
                b++;
            }
        }

        if (*b == pivot)
        {
            return b;
        }
        return e;
    };
    auto p = f(b, e, pivot);
    f(b, p, pivot - 1);
}

TEST(dutch_national_flag, one)
{
    constexpr size_t Pivot {1};
    std::vector<int> input {0, 1, 2, 0, 2, 1, 1};
    dutch_national_flag(input, Pivot);
    const std::vector<int> expected {0, 0, 1, 1, 1, 2, 2};
    ASSERT_EQ(input, expected);
}

TEST(dutch_national_flag, two)
{
    constexpr size_t Pivot {2};
    std::vector<int> input {0, 1, 2, 0, 2, 1, 1};
    dutch_national_flag(input, Pivot);
    const std::vector<int> expected {0, 1, 1, 0, 1, 2, 2};
    ASSERT_EQ(input, expected);
}

TEST(dutch_national_flag, zero)
{
    constexpr size_t Pivot {0};
    std::vector<int> input {0, 1, 2, 0, 2, 1, 1};
    dutch_national_flag(input, Pivot);
    const std::vector<int> expected {0, 0, 2, 1, 2, 1, 1};
    ASSERT_EQ(input, expected);
}
