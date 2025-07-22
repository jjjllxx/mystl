#pragma once

#include "iterator.h"
namespace mystl
{
template<class InputIt, class T = typename mystl::IteratorTraits<InputIt>::ValueType>
typename mystl::IteratorTraits<InputIt>::DifferenceType
    count(InputIt first, InputIt last, const T& val)
{
    typename mystl::IteratorTraits<InputIt>::DifferenceType cnt = 0;

    for (; first != last; ++first)
    {
        if (*first == val)
        {
            ++cnt;
        }
    }

    return cnt;
}

template<class InputIt, class T = typename mystl::IteratorTraits<InputIt>::ValueType, class UnaryPred>
typename mystl::IteratorTraits<InputIt>::DifferenceType
    count_if(InputIt first, InputIt last, UnaryPred p)
{
    typename mystl::IteratorTraits<InputIt>::DifferenceType cnt = 0;

    for (; first != last; ++first)
    {
        if (p(*first))
        {
            ++cnt;
        }
    }

    return cnt;
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

template<class InputIt, class T = typename mystl::IteratorTraits<InputIt>::ValueType>
constexpr InputIt find(InputIt first, InputIt last, const T& val)
{
    for (; first != last; ++first)
    {
        if (*first == val)
        {
            return first;
        }
    }

    return last;
}

template<class InputIt, class UnaryPred>
constexpr InputIt find_if(InputIt first, InputIt last, UnaryPred p)
{
    for (; first != last; ++first)
    {
        if (p(*first))
        {
            return first;
        }
    }

    return last;
}

template<class InputIt, class UnaryPred>
constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPred q)
{
    for (; first != last; ++first)
    {
        if (!q(*first))
        {
            return first;
        }
    }

    return last;
}

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (*first1 < *first2)
        {
            return true;
        }

        if (*first2 < *first1)
        {
            return false;
        }
    }

    return first1 == last1 && first2 != last2;
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (comp(*first1, *first2))
        {
            return true;
        }

        if (comp(*first2, *first1))
        {
            return false;
        }
    }

    return first1 == last1 && first2 != last2;
}
} // namespace mystl
