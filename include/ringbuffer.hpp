#include <cstddef>

template <typename T, size_t N>
class ringbuffer {
public:
    using value_type = T;

    bool push(const T x) {
        if (m_size == N) {
            return false;
        }
        m_data[m_write_index] = x; // NOLINT do not use array subscript
        ++m_write_index;
        if (m_write_index == N) {
            m_write_index = 0;
        }
        ++m_size;
        return true;
    }

    bool pop() {
        if (m_size == 0) {
            return false;
        }
        ++m_read_index;
        if (m_read_index == N) {
            m_read_index = 0;
        }
        --m_size;
        return true;
    }

    T& operator[](const size_t i)
    {
        size_t j  = (m_read_index + i) % N;
        return m_data[j]; // NOLINT do not use array subscript
    }

    size_t size() {
        return  m_size;
    }

    bool empty() {
        return m_size == 0;
    }

    constexpr size_t capacity() {
        return N;
    }


    class iterator
    {
    public:
        iterator(const ringbuffer<T, N> *ringbuffer, int index);
        const T& operator*() const;
        iterator& operator++();
        bool operator!=(const iterator& other) const;

    private:
        const ringbuffer<T, N> *m_ringbuffer;
        int m_index = -1;
    };

    constexpr ringbuffer<T, N>::iterator begin() {
        return iterator(this, 0);
    }

    constexpr ringbuffer<T, N>::iterator end() {
        return iterator(this, m_write_index);
    }

private:
    value_type m_data[N] {};
    static constexpr size_t m_max_index {N - 1};
    size_t m_write_index {0};
    size_t m_read_index {0};
    size_t m_size {0};

};


template <typename T, size_t N>
ringbuffer<T, N>::iterator::iterator(const ringbuffer<T, N>* ringbuffer, int index)
    : m_ringbuffer(ringbuffer), m_index(index)
{
}

template <typename T, size_t N>
const T& ringbuffer<T, N>::iterator::operator*()
{
    return m_ringbuffer->operator[](m_index);
}

template <typename T, size_t N>
typename ringbuffer<T, N>::iterator &ringbuffer<T, N>::iterator::operator++()
{
    ++m_index;
    return *this;
}

template <typename T, size_t N>
bool ringbuffer<T, N>::iterator::operator!=(const ringbuffer<T, N>::iterator &other) const
{
    return m_index != other.m_index;
}
