#pragma once

#include "iterator.h"
namespace mystl
{
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

template<typename ForwardIt1, typename ForwardIt2>
void iter_swap(ForwardIt1 it1, ForwardIt2 it2)
{
    mystl::swap(*it1, *it2);
}

// Binary Search
template<class ForwardIt, typename T = mystl::iterator_traits<ForwardIt>::value_type, class Compare>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& val, Compare comp)
{
    typename mystl::iterator_traits<ForwardIt>::difference_type cnt, step;

    cnt = mystl::distance(first, last);
    ForwardIt it;

    while (cnt > 0)
    {
        it   = first;
        step = cnt / 2;
        mystl::advance(it, step);

        if (comp(*it, val))
        {
            first = ++it;
            cnt -= step + 1;
        }
        else
        {
            cnt = step;
        }
    }

    return first;
}

template<class ForwardIt, typename T = mystl::iterator_traits<ForwardIt>::value_type>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& val)
{
    return mystl::lower_bound(first, last, val, mystl::less<T>());
}

template<class ForwardIt, typename T = mystl::iterator_traits<ForwardIt>::value_type, class Compare>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& val, Compare comp)
{
    typename mystl::iterator_traits<ForwardIt>::difference_type cnt, step;

    cnt = mystl::distance(first, last);
    ForwardIt it;

    while (cnt > 0)
    {
        it   = first;
        step = cnt / 2;
        mystl::advance(it, step);

        if (!comp(val, *it))
        {
            first = ++it;
            cnt -= step + 1;
        }
        else
        {
            cnt = step;
        }
    }

    return first;
}

template<class ForwardIt, typename T = mystl::iterator_traits<ForwardIt>::value_type>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& val)
{
    return mystl::upper_bound(first, last, val, mystl::less<T>());
}

template<class ForwardIt, typename T = mystl::iterator_traits<ForwardIt>::value_type, class Compare>
bool binary_search(ForwardIt first, ForwardIt last, const T& val, Compare comp)
{
    first = mystl::lower_bound(first, last, val, comp);
    return !(first == last) && !comp(val, *first);
}

template<class ForwardIt, typename T = mystl::iterator_traits<ForwardIt>::value_type>
bool binary_search(ForwardIt first, ForwardIt last, const T& val)
{
    return mystl::binary_search(first, last, val, mystl::less<T>());
}

template<class ForwardIt, typename T = mystl::iterator_traits<ForwardIt>::value_type, class Compare>
mystl::pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last, const T& val, Compare comp)
{
    first = mystl::lower_bound(first, last, val, comp);
    last  = mystl::upper_bound(first, last, val, comp);
    return mystl::make_pair(first, last);
}

template<class ForwardIt, typename T = mystl::iterator_traits<ForwardIt>::value_type>
mystl::pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last, const T& val)
{
    return mystl::equal_range(first, last, val, mystl::less<T>());
}

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
