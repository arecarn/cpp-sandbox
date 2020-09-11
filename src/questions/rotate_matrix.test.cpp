// Rotate Matrix: Given an image represented by an NxN matrix, where each pixel in
// the image is 4 bytes, write a method to rotate the image by 90 degrees. Can you
// do this in place?

#include <cstdint>
#include <cstring>
#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>

template <size_t N>
void rotate_matrix(std::uint32_t (&matrix)[N][N])
{
    const int max_layers = N / 2;
    for (int layer = 0; layer < max_layers; layer++)
    {
        for (int c = 0; c < (N - 1) - (2 * layer); c++)
        {
            const int top_row = layer;
            const int top_col = layer + c;
            const int right_row = layer + c;
            const int right_col = N - 1 - layer;
            const int bottom_row = N - 1 - layer;
            const int bottom_col = N - 1 - layer - c;
            const int left_row = N - 1 - layer - c;
            const int left_col = layer;

            // save right
            std::uint32_t right = matrix[right_row][right_col];
            // top to right
            matrix[right_row][right_col] = matrix[top_row][top_col];

            // save bottom
            std::uint32_t bottom = matrix[bottom_row][bottom_col];
            // right to bottom
            matrix[bottom_row][bottom_col] = right;

            // save left
            std::uint32_t left = matrix[left_row][left_col];
            // bottom to left
            matrix[left_row][left_col] = bottom;

            // left to top
            matrix[top_row][top_col] = left;
        }
    }
}

// clang-format off
uint32_t g_case_a[2][2] = {
    {1, 2},
    {3, 4},
};

uint32_t g_case_a_expected[2][2] = {
    {3, 1},
    {4, 2},
};

uint32_t g_case_b[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
};

uint32_t g_case_b_expected[3][3] = {
    {7, 4, 1},
    {8, 5, 2},
    {9, 6, 3},
};

uint32_t g_case_c[4][4] = {
    {1,   2,   3,   4},
    {5,   6,   7,   8},
    {9,   10,  11,  12},
    {13,  14,  15,  16},
};

uint32_t g_case_c_expected[4][4] = {
    {13,  9,   5,  1},
    {14,  10,  6,  2},
    {15,  11,  7,  3},
    {16,  12,  8,  4},
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
    rotate_matrix(matrix);
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

TEST(rotate_matrix, test_2x2)
{
    test_matrix(g_case_a, g_case_a_expected);
}

TEST(rotate_matrix, test_3x3)
{
    test_matrix(g_case_b, g_case_b_expected);
}

TEST(rotate_matrix, test_4x4)
{
    test_matrix(g_case_c, g_case_c_expected);
}
