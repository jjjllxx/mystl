#pragma once

#include "type_traits.h"

namespace mystl
{
template<typename T>
constexpr typename remove_reference<T>::type&& move(T&& arg) noexcept
{
    return static_cast<typename remove_reference<T>::type&&>(arg);
}

template<typename T>
constexpr T&& forward(typename remove_reference<T>::type& param) noexcept
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

template<class T1, class T2>
struct pair
{
    T1 first {};
    T2 second {};

    pair() = default;
    pair(const T1& a, const T2& b) :
        first(a),
        second(b)
    {
    }
};

template<class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y)
{
    pair<T1, T2> p;
    p.first  = x;
    p.second = y;

    return p;
}

template<class T1, class T2>
inline bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
}

template<class T1, class T2>
inline bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<class T1, class T2>
inline bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs == rhs);
}

template<class T1, class T2>
inline bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return rhs < lhs;
}
template<class T1, class T2>
inline bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(rhs < lhs);
}

template<class T1, class T2>
inline bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs < rhs);
}
} // namespace mystl