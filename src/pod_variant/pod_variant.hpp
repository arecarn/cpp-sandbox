#ifndef POD_VARIANT_HPP
#define POD_VARIANT_HPP

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

// get_type<i, Ts...>::type -> Ts[i] (Compile error of i >= length(Ts))
template <std::size_t I, typename T, typename... Ts>
struct GetType
{
    using type = typename GetType<I - 1, Ts...>::type;
};

template <typename T, typename... Ts>
struct GetType<0, T, Ts...>
{
    using type = T;
};

// Ts[index_type<A, Ts...>::Value] == A (Compilation error if A not in Ts)
template <typename A, typename T, typename... Ts>
struct IndexType
{
    static const std::size_t Value = IndexType<A, Ts...>::Value + 1;
};

template <typename A, typename... Ts>
struct IndexType<A, A, Ts...>
{
    static const std::size_t Value = 0;
};

template <typename T>
constexpr T max(const T& a, const T& b)
{
    return a > b ? a : b;
}

// max_size<Ts...>::Value
template <typename T, typename... Ts>
struct MaxSize
{
    static const std::size_t Value = max(sizeof(T), MaxSize<Ts...>::Value);
};

template <typename T>
struct MaxSize<T>
{
    static const std::size_t Value = sizeof(T);
};

// max_alignment<Ts...>::Value
template <typename T, typename... Ts>
struct MaxAlignment
{
    static const std::size_t Value = max(alignof(T), MaxAlignment<Ts...>::Value);
};

template <typename T>
struct MaxAlignment<T>
{
    static const std::size_t Value = alignof(T);
};

template <typename... Ts>
class PodVariant
{
    std::size_t m_curr_type{};
    alignas(MaxAlignment<Ts...>::Value) char m_data[MaxSize<Ts...>::Value]{}; //NOLINT

public:
    PodVariant() = default;

    template <typename T>
    PodVariant(const T& x)
        : m_curr_type(IndexType<T, Ts...>::Value)
    {
        const auto* ptr = reinterpret_cast<const char*>(&x);
        std::copy(ptr, ptr + sizeof(T), this->m_data);
    }

    template <typename T>
    const T& operator=(const T& x)
    {
        this->m_curr_type = IndexType<T, Ts...>::Value;
        const auto* const ptr = reinterpret_cast<const char*>(&x);
        std::copy(ptr, ptr + sizeof(T), this->m_data);
        return x;
    }

    template <typename T>
    bool is()
    {
        return this->m_curr_type == IndexType<T, Ts...>::Value;
    }
    template <typename T>
    T& as()
    {
        if (!this->is<T>())
        {
            throw std::runtime_error("Requested type is not contained");
        }
        return *reinterpret_cast<T*>(this->m_data);
    }

    template <typename T>
    bool into(T& x)
    {
        std::vector<int> v;

        if (!this->is<T>())
        {
            return false;
        }
        x = *reinterpret_cast<T*>(this->m_data);
        return true;
    }
};

#endif
