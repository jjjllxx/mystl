#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <stdexcept>

namespace dsa
{
const std::size_t VECTOR_INITIAL_CAPACITY = 16;

template<typename T>
class Vector
{
    std::size_t sz;
    std::size_t cap;

    T* data;

    void resize(const std::size_t new_cap)
    {
        T* new_data = new T[new_cap];
        std::copy(this->data, this->data + this->sz, new_data);
        delete[] this->data;
        this->data = new_data;
        this->cap  = new_cap;
    }

public:
    Vector() :
        sz(0),
        cap(dsa::VECTOR_INITIAL_CAPACITY),
        data(new T[dsa::VECTOR_INITIAL_CAPACITY])
    {
    }

    Vector(const std::size_t n) :
        sz(n),
        cap(n),
        data(new T[n])
    {
        for (std::size_t i = 0; i < this->sz; ++i)
        {
            *(this->data + i) = 0;
        }
    }

    Vector(const std::size_t n,
           const T&          item) :
        sz(n),
        cap(n),
        data(new T[n])
    {
        for (std::size_t i = 0; i < this->sz; ++i)
        {
            *(this->data + i) = item;
        }
    }

    Vector(const std::initializer_list<T>& init_list) :
        sz(init_list.size()),
        cap(init_list.size()),
        data(new T[init_list.size()])
    {
        std::size_t i = 0;
        for (const T& val : init_list)
        {
            *(this->data + i++) = val;
        }
    }

    ~Vector()
    {
        delete[] this->data;
    }

    std::size_t size() const
    {
        return this->sz;
    }

    std::size_t capacity() const
    {
        return this->cap;
    }

    bool empty() const
    {
        return this->sz == 0;
    }

    T& operator[](const std::size_t idx)
    {
        return *(this->data + idx);
    }

    const T& operator[](const std::size_t idx) const
    {
        return *(this->data + idx);
    }

    const T* begin() const
    {
        return this->data;
    }

    const T* end() const
    {
        return this->data + this->sz;
    }

    T* begin()
    {
        return this->data;
    }

    T* end()
    {
        return this->data + this->sz;
    }

    T& at(const std::size_t idx)
    {
        if (idx >= this->sz)
        {
            throw std::out_of_range("Index out of range in Vector::at()");
        }

        return *(this->data + idx);
    }

    const T& at(const std::size_t idx) const
    {
        if (idx >= this->sz)
        {
            throw std::out_of_range("Index out of range in Vector::at()");
        }

        return *(this->data + idx);
    }

    T find(const T& item) const
    {
        for (std::size_t i = 0; i < this->sz; ++i)
        {
            if (*(this->data + i) == item)
            {
                return i;
            }
        }

        return -1;
    }

    void push(const T& item)
    {
        if (this->sz == this->cap)
        {
            dsa::Vector<T>::resize(this->cap << 1);
        }

        *(this->data + this->sz++) = item;
    }

    void insert(const std::size_t idx,
                const T&          item)
    {
        if (idx > this->sz)
        {
            throw std::out_of_range("Index out of range in Vector::insert()");
        }

        if (this->sz == this->cap)
        {
            dsa::Vector<T>::resize(this->cap << 1);
        }

        T pre = *(this->data + idx);
        T cur = item;

        for (std::size_t i = idx; i <= this->sz; ++i)
        {
            pre               = *(this->data + i);
            *(this->data + i) = cur;
            cur               = pre;
        }

        this->sz++;
    }

    void prepend(const T& item)
    {
        dsa::Vector<T>::insert(0, item);
    }

    T pop()
    {
        if (dsa::Vector<T>::empty() == true)
        {
            throw std::out_of_range("pop() called on an empty vector");
        }

        const T last = *(this->data + --this->sz);

        if ((this->sz << 2) < this->cap)
        {
            dsa::Vector<T>::resize(this->cap >> 1);
        }

        return last;
    }

    void erase(const std::size_t idx)
    {
        if (idx >= this->sz)
        {
            throw std::out_of_range("Index out of range in Vector::erase()");
        }

        for (std::size_t i = idx; i < this->sz - 1; ++i)
        {
            *(this->data + i) = *(this->data + i + 1);
        }

        this->sz--;
    }

    void remove(const T& item)
    {
        std::size_t cur = 0;

        for (std::size_t i = 0; i < this->sz; ++i)
        {
            if (*(this->data + i) != item)
            {
                *(this->data + cur) = *(this->data + i);
                cur++;
            }
        }
        this->sz = cur;
    }
};
} // namespace dsa