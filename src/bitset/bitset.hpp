#ifndef BITSET_HPP
#define BITSET_HPP

#include <cstddef>
#include <cstdint>

static constexpr uint32_t bytes_to_represents_bits(uint32_t number_of_bits)
{
    uint32_t add {0};
    if (number_of_bits % 8 != 0)
    {
        add = 8;
    }
    return (number_of_bits + add) / 8;
}

class BitReference
{
public:
    BitReference(uint8_t& integer, uint8_t bit_pos)
        : m_integer {integer}
        , m_bit_pos {bit_pos}
    {
    }

    bool operator=(bool value) // NOLINT(misc-unconventional-assign-operator)
    {
        // assert(bit < Number Orbits)
        const uint8_t b = value ? 1 : 0;
        m_integer = static_cast<uint8_t>((m_integer & ~(1 << m_bit_pos)) | (b << m_bit_pos));
        return value;
    }

    operator bool() const
    {
        const auto mask = static_cast<uint8_t>(1 << m_bit_pos);
        return (m_integer & mask) != 0;
    }

private:
    uint8_t& m_integer;
    uint8_t m_bit_pos;
};

template <size_t NumberOfBits>
class Bitset
{
public:
    BitReference operator[](const size_t bit)
    {
        const size_t i {bit / 8};
        const uint8_t bit_pos {static_cast<uint8_t>(bit % 8)};

        return BitReference(m_data[i], bit_pos);
    }

    bool operator[](const size_t bit) const
    {
        const uint32_t bit_pos = (bit % 8);
        const auto mask = static_cast<uint8_t>(1 << bit_pos);
        return m_data[bit / 8] & mask;
    }

    void set(size_t bit, bool value)
    {
        // assert(bit < Number Orbits)
        const uint8_t b = value ? 1 : 0;
        const uint32_t i = bit / 8;
        const uint32_t bit_pos = (bit % 8);
        m_data[i] = (m_data[i] & ~(1 << bit_pos)) | (b << bit_pos);
    }

    [[nodiscard]] bool get(size_t bit) const
    {
        // assert(bit < Number Orbits)
        const uint32_t bit_pos = (bit % 8);
        const auto mask = static_cast<uint8_t>(1 << bit_pos);
        return m_data[bit / 8] & mask;
    }

    uint8_t* data()
    {
        return m_data;
    }

    static_assert(NumberOfBits != 0, "Bitset can't represent 0 bits");

private:
    static constexpr uint32_t NumBytes {bytes_to_represents_bits(NumberOfBits)};
    uint8_t m_data[NumBytes] {};
};

#endif // BITSET_HP
