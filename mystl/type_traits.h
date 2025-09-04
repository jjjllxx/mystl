#pragma once

namespace mystl
{
template<typename T, T v>
struct integral_constant
{
    static constexpr T value = v;

    using value_type = T;
    using type       = integral_constant;

    constexpr operator value_type() const noexcept
    {
        return value;
    }
};

using true_type  = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template<typename T>
struct remove_reference
{
    using type = T;
};

template<typename T>
struct remove_reference<T&>
{
    using type = T;
};

template<typename T>
struct remove_reference<T&&>
{
    using type = T;
};

template<bool B, class T = void>
struct enable_if
{
};

template<class T>
struct enable_if<true, T>
{
    using type = T;
};

template<bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template<typename T>
struct is_integral_base : false_type
{
};

template<>
struct is_integral_base<bool> : true_type
{
};

template<>
struct is_integral_base<char> : true_type
{
};

template<>
struct is_integral_base<signed char> : true_type
{
};

template<>
struct is_integral_base<unsigned char> : true_type
{
};

template<>
struct is_integral_base<wchar_t> : true_type
{
};

template<>
struct is_integral_base<short> : true_type
{
};

template<>
struct is_integral_base<unsigned short> : true_type
{
};

template<>
struct is_integral_base<int> : true_type
{
};

template<>
struct is_integral_base<unsigned int> : true_type
{
};

template<>
struct is_integral_base<long> : true_type
{
};

template<>
struct is_integral_base<unsigned long> : true_type
{
};

template<>
struct is_integral_base<long long> : true_type
{
};

template<>
struct is_integral_base<unsigned long long> : true_type
{
};

template<typename T>
struct is_integral : is_integral_base<typename remove_reference<T>::type>
{
};

template<typename T>
using is_integral_t = typename is_integral<T>::type;

template<typename T>
constexpr bool is_integral_v = is_integral<T>::value;

template<class T, class U>
struct is_same : mystl::false_type
{
};

template<class T>
struct is_same<T, T> : mystl::true_type
{
};

template<class T, class U>
constexpr bool is_same_v = is_same<T, U>::value;
} // namespace mystl