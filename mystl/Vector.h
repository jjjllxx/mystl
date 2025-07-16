#pragma once

#include "algorithm.h"
#include "iterator.h"
#include "types.h"
#include <initializer_list>
#include <stdexcept>

namespace mystl
{
template<typename T>
class vector
{
public:
    class iterator
    {
        T* p;

    public:
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;
        using difference_type   = mystl::ptrdiff_t;
        using iterator_category = mystl::random_access_iterator_tag;

        iterator() = default;
        explicit iterator(pointer ptr) :
            p(ptr)
        {
        }

        reference operator*()
        {
            return *this->p;
        }

        reference operator*() const
        {
            return *this->p;
        }

        pointer operator->() const
        {
            return this->p;
        }

        iterator& operator++()
        {
            ++this->p;
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
            --this->p;
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        iterator operator+(const difference_type n) const
        {
            iterator tmp { this->p + n };
            return tmp;
        }

        iterator operator-(const difference_type n) const
        {
            return *this + (-n);
        }

        iterator& operator+=(const difference_type n)
        {
            *this = *this + n;
            return *this;
        }

        iterator& operator-=(const difference_type n)
        {
            *this = *this - n;
            return *this;
        }

        difference_type operator-(const iterator& other) const
        {
            return static_cast<difference_type>(this->p - other.p);
        }

        bool operator==(const iterator& other) const
        {
            return this->p == other.p;
        }

        bool operator!=(const iterator& rhs) const
        {
            return !(*this == rhs);
        }

        bool operator<(const iterator& other) const
        {
            return this->p < other.p;
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
            return !(this->p < other.p);
        }

        friend class vector;
    };

    class const_iterator
    {
        const T* p;

    public:
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using difference_type   = mystl::ptrdiff_t;
        using iterator_category = mystl::random_access_iterator_tag;

        const_iterator() = default;
        explicit const_iterator(pointer ptr) :
            p(ptr)
        {
        }

        const_iterator(const iterator& it) :
            p(it.p)
        {
        }

        reference operator*() const
        {
            return *p;
        }

        pointer operator->() const
        {
            return p;
        }

        const_iterator& operator++()
        {
            ++p;
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
            --p;
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        const_iterator operator+(difference_type n) const
        {
            return const_iterator(p + n);
        }

        const_iterator operator-(difference_type n) const
        {
            return const_iterator(p - n);
        }

        difference_type operator-(const const_iterator& other) const
        {
            return p - other.p;
        }

        const_iterator& operator+=(difference_type n)
        {
            p += n;
            return *this;
        }

        const_iterator& operator-=(difference_type n)
        {
            p -= n;
            return *this;
        }

        bool operator==(const const_iterator& other) const
        {
            return p == other.p;
        }

        bool operator!=(const const_iterator& other) const
        {
            return p != other.p;
        }

        bool operator<(const const_iterator& other) const
        {
            return p < other.p;
        }

        bool operator>(const const_iterator& other) const
        {
            return p > other.p;
        }

        bool operator<=(const const_iterator& other) const
        {
            return p <= other.p;
        }

        bool operator>=(const const_iterator& other) const
        {
            return p >= other.p;
        }

        friend class vector;
    };

    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;
    using size_type       = mystl::size_t;
    using difference_type = mystl::ptrdiff_t;

    vector() :
        sz(0),
        cap(0),
        data(nullptr)
    {
    }

    vector(const size_type n) :
        sz(n),
        cap(n),
        data(new T[n])
    {
        for (size_type i = 0; i < this->sz; ++i)
        {
            *(this->data + i) = 0;
        }
    }

    vector(const size_type n,
           const T&        item) :
        sz(n),
        cap(n),
        data(new T[n])
    {
        for (size_type i = 0; i < this->sz; ++i)
        {
            *(this->data + i) = item;
        }
    }

    vector(const std::initializer_list<T>& init_list) :
        sz(init_list.size()),
        cap(init_list.size()),
        data(new T[init_list.size()])
    {
        size_type i = 0;
        for (const T& val : init_list)
        {
            *(this->data + i++) = val;
        }
    }

    vector(const vector<T>& other) :
        sz(other.sz),
        cap(other.cap),
        data(new T[cap])
    {
        mystl::copy(other.data, other.data + other.sz, this->data);
    }

    vector<T>& operator=(const vector<T>& other)
    {
        if (this != &other)
        {
            delete[] this->data;
            this->cap  = other.cap;
            this->data = new T[this->cap];
            mystl::copy(other.data, other.data + other.sz, this->data);
            this->sz = other.sz;
        }

        return *this;
    }

    vector(vector<T>&& other) noexcept :
        sz(other.sz),
        cap(other.cap),
        data(other.data)
    {
        other.cap  = 0;
        other.sz   = 0;
        other.data = nullptr;
    }

    vector<T>& operator=(vector<T>&& other) noexcept
    {
        if (this != &other)
        {
            delete[] this->data;
            this->cap  = other.cap;
            this->sz   = other.sz;
            this->data = other.data;

            other.cap  = 0;
            other.sz   = 0;
            other.data = nullptr;
        }

        return *this;
    }

    ~vector()
    {
        delete[] this->data;
    }

    size_type size() const
    {
        return this->sz;
    }

    size_type capacity() const
    {
        return this->cap;
    }

    bool empty() const
    {
        return this->sz == 0;
    }

    reference operator[](const size_type n)
    {
        return *(this->data + n);
    }

    const_reference operator[](const size_type n) const
    {
        return *(this->data + n);
    }

    const_iterator begin() const
    {
        return const_iterator { this->data };
    }

    const_iterator end() const
    {
        return const_iterator { this->data + this->sz };
    }

    const_iterator cbegin() const
    {
        return const_iterator { this->data };
    }

    const_iterator cend() const
    {
        return const_iterator { this->data + this->sz };
    }

    iterator begin()
    {
        return iterator { this->data };
    }

    iterator end()
    {
        return iterator { this->data + this->sz };
    }

    reference at(const size_type idx)
    {
        if (idx >= this->sz)
        {
            throw std::out_of_range("Index out of range in vector::at()");
        }

        return *(this->data + idx);
    }

    const_reference at(const size_type pos) const
    {
        if (pos >= this->sz)
        {
            throw std::out_of_range("Index out of range in vector::at()");
        }

        return *(this->data + pos);
    }

    const_reference front() const
    {
        return *this->data;
    }

    reference front()
    {
        return *this->data;
    }

    const_reference back() const
    {
        return *(this->data + this->sz - 1);
    }

    reference back()
    {
        return *(this->data + this->sz - 1);
    }

    void push_back(const T& value)
    {
        if (this->sz == this->cap)
        {
            this->reserve(this->cap == 0 ? 1 : this->cap << 1);
        }

        *(this->data + this->sz++) = value;
    }

    void pop_back()
    {
        --this->sz;
    }

    iterator insert(const_iterator pos,
                    const T&       value)
    {
        return this->insert(pos, 1, value);
    }

    iterator insert(const_iterator  pos,
                    const size_type count,
                    const T&        value)
    {
        const difference_type idx = pos - const_iterator { this->data };

        if (count == 0)
        {
            return iterator { this->data + idx };
        }

        if (this->sz + count > this->cap)
        {
            this->reserve(mystl::max(this->cap << 1, this->sz + count));
        }

        for (size_type i = this->sz + count - 1; i >= idx + count; --i)
        {
            this->data[i] = mystl::move(this->data[i - count]);
        }

        for (size_type i = 0; i < count; ++i)
        {
            this->data[idx + i] = value;
        }

        this->sz += count;

        return iterator { this->data + idx };
    }

    template<class InputIt, typename = typename mystl::enable_if_t<!mystl::is_integral_v<InputIt>>>
    iterator insert(const_iterator pos,
                    InputIt        first,
                    InputIt        last)
    {
        const difference_type idx = pos - const_iterator { this->data };

        if (first >= last)
        {
            return iterator { this->data + idx };
        }

        size_type cnt = 0;
        for (InputIt it = first; it != last; ++it)
        {
            ++cnt;
        }

        if (this->sz + cnt > this->cap)
        {
            this->reserve(mystl::max(this->cap << 1, this->sz + cnt));
        }

        for (size_type i = this->sz + cnt; i > idx + cnt; --i)
        {
            this->data[i - 1] = mystl::move(this->data[i - 1 - cnt]);
        }

        size_type i = 0;
        for (InputIt it = first; it != last; ++it, ++i)
        {
            this->data[idx + i] = *it;
        }

        this->sz += cnt;

        return iterator { this->data + idx };
    }

    iterator erase(const_iterator pos)
    {
        return this->erase(pos, pos + 1);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        const difference_type idx = first - const_iterator { this->data };
        if (first >= last)
        {
            return iterator { this->data + idx };
        }

        const difference_type diff = last - first;

        for (size_type i = idx; i < this->sz - diff; ++i)
        {
            this->data[i] = mystl::move(this->data[i + diff]);
        }

        this->sz -= diff;
        return iterator { this->data + idx };
    }

    void reserve(const size_type n)
    {
        if (n > this->sz)
        {
            T* new_data = new T[n];
            mystl::copy(this->data, this->data + this->sz, new_data);
            delete[] this->data;
            this->data = new_data;
            this->cap  = n;
        }
    }

private:
    size_type sz;
    size_type cap;

    T* data;
};

template<typename T>
inline bool operator==(const vector<T>& lhs, const vector<T>& rhs)
{
    return lhs.size() == rhs.size() && mystl::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T>
inline bool operator<(const vector<T>& lhs, const vector<T>& rhs)
{
    return mystl::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T>
inline bool operator!=(const vector<T>& lhs, const vector<T>& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
inline bool operator>(const vector<T>& lhs, const vector<T>& rhs)
{
    return rhs < lhs;
}

template<typename T>
inline bool operator<=(const vector<T>& lhs, const vector<T>& rhs)
{
    return !(rhs < lhs);
}

template<typename T>
inline bool operator>=(const vector<T>& lhs, const vector<T>& rhs)
{
    return !(lhs < rhs);
}
} // namespace mystl
