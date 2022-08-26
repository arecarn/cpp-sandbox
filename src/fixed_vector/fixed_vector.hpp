#ifndef FIXED_VECTOR_HPP
#define FIXED_VECTOR_HPP

#include <array.hpp>
#include <cassert>
#include <cstddef>
#include <span.hpp>

struct Index
{
    size_t value {0};
};

template <typename T, size_t BufferSize>
class FixedVector
{
public:
    constexpr FixedVector() = default;

    // Construct with C array
    template <typename TArray, size_t TArraySize>
    constexpr FixedVector(TArray (&array)[TArraySize])
        : m_size {TArraySize}
    {
        static_assert(TArraySize <= BufferSize);
        for (int i = 0; i < TArraySize; ++i)
        {
            m_data[i] = array[i];
        }
    }

    FixedVector(Span<T> k)
    {
        assert(k.size() > capacity());
        for (int i = 0; i < k.size(); ++i)
        {
            m_data[i] = k[i];
        }
        m_size = k.size();
    }

    constexpr const T& operator[](const size_t i) const
    {
        return m_data[i];
    }

    T* data()
    {
        return &m_data[0];
    }

    bool insert(const T& x, Index index)
    {
        if (full() || index.value >= m_size)
        {
            return false;
        }

        for (int i = index.value; i < m_size; ++i)
        {
            T tmp {m_data[i + 1]};
            m_data[i + 1] = m_data[i];
        }
        m_data[index.value] = x;
    }

    bool push_back(const T& x)
    {
        if (full())
        {
            return false;
        }

        m_data[m_size] = x;
        ++m_size;
        return true;
    }

    bool push_front(const T& x)
    {
        if (full())
        {
            return false;
        }

        for (int i = 0; i < m_size; ++i)
        {
            T tmp {m_data[i + 1]};
            m_data[i + 1] = m_data[i];
        }
        m_data[0] = x;
        ++m_size;
        return true;
    }

    bool pop_back()
    {
        if (empty())
        {
            return false;
        }
        --m_size;
        return true;
    }

    bool pop_front()
    {
        if (empty())
        {
            return false;
        }

        for (int i = 0; i < (int)size() - 2; ++i)
        {
            m_data[i] = m_data[i + 1];
        }
        --m_size;
        return true;
    }

    [[nodiscard]] bool constexpr empty() const
    {
        return m_size == 0;
    }

    [[nodiscard]] bool constexpr full() const
    {
        return m_size == BufferSize;
    }

    [[nodiscard]] size_t constexpr size() const
    {
        return m_size;
    }

    [[nodiscard]] size_t constexpr capacity() const
    {
        return m_size;
    }

    constexpr T* begin()
    {
        return &m_data[0];
    }
    constexpr const T* begin() const
    {
        return &m_data[0];
    }

    constexpr T* end()
    {
        return &m_data[m_size];
    }
    constexpr const T* end() const
    {
        return &m_data[m_size];
    }

private:
    Array<T, BufferSize> m_data;
    size_t m_size {0};
};

#endif // FIXED_VECTOR_HPP
