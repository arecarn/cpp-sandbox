#ifndef POD_VARIANT_HPP
#define POD_VARIANT_HPP

#include <algorithm>
#include <cstdint>
#include <stdexcept>

// get_type<i, Ts...>::type -> Ts[i] (Compile error of i >= length(Ts))
template <std::size_t i, typename T, typename... Ts>
struct get_type
{
    typedef typename get_type<i - 1, Ts...>::type type;
};

template <typename T, typename... Ts>
struct get_type<0, T, Ts...>
{
    typedef T type;
};

// Ts[index_type<A, Ts...>::value] == A (Compilation error if A not in Ts)
template <typename A, typename T, typename... Ts>
struct index_type
{
    static const std::size_t value = index_type<A, Ts...>::value + 1;
};

template <typename A, typename... Ts>
struct index_type<A, A, Ts...>
{
    static const std::size_t value = 0;
};

template <typename T>
constexpr T max(const T& a, const T& b)
{
    return a > b ? a : b;
}

// max_size<Ts...>::value
template <typename T, typename... Ts>
struct max_size
{
    static const std::size_t value = max(sizeof(T), max_size<Ts...>::value);
};

template <typename T>
struct max_size<T>
{
    static const std::size_t value = sizeof(T);
};

// max_alignment<Ts...>::value
template <typename T, typename... Ts>
struct max_alignment
{
    static const std::size_t value = max(alignof(T), max_alignment<Ts...>::value);
};

template <typename T>
struct max_alignment<T>
{
    static const std::size_t value = alignof(T);
};

template <typename... Ts>
class PodVariant
{
    std::size_t curr_type;
    alignas(max_alignment<Ts...>::value) char data[max_size<Ts...>::value];

public:
    PodVariant()
        : curr_type()
        , data()
    {
    }

    template <typename T>
    PodVariant(const T& x)
        : curr_type(index_type<T, Ts...>::value)
    {
        auto ptr = reinterpret_cast<const char*>(&x);
        std::copy(ptr, ptr + sizeof(T), this->data);
    }

    template <typename T>
    const T& operator=(const T& x)
    {
        this->curr_type = index_type<T, Ts...>::value;
        auto ptr = reinterpret_cast<const char*>(&x);
        std::copy(ptr, ptr + sizeof(T), this->data);
        return x;
    }

    template <typename T>
    bool is()
    {
        return this->curr_type == index_type<T, Ts...>::value;
    }

    template <typename T>
    T& as()
    {
        if (!this->is<T>())
        {
            throw std::runtime_error("Requested type is not contained");
        }
        return *reinterpret_cast<T*>(this->data);
    }

    template <typename T>
    bool into(T& x)
    {
        if (!this->is<T>())
        {
            return false;
        }
        x = *reinterpret_cast<T*>(this->data);
        return true;
    }
};

#endif
