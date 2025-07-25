#pragma once

#include "types.h"

namespace mystl
{
struct input_iterator_tag
{
};

struct output_iterator_tag
{
};

struct forward_iterator_tag : public input_iterator_tag
{
};

struct bidirectional_iterator_tag : public forward_iterator_tag
{
};

struct random_access_iterator_tag : bidirectional_iterator_tag
{
};

template<typename iterator>
struct iterator_traits
{
    using value_type        = typename iterator::value_type;
    using reference         = typename iterator::reference;
    using pointer           = typename iterator::pointer;
    using difference_type   = typename iterator::difference_type;
    using iterator_category = typename iterator::iterator_category;
};

template<typename T>
struct iterator_traits<T*>
{
    using value_type        = T;
    using reference         = T&;
    using pointer           = T*;
    using difference_type   = mystl::ptrdiff_t;
    using iterator_category = mystl::random_access_iterator_tag;
};

template<typename T>
struct iterator_traits<const T*>
{
    using value_type        = T;
    using reference         = const T&;
    using pointer           = const T*;
    using difference_type   = mystl::ptrdiff_t;
    using iterator_category = mystl::random_access_iterator_tag;
};

namespace detail
{
    template<class It>
    void do_advance(It& it, typename iterator_traits<It>::difference_type n, input_iterator_tag)
    {
        while (n > 0)
        {
            --n;
            ++it;
        }
    }

    template<class It>
    void do_advance(It& it, typename iterator_traits<It>::difference_type n, bidirectional_iterator_tag)
    {
        while (n > 0)
        {
            --n;
            ++it;
        }

        while (n < 0)
        {
            ++n;
            --it;
        }
    }

    template<class It>
    void do_advance(It& it, typename iterator_traits<It>::difference_type n, random_access_iterator_tag)
    {
        it += n;
    }

    template<class It>
    typename iterator_traits<It>::difference_type
        do_distance(It first, It last, random_access_iterator_tag)
    {
        return last - first;
    }

    template<class It>
    typename iterator_traits<It>::difference_type
        do_distance(It first, It last, input_iterator_tag)
    {
        typename iterator_traits<It>::difference_type cnt = 0;
        while (first != last)
        {
            ++first;
            ++cnt;
        }
        return cnt;
    }
} // namespace detail

template<class It, class Distance>
void advance(It& it, Distance n)
{
    mystl::detail::do_advance(it,
                              typename iterator_traits<It>::difference_type { n },
                              typename iterator_traits<It>::iterator_category {});
}

template<class InputIt>
InputIt next(InputIt it, typename iterator_traits<InputIt>::difference_type n = 1)
{
    mystl::advance(it, n);
    return it;
}

template<class InputIt>
InputIt prev(InputIt it, typename iterator_traits<InputIt>::difference_type n = -1)
{
    mystl::advance(it, -n);
    return it;
}

template<class It>
constexpr typename iterator_traits<It>::difference_type
    distance(It first, It last)
{
    return mystl::detail::do_distance(first,
                                      last,
                                      typename iterator_traits<It>::iterator_category {});
}
} // namespace mystl
