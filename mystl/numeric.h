#pragma once

namespace mystl
{
template<class ForwardIt, class T>
void iota(ForwardIt first, ForwardIt last, T value)
{
    for (;first != last; ++first, ++value)
    {
        *first = value;
    }
}
} // namespace mystl