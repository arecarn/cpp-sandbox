// Write a program that takes an vector v and an index i into v, and rearranges
// the elements such that all elements less than v[i] (the “pivot”) appear first,
// followed by elements equal to the pivot, followed by elements greater than
// the pivot.

#include <array>
#include <gtest/gtest.h>
#include <iostream>

// Hold the following invariant:
// v[0 : less_end] < pivot
// v[less_end + 1 : unknown_begin - 1] == pivot
// v[unknown_begin : greater_begin - 1] == ?
// v[greater_begin : v.size()] > pivot
template <typename T>
void dutch_national_flag(std::vector<T>& v, size_t pivot_index)
{
    auto pivot = v[pivot_index];
    size_t less_end = 0;
    size_t unknown_begin = 0;
    size_t greater_begin = v.size();

    while (unknown_begin < greater_begin)
    {
        if (v[unknown_begin] < pivot)
        {
            std::swap(v[unknown_begin], v[less_end]);
            ++less_end;
            ++unknown_begin;
        }
        else if (v[unknown_begin] > pivot)
        {
            --greater_begin;
            std::swap(v[unknown_begin], v[greater_begin]);
        }
        else // v[unknown_begin] == pivot
        {
            ++unknown_begin;
        }
    }
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
    const std::vector<int> expected {0, 1, 0, 1, 1, 2, 2};
    ASSERT_EQ(input, expected);
}

TEST(dutch_national_flag, zero)
{
    constexpr size_t Pivot {0};
    std::vector<int> input {0, 1, 2, 0, 2, 1, 1};
    dutch_national_flag(input, Pivot);
    const std::vector<int> expected {0, 0, 2, 2, 1, 1, 1};
    ASSERT_EQ(input, expected);
}
