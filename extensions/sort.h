#pragma once

#include "mystl/algorithm.h"
#include "mystl/iterator.h"
#include "mystl/vector.h"

namespace ext
{
namespace sort
{
    template<class It>
    void merge_sort_recursive(It it, const mystl::size_t left, const mystl::size_t right)
    {
        if (right - left <= 1)
        {
            return;
        }

        const mystl::size_t mid = ((right - left) >> 1) + left;
        merge_sort_recursive(it, left, mid);
        merge_sort_recursive(it, mid, right);

        if (*(it + mid - 1) <= *(it + mid))
        {
            return;
        }

        using value_type = typename mystl::iterator_traits<It>::value_type;
        mystl::vector<value_type> buffer(right - left);
        mystl::merge(it + left, it + mid, it + mid, it + right, buffer.begin());
        mystl::copy(buffer.begin(), buffer.end(), it + left);
    }

    template<class It>
    void merge_sort_iterative(It it, const mystl::size_t left, const mystl::size_t right)
    {
        using value_type = typename mystl::iterator_traits<It>::value_type;
        for (mystl::size_t sz = 1; sz < right - left; sz += sz)
        {
            for (mystl::size_t lo = left; lo < right - sz; lo += sz + sz)
            {
                const mystl::size_t mid = lo + sz;

                if (*(it + mid - 1) <= *(it + mid))
                {
                    continue;
                }

                const mystl::size_t hi = mystl::min(mid + sz, right);

                mystl::vector<value_type> buffer(hi - lo);
                mystl::merge(it + lo, it + mid, it + mid, it + hi, buffer.begin());
                mystl::copy(buffer.begin(), buffer.end(), it + lo);
            }
        }
    }
} // namespace sort
} // namespace ext