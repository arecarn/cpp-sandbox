#include <cstddef>

template <typename T>
class span {
    public:

    using value_type = T;

    // Construct with C array
    template <typename ArrayT, size_t t_size>
    constexpr explicit span(ArrayT(&array)[t_size])
    : m_begin {array}, // NOLINT(cppcoreguidelines-pro-bounds-pointer-decay, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
        m_end {array + t_size} // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic, cppcoreguidelines-pro-bounds-pointer-decay, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    {}

    // Construct with array<T,size> or types with a .data() and .size() members
    template <typename TArray>
    constexpr explicit span(TArray& array)
    : m_begin {array.data()},
        m_end {array.data() + array.size()} // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    {}

    constexpr T& operator[](const size_t i) {
        return m_begin[i]; // NOLINT(
    }
    constexpr const T& operator[](const size_t i) const {
        return m_begin[i]; // NOLINT
    }

    size_t constexpr size() {
        return m_end - m_begin; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }

    constexpr T* begin() {
        return m_begin;
    }
    constexpr const T* begin() const {
        return m_begin;
    }

    constexpr T* end() {
        return m_end;
    }
    constexpr const T* end() const {
        return m_end;
    }

    private:
    T* m_begin;
    T* m_end;
};
