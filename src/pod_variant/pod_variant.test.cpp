#include "pod_variant.hpp"

#include <gtest/gtest.h>

struct Dub
{
    double x;
    double y;
    double z;
};

constexpr int Data_Size = 128;
struct alignas(Data_Size) Test
{
    char data[Data_Size];
};

constexpr int X_Size = 5;
char g_x[X_Size];

TEST(test, test) // NOLINT
{
    PodVariant<char, Dub> u {'a'};
    ASSERT_EQ(u.as<char>(), 'a');
    std::cout << "<<<<" << alignof(PodVariant<char, Dub>) << ">>>>"
              << "\n";
    std::cout << "<<<<" << alignof(char) << ">>>>"
              << "\n";
    std::cout << "<<<<" << alignof(long double) << ">>>>"
              << "\n";
    std::cout << "<<<<" << alignof(Test) << ">>>>"
              << "\n";
}
