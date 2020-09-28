// Find the parity of a word. If a word has an odd number of bits set to 1 the
// parity is 1 and if there are an even number of bits the parity is 0.
#include <cstdint>
#include <gtest/gtest.h>

uint8_t parity(uint64_t word)
{
    uint8_t result = 0;
    while (word != 0)
    {
        result ^= (word & 1);
        word >>= 1;
    }
    return result;
}

TEST(parity, with_odd_bits_return_0)
{
    // 0b0101010
    ASSERT_EQ(parity(0xAA), 0);
}

TEST(parity, with_even_bits_return_1)
{
    // 0b0101000
    ASSERT_EQ(parity(0xA8), 1);
}
