#pragma once

namespace mystl
{
template<typename T = void>
struct less
{
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs < rhs;
    }
};

template<typename T = void>
struct greater
{
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs > rhs;
    }
};
} // namespace mystl