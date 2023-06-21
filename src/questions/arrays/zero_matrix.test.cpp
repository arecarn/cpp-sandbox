// Zero Matrix: Write an algorithm such that if an element in an MxN matrix is
// 0, its entire row and column are set to 0.

#include <cstring>
#include <gtest/gtest.h>
#include <iostream>
#include <unordered_set>

template <size_t N>
void zero_matrix(std::uint32_t (&matrix)[N][N])
{
    std::unordered_set<size_t> zero_rows;
    std::unordered_set<size_t> zero_cols;

    for (size_t row = 0; row < N; ++row)
    {
        for (size_t col = 0; col < N; ++col)
        {
            if (matrix[row][col] == 0)
            {
                zero_cols.insert(col);
                zero_rows.insert(row);
            }
        }
    }

    for (size_t row = 0; row < N; ++row)
    {
        for (size_t col = 0; col < N; ++col)
        {
            if (zero_cols.find(col) != zero_cols.end()
                || zero_rows.find(row) != zero_rows.end())
            {
                matrix[row][col] = 0;
            }
        }
    }

    auto x = [](auto s) {
        for (auto i : s)
        {
            std::cerr << i << ", ";
        }
        std::cerr << "\n";
    };
    x(zero_cols);
    x(zero_rows);
}

// clang-format off
uint32_t g_case_a[2][2] = {
    {0, 2},
    {3, 4},
};

uint32_t g_case_a_expected[2][2] = {
    {0, 0},
    {0, 4},
};

uint32_t g_case_b[3][3] = {
    {1, 2, 3},
    {4, 0, 6},
    {7, 8, 9},
};

uint32_t g_case_b_expected[3][3] = {
    {1, 0, 3},
    {0, 0, 0},
    {7, 0, 9},
};

uint32_t g_case_c[4][4] = {
    {0,   2,   3,   4},
    {5,   6,   7,   8},
    {9,   10,  11,  0},
    {13,  14,  15,  16},
};

uint32_t g_case_c_expected[4][4] = {
    {0,  0,   0,   0},
    {0,  6,   7,   0},
    {0,  0,   0,   0},
    {0,  14,  15,  0},
};
// clang-format off

template <size_t N>
void print_matrix(const std::uint32_t (&matrix)[N][N])
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
    print_matrix(expected);
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
