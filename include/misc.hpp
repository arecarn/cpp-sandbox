#include <type_traits>

// Get the underlying type of a class enumeration value
template <typename Enum>
constexpr auto to_underlying(Enum enum_value) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>(enum_value);
}
