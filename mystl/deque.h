#pragma once

#include "algorithm.h"
#include "iterator.h"
#include "type_traits.h"
#include <initializer_list>
#include <stdexcept>

namespace mystl
{
template<typename T>
constexpr mystl::size_t get_block_size()
{
    return sizeof(T) < 512 ? 512 / sizeof(T) : 1;
}

template<typename T>
static constexpr mystl::size_t BLOCK_SIZE = get_block_size<T>();

static constexpr mystl::size_t INITIAL_MAP_SIZE = 8;

template<typename T>
class deque
{
public:
    class iterator
    {
        T*  cur   = nullptr;
        T*  first = nullptr;
        T*  last  = nullptr;
        T** node  = nullptr; // pointer to block pointer

    public:
        using value_type        = T;
        using difference_type   = mystl::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = mystl::random_access_iterator_tag;

        reference operator*()
        {
            return *this->cur;
        }

        reference operator*() const
        {
            return *this->cur;
        }

        iterator& operator++()
        {
            ++this->cur;

            if (this->cur == this->last)
            {
                ++this->node;
                this->first = *this->node;
                this->cur   = this->first;
                this->last  = this->first + BLOCK_SIZE<T>;
            }

            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--()
        {
            if (this->cur == this->first)
            {
                --this->node;
                this->first = *this->node;
                this->last  = this->first + BLOCK_SIZE<T>;
                this->cur   = this->last - 1;
            }
            else
            {
                --this->cur;
            }

            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        iterator operator+(const mystl::ptrdiff_t n) const
        {
            const mystl::ptrdiff_t offset      = this->cur - this->first + n;
            mystl::ptrdiff_t       blockOffset = offset / BLOCK_SIZE<T>;
            mystl::ptrdiff_t       idxInBlock  = offset % BLOCK_SIZE<T>;

            if (idxInBlock < 0)
            {
                --blockOffset;
                idxInBlock += BLOCK_SIZE<T>;
            }

            iterator tmp;
            tmp.node  = this->node + blockOffset;
            tmp.first = *tmp.node;
            tmp.cur   = tmp.first + idxInBlock;
            tmp.last  = tmp.first + BLOCK_SIZE<T>;

            return tmp;
        }

        iterator operator-(const mystl::ptrdiff_t n) const
        {
            return *this + (-n);
        }

        iterator& operator+=(const mystl::ptrdiff_t n)
        {
            *this = *this + n;
            return *this;
        }

        iterator& operator-=(const mystl::ptrdiff_t n)
        {
            *this = *this - n;
            return *this;
        }

        difference_type operator-(const iterator& other) const
        {
            return static_cast<difference_type>((this->node - other.node) * BLOCK_SIZE<T>
                                                + (this->cur - this->first)
                                                - (other.cur - other.first));
        }

        bool operator==(const iterator& other) const
        {
            return this->node == other.node && this->cur == other.cur;
        }

        bool operator!=(const iterator& rhs) const
        {
            return !(*this == rhs);
        }

        bool operator<(const iterator& other) const
        {
            return (*this - other) < 0;
        }

        bool operator>(const iterator& other) const
        {
            return other < *this;
        }

        bool operator<=(const iterator& other) const
        {
            return !(*this > other);
        }

        bool operator>=(const iterator& other) const
        {
            return !(*this < other);
        }

        friend class deque;
    };

    class const_iterator
    {
        T*  cur   = nullptr;
        T*  first = nullptr;
        T*  last  = nullptr;
        T** node  = nullptr; // pointer to block pointer

    public:
        using value_type        = T;
        using difference_type   = mystl::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = mystl::random_access_iterator_tag;

        const_iterator(const iterator& it) :
            cur(it.cur),
            first(it.first),
            last(it.last),
            node(it.node)
        {
        }

        reference operator*() const
        {
            return *this->cur;
        }

        const_iterator& operator++()
        {
            ++this->cur;

            if (this->cur == this->last)
            {
                ++this->node;
                this->first = *this->node;
                this->cur   = this->first;
                this->last  = this->first + BLOCK_SIZE<T>;
            }

            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const_iterator& operator--()
        {
            if (this->cur == this->first)
            {
                --this->node;
                this->first = *this->node;
                this->last  = this->first + BLOCK_SIZE<T>;
                this->cur   = this->last - 1;
            }
            else
            {
                --this->cur;
            }

            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        const_iterator operator+(const mystl::ptrdiff_t n) const
        {
            const mystl::ptrdiff_t offset      = this->cur - this->first + n;
            mystl::ptrdiff_t       blockOffset = offset / BLOCK_SIZE<T>;
            mystl::ptrdiff_t       idxInBlock  = offset % BLOCK_SIZE<T>;

            if (idxInBlock < 0)
            {
                --blockOffset;
                idxInBlock += BLOCK_SIZE<T>;
            }

            const_iterator tmp;
            tmp.node  = this->node + blockOffset;
            tmp.first = *tmp.node;
            tmp.cur   = tmp.first + idxInBlock;
            tmp.last  = tmp.first + BLOCK_SIZE<T>;

            return tmp;
        }

        const_iterator operator-(const mystl::ptrdiff_t n) const
        {
            return *this + (-n);
        }

        const_iterator& operator+=(const mystl::ptrdiff_t n)
        {
            *this = *this + n;
            return *this;
        }

        const_iterator& operator-=(const mystl::ptrdiff_t n)
        {
            *this = *this - n;
            return *this;
        }

        difference_type operator-(const const_iterator& other) const
        {
            return static_cast<difference_type>((this->node - other.node) * BLOCK_SIZE<T>
                                                + (this->cur - this->first)
                                                - (other.cur - other.first));
        }

        bool operator==(const const_iterator& other) const
        {
            return this->node == other.node && this->cur == other.cur;
        }

        bool operator!=(const const_iterator& rhs) const
        {
            return !(*this == rhs);
        }

        bool operator<(const const_iterator& other) const
        {
            return (*this - other) < 0;
        }

        bool operator>(const const_iterator& other) const
        {
            return other < *this;
        }

        bool operator<=(const const_iterator& other) const
        {
            return !(*this > other);
        }

        bool operator>=(const const_iterator& other) const
        {
            return !(*this < other);
        }

        friend class deque;
    };

public:
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;
    using size_type       = mystl::size_t;
    using difference_type = mystl::ptrdiff_t;

    deque() :
        sz(0)
    {
        this->allocate_map(0);
    }

    deque(const size_type n) :
        sz(n)
    {
        this->allocate_map(n);
        iterator it = this->start;

        for (size_type idx = 0; idx < n; ++idx)
        {
            *it = T {};
            ++it;
        }

        this->finish = it;
    }

    deque(const std::initializer_list<T>& list) :
        sz(list.size())
    {
        this->allocate_map(list.size());
        iterator it = this->start;

        for (const_reference val : list)
        {
            *it = val;
            ++it;
        }

        this->finish = it;
    }

    deque(const size_type n, const_reference val) :
        sz(n)
    {
        this->allocate_map(n);
        iterator it = this->start;

        for (size_type idx = 0; idx < n; ++idx, ++it)
        {
            *it = val;
        }

        this->finish = it;
    }

    template<class InputIt, typename = mystl::enable_if_t<!mystl::is_integral_v<InputIt>>>
    deque(InputIt first, InputIt last) :
        sz(mystl::distance(first, last))
    {
        this->allocate_map(this->sz);
        iterator out = this->start;

        for (InputIt in = first; in != last; ++in, ++out)
        {
            *out = *in;
        }

        this->finish = out;
    }

    deque(const mystl::deque<T>& other) :
        sz(other.sz)
    {
        this->allocate_map(other.sz);
        iterator it = this->start;

        for (const_reference val : other)
        {
            *it = val;
            ++it;
        }

        this->finish = it;
    }

    mystl::deque<T>& operator=(const mystl::deque<T>& other)
    {
        if (this != &other)
        {
            for (size_type idx = 0; idx < this->map_size; ++idx)
            {
                if (this->map[idx] != nullptr)
                {
                    delete[] this->map[idx];
                }
            }

            delete[] this->map;

            this->sz = other.sz;

            this->allocate_map(this->sz);

            iterator it = this->start;

            for (const_reference val : other)
            {
                *it = val;
                ++it;
            }

            this->finish = it;
        }

        return *this;
    }

    deque(mystl::deque<T>&& other) noexcept :
        map(other.map),
        map_size(other.map_size),
        sz(other.sz),
        start(other.start),
        finish(other.finish)
    {
        other.map      = nullptr;
        other.map_size = 0;
        other.sz       = 0;
        other.start    = {};
        other.finish   = {};
    }

    mystl::deque<T>& operator=(mystl::deque<T>&& other) noexcept
    {
        if (this != &other)
        {
            for (size_type idx = 0; idx < this->map_size; ++idx)
            {
                if (this->map[idx] != nullptr)
                {
                    delete[] this->map[idx];
                }
            }

            delete[] this->map;

            this->map      = other.map;
            this->map_size = other.map_size;
            this->sz       = other.sz;
            this->start    = other.start;
            this->finish   = other.finish;

            other.map      = nullptr;
            other.map_size = 0;
            other.sz       = 0;
            other.start    = {};
            other.finish   = {};
        }

        return *this;
    }

    ~deque()
    {
        for (size_type idx = 0; idx < this->map_size; ++idx)
        {
            if (this->map[idx] != nullptr)
            {
                delete[] this->map[idx];
            }
        }
        delete[] this->map;
    }

    const_reference front() const
    {
        return *this->start;
    }

    reference front()
    {
        return *this->start;
    }

    reference back()
    {
        if (this->finish.cur == this->finish.first)
        {
            return *(*(this->finish.node - 1) + BLOCK_SIZE<T> - 1);
        }

        return *(this->finish.cur - 1);
    }

    const_reference back() const
    {
        if (this->finish.cur == this->finish.first)
        {
            return *(*(this->finish.node - 1) + BLOCK_SIZE<T> - 1);
        }

        return *(this->finish.cur - 1);
    }

    size_type size() const
    {
        return this->sz;
    }

    bool empty() const
    {
        return this->sz == 0;
    }

    reference operator[](const size_type idx)
    {
        return *(this->start + idx);
    }

    const_reference operator[](const size_type idx) const
    {
        return *(this->start + idx);
    }

    reference at(const size_type idx)
    {
        if (idx >= this->sz)
        {
            throw std::out_of_range("Index out of range in deque::at()");
        }

        return *(this->start + idx);
    }

    const_reference at(const size_type idx) const
    {
        if (idx >= this->sz)
        {
            throw std::out_of_range("Index out of range in deque::at()");
        }

        return *(this->start + idx);
    }

    const_iterator begin() const
    {
        return const_iterator { this->start };
    }

    const_iterator end() const
    {
        return const_iterator { this->finish };
    }

    const_iterator cbegin() const
    {
        return const_iterator { this->start };
    }

    const_iterator cend() const
    {
        return const_iterator { this->finish };
    }

    iterator begin()
    {
        return this->start;
    }

    iterator end()
    {
        return this->finish;
    }

    void push_front(const_reference val)
    {
        if (this->start.node == this->map && this->start.cur == this->start.first)
        {
            this->resize_map(this->map_size << 1);
        }

        if (this->start.cur == this->start.first)
        {
            if (*(this->start.node - 1) == nullptr)
            {
                *(this->start.node - 1) = new T[BLOCK_SIZE<T>];
            }
        }

        --this->start;
        *this->start = val;
        ++this->sz;
    }

    void push_back(const_reference val)
    {
        if (this->finish.node == this->map + this->map_size - 1 && this->finish.cur == this->finish.last - 1)
        {
            this->resize_map(this->map_size << 1);
        }

        if (this->finish.cur == this->finish.last - 1)
        {
            if (*(this->finish.node + 1) == nullptr)
            {
                *(this->finish.node + 1) = new T[BLOCK_SIZE<T>];
            }
            ++this->finish;
        }

        *this->finish = val;
        ++this->finish;
        ++this->sz;
    }

    void pop_front()
    {
        ++this->start;
        --this->sz;
    }

    void pop_back()
    {
        --this->finish;
        --this->sz;
    }

    void clear()
    {
        this->sz     = 0;
        this->finish = this->start;
    }

private:
    pointer*  map;      // pointer to an array of blocks (map of pointers)
    size_type map_size; // number of pointers in the map
    size_type sz;       // number of pointers in the map

    iterator start;
    iterator finish;

    void allocate_map(const size_type n)
    {
        const size_type totalBlocks = (n + BLOCK_SIZE<value_type> - 1) / BLOCK_SIZE<value_type>;

        this->map_size = mystl::max(INITIAL_MAP_SIZE, totalBlocks << 1);
        this->map      = new pointer[this->map_size] {

        };

        const size_type startIdx = (this->map_size - totalBlocks) >> 1;
        for (size_type i = 0; i < mystl::max<size_type>(1, totalBlocks); ++i)
        {
            this->map[startIdx + i] = new value_type[BLOCK_SIZE<value_type>];
        }

        this->start.node  = this->map + startIdx;
        this->start.first = *this->start.node;
        this->start.cur   = this->start.first;
        this->start.last  = this->start.first + BLOCK_SIZE<value_type>;
        this->finish      = this->start;
    }

    void resize_map(const size_type newMapSize)
    {
        if (newMapSize * BLOCK_SIZE<value_type> > this->sz)
        {
            const size_type newMapSize = this->map_size << 1;

            pointer* newMap = new pointer[newMapSize] {};

            const size_type totalBlocks = (this->sz + BLOCK_SIZE<value_type> - 1) / BLOCK_SIZE<value_type>;
            const size_type newCenter   = (newMapSize - totalBlocks) >> 1;

            for (size_type i = 0; i < totalBlocks; ++i)
            {
                newMap[newCenter + i] = this->map[i];
            }

            this->start.node  = newMap + newCenter;
            this->start.first = *this->start.node;
            this->start.cur   = this->start.first;
            this->start.last  = this->start.first + BLOCK_SIZE<value_type>;
            this->finish      = this->start + this->sz;

            delete[] this->map;
            this->map      = newMap;
            this->map_size = newMapSize;
        }
    }
};
} // namespace mystl