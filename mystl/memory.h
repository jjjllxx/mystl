#pragma once

#include "mystl/types.h"
#include "mystl/utility.h"
#include <limits>
#include <new>

namespace mystl
{
template<typename T>
struct allocator
{
    using value_type         = T;
    using pointer            = T*;
    using const_pointer      = const T*;

    using void_pointer       = void*;
    using const_void_pointer = const void*;

    using size_type       = mystl::size_t;
    using difference_type = mystl::ptrdiff_t;

    allocator() noexcept = default;
    template<typename U>
    constexpr allocator(const mystl::allocator<U>&) noexcept
    {
    }

    [[nodiscard]] T* allocate(size_type n)
    {
        if (n > std::numeric_limits<size_type>::max() / sizeof(T))
        {
            throw std::bad_array_new_length();
        }

        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, size_type) noexcept
    {
        ::operator delete(p);
    }

    template<typename U>
    struct rebind
    {
        using other = allocator<U>;
    };
};

template<typename T, typename U>
constexpr bool operator==(const allocator<T>&, const allocator<U>&) noexcept
{
    return true;
}

template<typename T, typename U>
constexpr bool operator!=(const allocator<T>&, const allocator<U>&) noexcept
{
    return false;
}

template<typename Alloc>
struct allocator_traits
{
    using allocate_type      = Alloc;
    using value_type         = typename Alloc::value_type;
    using pointer            = typename Alloc::pointer;
    using const_pointer      = typename Alloc::const_pointer;
    using void_pointer       = typename Alloc::void_pointer;
    using const_void_pointer = typename Alloc::const_void_pointer;

    using size_type       = typename Alloc::size_type;
    using difference_type = typename Alloc::difference_type;

    template<typename T>
    using rebind_alloc = typename Alloc::template rebind<T>::other;

    template<typename T>
    using rebind_traits = allocator_traits<rebind_alloc<T>>;

    static pointer allocate(Alloc& a, size_type n)
    {
        return a.allocate(n);
    }

    static void deallocate(Alloc& a, pointer p , size_type n)
    {
        a.deallocate(p, n);
    }

    template<typename T, typename... Args>
    static void construct(Alloc&, T* p, Args&&... args)
    {
        ::new (static_cast<void*>(p)) T(mystl::forward<Args>(args)...);
    }

    template<typename T>
    static void destroy(Alloc&, T* p)
    {
        p->~T();
    }
};
} // namespace mystl