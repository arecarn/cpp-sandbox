#include <bitset.hpp>

#include <gtest/gtest.h>

enum Bits
{
    Bit0,
    Bit1,
    Bit2,
    Bit3,
    Bit4,
    Bit5,
    Bit6,
    Bit7,
    Bit8,
    Bit9,
    BitCount,
};

TEST(array, static)
{
    Bitset<BitCount> bs;
    ASSERT_EQ((bool)bs[Bit9], false);

    bs[Bit9] = true;
    ASSERT_EQ((bool)bs[Bit9], true);

    bs[Bit9] = false;
    ASSERT_EQ((bool)bs[Bit9], false);
}
