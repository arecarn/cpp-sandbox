#include "pod_variant.hpp"

#include <gtest/gtest.h>

static int g_jjjj;

struct Dub {
    double x;
    double y;
    double z;
};

constexpr int Data_Size = 128;
struct alignas(Data_Size) Test {
    char data[Data_Size];
};


constexpr int X_Size = 5;
char g_x[X_Size];

TEST(test, test) // NOLINT
{
    static int bbbb;
    PodVariant<char, Dub> u{'a'};
    ASSERT_EQ(u.as<char>(), 'a');
    std::cout << "<<<<" << alignof(u) << ">>>>" << "\n";
    std::cout << "<<<<" << alignof('a') << ">>>>" << "\n";
    std::cout << "<<<<" << alignof(long double) << ">>>>" << "\n";
    std::cout << "<<<<" << alignof(Test) << ">>>>" << "\n";
    ASSERT_TRUE(false);
};
