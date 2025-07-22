#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace mystl
{
template<typename T, std::size_t N>
class array
{
    T* data;

public:
    array()
    {
        this->data = new T[N]();
    }

    array(const std::initializer_list<T>& list)
    {
        if (list.size() > N)
        {
            throw std::overflow_error("too many initializers for mystl::array");
        }

        this->data      = new T[N]();
        std::size_t idx = 0;
        for (const T& val : list)
        {
            *(this->data + idx++) = val;
        }

        while (idx < N)
        {
            *(this->data + idx++) = T{};
        }
    }

    array(const mystl::array<T, N>& other)
    {
        this->data = new T[N];

        std::copy(other.data, other.data + N, this->data);
    }

    array<T, N>& operator=(const mystl::array<T, N>& other)
    {
        if (this != &other)
        {
            T* newData = new T[N];
            std::copy(other.data, other.data + N, newData);
            delete[] this->data;
            this->data = newData;
        }

        return *this;
    }

    array(mystl::array<T, N>&& other) noexcept
    {
        this->data = other.data;
        other.data = nullptr;
    }

    array<T, N>& operator=(mystl::array<T, N>&& other) noexcept
    {
        if (this != &other)
        {
            delete[] this->data;
            this->data = other.data;
            other.data = nullptr;
        }

        return *this;
    }

    ~array()
    {
        delete[] this->data;
    }

    std::size_t size() const
    {
        return N;
    }

    bool empty() const
    {
        return N == 0;
    }

    const T& operator[](const std::size_t idx) const
    {
        return *(this->data + idx);
    }

    T& operator[](const std::size_t idx)
    {
        return *(this->data + idx);
    }

    const T& at(const std::size_t idx) const
    {
        if (idx >= N)
        {
            throw std::out_of_range("Index out of range in array::at()");
        }

        return *(this->data + idx);
    }

    T& at(const std::size_t idx)
    {
        if (idx >= N)
        {
            throw std::out_of_range("Index out of range in array::at()");
        }

        return *(this->data + idx);
    }

    const T* begin() const
    {
        return this->data;
    }

    const T* end() const
    {
        return this->data + N;
    }

    T* begin()
    {
        return this->data;
    }

    T* end()
    {
        return this->data + N;
    }

    const T& front() const
    {
        return *this->data;
    }

    const T& back() const
    {
        return *(this->data + N - 1);
    }

    void fill(const T& val)
    {
        for (std::size_t idx = 0; idx < N; ++idx)
        {
            *(this->data + idx) = val;
        }
    }
};
} // namespace mystl