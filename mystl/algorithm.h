#pragma once

#include "bits/stl_algobase.h"
#include "functional.h"
#include "iterator.h"
#include "utility.h"

namespace mystl
{
// modify
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

// Heap
namespace Detail
{
    template<class RandomIt, class Compare>
    void sift_down(RandomIt                                                   first,
                   typename mystl::iterator_traits<RandomIt>::difference_type start,
                   typename mystl::iterator_traits<RandomIt>::difference_type size,
                   Compare                                                    comp)
    {
        const auto val  = *(first + start);
        auto       hole = start;

        while (2 * hole + 1 < size) // To ensure node at it have both left node and right node
        {
            auto child = 2 * hole + 1;
            if (child + 1 < size && comp(*(first + child), *(first + child + 1)))
            {
                ++child;
            }

            if (comp(val, *(first + child)) == false)
            {
                break;
            }

            *(first + hole) = *(first + child);
            hole            = child;
        }
        *(first + hole) = val;
    }
} // namespace Detail

template<class RandomIt, class Compare>
void make_heap(RandomIt first, RandomIt last, Compare comp)
{
    using Diff      = typename mystl::iterator_traits<RandomIt>::difference_type;
    const Diff size = last - first;

    for (Diff i = size / 2 - 1; i >= 0; --i)
    {
        mystl::Detail::sift_down(first, i, size, comp);
        if (i == 0)
        {
            break; // avoid underflow for unsigned types
        }
    }
}

template<class RandomIt, class Compare>
void push_heap(RandomIt first, RandomIt last, Compare comp)
{
    using Diff = typename mystl::iterator_traits<RandomIt>::difference_type;

    Diff       child = last - first - 1;
    const auto value = *(first + child);
    while (child > 0)
    {
        Diff parent = (child - 1) / 2;
        if (comp(*(first + parent), value) == false)
        {
            break;
        }

        *(first + child) = *(first + parent);
        child            = parent;
    }

    *(first + child) = value;
}

template<class RandomIt, class Compare>
void pop_heap(RandomIt first, RandomIt last, Compare comp)
{
    using Diff = typename mystl::iterator_traits<RandomIt>::difference_type;

    Diff n = last - first;
    if (n <= 1)
    {
        return;
    }

    mystl::iter_swap(first, last - 1);
    mystl::Detail::sift_down(first, Diff { 0 }, n - 1, comp);
}

template<class RandomIt, class Compare>
bool is_heap(RandomIt first, RandomIt last, Compare comp)
{
    using Diff = typename mystl::iterator_traits<RandomIt>::difference_type;

    const Diff n = last - first;

    for (Diff parent = 0; parent < n; ++parent)
    {
        Diff left  = 2 * parent + 1;
        Diff right = 2 * parent + 2;

        if (left < n && comp(*(first + parent), *(first + left)))
        {
            return false;
        }

        if (right < n && comp(*(first + parent), *(first + right)))
        {
            return false;
        }
    }

    return true;
}

template<class RandomIt, class Compare>
RandomIt is_heap_until(RandomIt first, RandomIt last, Compare comp)
{
    using Diff = typename mystl::iterator_traits<RandomIt>::difference_type;

    const Diff n = last - first;

    for (Diff parent = 0; parent < n; ++parent)
    {
        Diff left  = 2 * parent + 1;
        Diff right = 2 * parent + 2;

        if (left < n && comp(*(first + parent), *(first + left)))
        {
            return first + left;
        }

        if (right < n && comp(*(first + parent), *(first + right)))
        {
            return first + right;
        }
    }

    return last;
}

template<class RandomIt, class Compare>
void sort_heap(RandomIt first, RandomIt last, Compare comp)
{
    while (first != last)
    {
        mystl::pop_heap(first, last--, comp);
    }
}

template<class ForwardIt>
ForwardIt min_element(ForwardIt first, ForwardIt last)
{
    using value_type = typename mystl::iterator_traits<ForwardIt>::value_type;
    return mystl::min_element(first, last, mystl::less<value_type>());
}

template<class ForwardIt, class Compare>
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp)
{
    if (first == last)
    {
        return last;
    }

    ForwardIt smallest = first;

    while (++first != last)
    {
        if (comp(*first, *smallest))
        {
            smallest = first;
        }
    }

    return smallest;
}

template<class ForwardIt>
ForwardIt max_element(ForwardIt first, ForwardIt last)
{
    using value_type = typename mystl::iterator_traits<ForwardIt>::value_type;
    return mystl::max_element(first, last, mystl::less<value_type>());
}

template<class ForwardIt, class Compare>
ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp)
{
    if (first == last)
    {
        return last;
    }

    ForwardIt largest = first;

    while (++first != last)
    {
        if (comp(*largest, *first))
        {
            largest = first;
        }
    }

    return largest;
}

template<class T>
constexpr mystl::pair<T, T> minmax(const T& a, const T& b)
{
    return (b < a)
               ? mystl::pair<const T&, const T&>(b, a)
               : mystl::pair<const T&, const T&>(a, b);
}

template<class T, class Compare>
constexpr mystl::pair<T, T> minmax(const T& a, const T& b, Compare comp)
{
    return comp(b, a)
               ? mystl::pair<const T&, const T&>(b, a)
               : mystl::pair<const T&, const T&>(a, b);
}

template<class ForwardIt, class Compare>
mystl::pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first, ForwardIt last, Compare comp)
{
    if (first == last)
    {
        return last;
    }

    ForwardIt smallest = first;
    ForwardIt largest  = first;

    while (++first != last)
    {
        if (comp(*first, *smallest))
        {
            smallest = first;
        }

        if (comp(*largest, *first))
        {
            largest = first;
        }
    }

    return mystl::pair<ForwardIt, ForwardIt>(smallest, largest);
}

// search
template<class InputIt, class T = typename mystl::iterator_traits<InputIt>::value_type>
typename mystl::iterator_traits<InputIt>::difference_type
    count(InputIt first, InputIt last, const T& val)
{
    typename mystl::iterator_traits<InputIt>::difference_type cnt = 0;

    for (; first != last; ++first)
    {
        if (*first == val)
        {
            ++cnt;
        }
    }

    return cnt;
}

template<class InputIt, class T = typename mystl::iterator_traits<InputIt>::value_type, class UnaryPred>
typename mystl::iterator_traits<InputIt>::difference_type
    count_if(InputIt first, InputIt last, UnaryPred p)
{
    typename mystl::iterator_traits<InputIt>::difference_type cnt = 0;

    for (; first != last; ++first)
    {
        if (p(*first))
        {
            ++cnt;
        }
    }

    return cnt;
}

template<class InputIt, class T = typename mystl::iterator_traits<InputIt>::value_type>
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
// sort
template<class InputIt1, class InputIt2, class OutputIt>
OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first)
{
    while (first1 != last1 && first2 != last2)
    {
        if (*first2 < *first1)
        {
            *d_first = *first2;
            first2++;
        }
        else
        {
            *d_first = *first1;
            first1++;
        }

        d_first++;
    }

    mystl::copy(first1, last1, d_first);
    mystl::copy(first2, last2, d_first);

    return d_first;
}

template<class InputIt1, class InputIt2, class OutputIt, class Compare>
OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
{
    while (first1 != last1 && first2 != last2)
    {
        if (comp(*first1, *first2))
        {
            *d_first = *first1;
            first1++;
        }
        else
        {
            *d_first = *first2;
            first2++;
        }

        d_first++;
    }

    mystl::copy(first1, last1, d_first);
    mystl::copy(first2, last2, d_first);

    return d_first;
}

template<class ForwardIt, class UnaryPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
    ForwardIt left  = first;
    ForwardIt right = last - 1;

    while (left <= right)
    {
        if (p(*left) == false && p(*right) == true)
        {
            mystl::swap(*left, *right);
        }

        while (p(*left) == true)
        {
            left++;
        }

        while (p(*right) == false)
        {
            right--;
        }
    }

    return left;
}
} // namespace mystl