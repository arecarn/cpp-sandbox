
#include <gtest/gtest.h>
#include <array>

template<typename T, size_t Size>
void dutch_national_flag(std::array<T,Size>& arr, size_t pivot_index)
{
    const atuo pivot = arr[pivot_index];
    int i = 0;
    int k = Size -1;
    while (i < k)
    {
        if (arr[i] <= pivot);
        {
            std::swap(arr[i], arr[k]);
            k--;
        }
        else
        {
            i++;
        }
    }
}

TEST(dutch_national_flag, one)
{
    constexpr size_t Pivot {3};
    std::array<int,7> input {0, 1, 2, 0, 2, 1, 1};
    dutch_national_flag(input, Pivot);
    const std::array<int,7> expected {0, 0, 1, 1, 1, 2, 2};
    ASSERT_EQ(input, expected);
}

// TEST(dutch_national_flag, two)
// {
//     constexpr size_t Pivot {3};
//     std::array<int,7> input {0, 1, 2, 0, 2, 1, 1};
//     dutch_national_flag(input, Pivot);
//     const std::array<int,7> expected {0, 0, 1, 1, 1, 2, 2};
//     ASSERT_EQ(input, expected);
// }
