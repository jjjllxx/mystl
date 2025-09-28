#pragma once

namespace mystl {
template<class T>
const T& min(const T& a, const T& b)
{
    return b < a ? b : a;
}

template<class T, class Compare>
const T& min(const T& a, const T& b, Compare comp)
{
    return comp(b, a) ? b : a;
}

template<class T>
const T& max(const T& a, const T& b)
{
    return a < b ? b : a;
}

template<class T, class Compare>
const T& max(const T& a, const T& b, Compare comp)
{
    return comp(a, b) ? b : a;
}

template<typename InputIt, typename OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt dest)
{
    while (first != last)
    {
        *dest = *first;
        ++first;
        ++dest;
    }
    return dest;
}

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (*first1 != *first2)
        {
            return false;
        }
    }

    return true;
}

template<class InputIt1, class InputIt2, class BinaryPred>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPred p)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (!p(*first1, *first2))
        {
            return false;
        }
    }

    return true;
}
}