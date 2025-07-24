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
} // namespace mystl
