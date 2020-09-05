#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

template <typename T, size_t N>
class Array
{
public:
    // TODO(rcarney) need to add extra type parameters
    using value_type = T;

    constexpr T& operator[](const size_t i)
    {
        return m_data[i];
    }
    constexpr const T& operator[](const size_t i) const
    {
        return m_data[i];
    }

    T* data()
    {
        return &m_data[0];
    }

    static size_t constexpr size()
    {
        return N;
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
        return &m_data[N];
    }
    constexpr const T* end() const
    {
        return &m_data[N];
    }

    T m_data[N];
};

template <size_t I, typename T, size_t N>
constexpr T& get(Array<T, N>& a)
{
    static_assert(I < N, "I must be less than N");
    return a[I];
}

template <size_t I, typename T, size_t N>
constexpr const T& get(const Array<T, N>& a)
{
    static_assert(I < N, "I must be less than N");
    return a[I];
}

#endif // ARRAY_HPP
