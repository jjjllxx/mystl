#pragma once

#include "bits/stl_algobase.h"
#include "mystl/types.h"
#include <cstddef>
#include <cstring>

namespace mystl
{
const mystl::size_t STRING_INITIAL_CAPACITY = 15;

class string
{
    mystl::size_t sz;
    mystl::size_t cap;

    char* data;

public:
    static const mystl::size_t npos = -1;

    string() :
        sz(0),
        cap(mystl::STRING_INITIAL_CAPACITY),
        data(new char[mystl::STRING_INITIAL_CAPACITY + 1])
    {
    }

    string(const char* s) :
        sz(strlen(s)),
        cap(mystl::max(this->sz, mystl::STRING_INITIAL_CAPACITY)),
        data(new char[this->cap + 1])
    {
        mystl::copy(s, s + this->sz + 1, this->data);
    }

    string(const string& other)
    {
        this->sz   = other.size();
        this->data = new char[this->sz + 1];
        mystl::copy(other.data, other.data + this->sz + 1, data);
    }

    string& operator=(const string& other)
    {
        if (this != &other)
        {
            delete[] this->data;
            this->sz   = other.sz;
            this->data = new char[this->sz + 1];
            mystl::copy(other.data, other.data + this->sz + 1, this->data);
        }

        return *this;
    }

    string(string&& other) noexcept :
        sz(other.sz),
        cap(other.cap),
        data(other.data)
    {
        other.sz   = 0;
        other.cap  = 0;
        other.data = nullptr;
    }

    string& operator=(string&& other) noexcept
    {
        if (this != &other)
        {
            delete[] this->data;
            this->sz  = other.sz;
            this->cap = other.cap;

            this->data = other.data;
            other.sz   = 0;
            other.cap  = 0;
            other.data = nullptr;
        }

        return *this;
    }

    ~string()
    {
        delete[] this->data;
    }

    const char* begin() const
    {
        return this->data;
    }

    const char* end() const
    {
        return this->data + this->sz;
    }

    char* begin()
    {
        return this->data;
    }

    char* end()
    {
        return this->data + this->sz;
    }

    mystl::size_t size() const
    {
        return this->sz;
    }

    mystl::size_t capacity() const
    {
        return this->cap;
    }

    bool empty() const
    {
        return this->sz == 0;
    }

    void push_back(const char c)
    {
        if (this->sz == this->cap)
        {
            string::reserve(this->cap == 0 ? 1 : this->cap << 1);
        }

        *(this->data + this->sz++) = c;
        *(this->data + this->sz)   = '\0';
    }

    char pop_back()
    {
        const char back          = *(this->data + --this->sz);
        *(this->data + this->sz) = '\0';
        return back;
    }

    void reserve(const mystl::size_t newCap)
    {
        if (newCap > this->sz)
        {
            char* newData = new char[newCap + 1];
            mystl::copy(this->data, this->data + this->sz + 1, newData);
            delete[] this->data;
            this->data = newData;
            this->cap  = newCap;
        }
    }

    char& front()
    {
        return *this->data;
    }

    const char& front() const
    {
        return *this->data;
    }

    char& back()
    {
        return *(this->data + this->sz - 1);
    }

    const char& back() const
    {
        return *(this->data + this->sz - 1);
    }

    const char& operator[](const mystl::size_t idx) const
    {
        return *(this->data + idx);
    }

    char& operator[](const mystl::size_t idx)
    {
        return *(this->data + idx);
    }

    bool operator==(const mystl::string& other) const
    {
        if (other.sz != this->sz)
            return false;

        for (mystl::size_t idx = 0; idx < this->sz; ++idx)
            if (this->data[idx] != other[idx])
                return false;

        return true;
    }

    bool operator<(const mystl::string& other) const
    {
        for (mystl::size_t i = 0; i < mystl::min(this->sz, other.sz); ++i)
            if (this->data[i] < other[i])
                return true;
            else if (this->data[i] > other[i])
                return false;

        return this->sz < other.sz;
    }

    bool operator>(const mystl::string& other) const
    {
        return other < *this;
    }

    bool operator!=(const mystl::string& other) const
    {
        return !(*this == other);
    }

    bool operator<=(const mystl::string& other) const
    {
        return !(other < *this);
    }

    bool operator>=(const mystl::string& other) const
    {
        return !(*this < other);
    }
};

inline int stoi(const mystl::string& str)
{
    bool is_neg = str[0] == '-';
    int  res    = 0;
    for (std::size_t idx = is_neg ? 1 : 0; idx < str.size(); ++idx)
    {
        res *= 10;
        res += str[idx] - '0';
    }
    return is_neg ? -res : res;
}
} // namespace mystl