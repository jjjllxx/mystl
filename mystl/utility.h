#pragma once

#include "type_traits.h"

namespace mystl
{
template<typename T>
constexpr typename remove_reference<T>::Type&& move(T&& arg) noexcept
{
    return static_cast<typename remove_reference<T>::Type&&>(arg);
}

template<typename T>
constexpr T&& forward(typename remove_reference<T>::Type& param) noexcept
{
    return static_cast<T&&>(param);
}

template<typename T>
void swap(T& a, T& b)
{
    T temp = mystl::move(a);
    a      = mystl::move(b);
    b      = mystl::move(temp);
}
} // namespace mystl
