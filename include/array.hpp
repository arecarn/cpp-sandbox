#include <cstddef>

template <typename T, size_t n>
struct array {
    using value_type = T;

    value_type data[n];

    constexpr T& operator[](const size_t i) {
        return data[i];
    }
    constexpr const T& operator[](const size_t i) const {
        return data[i]; // NOLINT
    }

    size_t constexpr size() {
        return n;
    }

    constexpr T* begin() {
        return &data[0];
    }
    constexpr const T* begin() const {
        return &data[0];
    }

    constexpr T* end() {
        return &data[n];
    }
    constexpr const T* end() const {
        return &data[n];
    }
};



template <size_t I, typename T, size_t N>
constexpr T& get(array<T, N>& a)
{
    static_assert(I < N, "I must be less than N");
    return a[I];
}

template <size_t I, typename T, size_t N>
constexpr const T& get(const array<T, N>& a)
{
    static_assert(I < N, "I must be less than N");
    return a[I];
}
