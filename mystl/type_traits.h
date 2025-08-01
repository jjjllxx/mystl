#pragma once

namespace mystl
{
template<typename T, T v>
struct integral_constant
{
    static constexpr T Value = v;

    using value_type = T;
    using Type       = integral_constant;

    constexpr operator value_type() const noexcept
    {
        return Value;
    }
};

using true_type  = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template<typename T>
struct remove_reference
{
    using Type = T;
};

template<typename T>
struct remove_reference<T&>
{
    using Type = T;
};

template<typename T>
struct remove_reference<T&&>
{
    using Type = T;
};
} // namespace mystl
