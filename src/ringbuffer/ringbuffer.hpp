#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <cstddef>
#include <cstdint>

template <typename T, size_t N>
class ringbuffer
{
public:
    using value_type = T;

    ringbuffer() = default;
    ~ringbuffer() = default;

    bool push_back(const T x)
    {
        if (m_size == N)
        {
            return false;
        }

        if (m_front == -1) // queue is empty
        {
            m_front = 0;
            m_back = 0;
        }
        else if (static_cast<size_t>(m_back) == Max_Index) // m_back at last position
        {
            m_back = 0;
        }
        else
        {
            ++m_back;
        }

        m_data[m_back] = x;
        ++m_size;
        return true;
    }

    bool push_front(const T x)
    {
        if (m_size == N)
        {
            return false;
        }

        if (m_front == -1) // If queue is initially empty
        {
            m_front = 0;
            m_back = 0;
        }
        else if (m_front == 0) // m_front at first position
        {
            m_front = Max_Index;
        }
        else
        {
            --m_front;
        }

        ++m_size;
        m_data[m_front] = x;
        return true;
    }

    bool pop_front()
    {
        if (m_size == 0)
        {
            return false;
        }

        if (m_front == m_back) // has only one element
        {
            m_front = -1;
            m_back = -1;
        }
        else if (static_cast<size_t>(m_front) == Max_Index) // back to initial position
        {
            m_front = 0;
        }
        else
        {
            ++m_front;
        }
        --m_size;
        return true;
    }

    bool pop_back()
    {
        if (m_size == 0)
        {
            return false;
        }

        if (m_front == m_back) // only one element
        {
            m_front = -1;
            m_back = -1;
        }
        else if (m_back == 0)
        {
            m_back = Max_Index;
        }
        else
        {
            --m_back;
        }
        --m_size;
        return true;
    }

    T& operator[](const size_t i)
    {
        size_t j = (static_cast<size_t>(m_front) + i) % N;
        return m_data[j];
    }

    [[nodiscard]] size_t size() const
    {
        return m_size;
    }

    [[nodiscard]] bool empty() const
    {
        return m_size == 0;
    }

    static constexpr size_t capacity()
    {
        return Capacity;
    }

private:
    static constexpr size_t Capacity {N};
    static constexpr size_t Max_Index {N - 1};
    value_type m_data[N] {};
    int32_t m_back {0};
    int32_t m_front {-1};
    size_t m_size {0};
};

#endif // RINGBUFFER_HPP
