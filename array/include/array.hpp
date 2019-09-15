#include <cstddef>

template <typename T, size_t n>
struct array {
    using value_type = T;

    value_type data[n];

    void operator[](size_t i)
    {
        return data[i];
    }

    T* begin()
    {
        return &data[0];
    }

    T* end()
    {
        return &data[n];
    }
};
