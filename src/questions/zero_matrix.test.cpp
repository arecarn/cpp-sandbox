// Zero Matrix: Write an algorithm such that if an element in an MxN matrix is 0, its entire row and
// column are set to 0.

#include <cstring>
#include <gtest/gtest.h>
#include <iostream>

template <size_t N>
void zero_matrix(std::uint32_t (&matrix)[N][N])
{
    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < N; ++col)
        {
            if (matrix[row][col] == 0)
            {
                continue;
            }
            // check left
            const bool zero_left = col > 0 && matrix[row][col - 1] == 0;
            // check above
            const bool zero_above = row > 0 && matrix[row - 1][col] == 0;
            // check right
            const bool zero_right = col < N - 1 && matrix[row][col + 1] == 0;
            // check below
            const bool zero_below = row < N - 1 && matrix[row + 1][col] == 0;

            if (zero_left || zero_above || zero_right || zero_below)
            {
                matrix[row][col] = 0;
            }
        }
    }
}

// clang-format off
uint32_t g_case_a[2][2] = {
    {0, 2},
    {3, 4},
};

uint32_t g_case_a_expected[2][2] = {
    {0, 0},
    {0, 0},
};

uint32_t g_case_b[3][3] = {
    {1, 2, 3},
    {4, 0, 6},
    {7, 8, 9},
};

uint32_t g_case_b_expected[3][3] = {
    {7, 0, 1},
    {0, 0, 0},
    {9, 0, 3},
};

uint32_t g_case_c[4][4] = {
    {0,   2,   3,   4},
    {5,   6,   7,   8},
    {9,   10,  11,  0},
    {13,  14,  15,  16},
};

uint32_t g_case_c_expected[4][4] = {
    {0,  0,   0,  0},
    {0,  10,  6,  0},
    {0,  0,   0,  0},
    {0,  12,  8,  0},
};
// clang-format off

template <size_t N>
void print_matrix(std::uint32_t (&matrix)[N][N])
{
    std::cerr << __func__ << std::endl;
    for (size_t i = 0; i < N; ++i)
    {
        std::cerr << i << ": ";
        for (size_t j{0}; j < N; ++j)
        {
            std::cerr << matrix[i][j] << '\t';
        }
        std::cerr << "\n";
    }
}

template <size_t N>
void test_matrix(std::uint32_t (&matrix)[N][N], const std::uint32_t (&expected)[N][N])
{
    zero_matrix(matrix);
    std::cerr << "Expected:\n";
    print_matrix(matrix);
    std::cerr << "Got:\n";
    print_matrix(matrix);
    ASSERT_TRUE(
        0 == std::memcmp(
            matrix,
            expected,
            sizeof(matrix)
        )
    );
}

TEST(zero_matrix, test_2x2)
{
    test_matrix(g_case_a, g_case_a_expected);
}

TEST(zero_matrix, test_3x3)
{
    test_matrix(g_case_b, g_case_b_expected);
}

TEST(zero_matrix, test_4x4)
{
    test_matrix(g_case_c, g_case_c_expected);
}
