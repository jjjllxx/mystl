#pragma once

#include "deque.h"

namespace mystl
{
template<typename T, class Container = mystl::deque<T>>
class queue
{
    Container c;

public:
    bool empty() const
    {
        return this->c.empty();
    }

    T& front()
    {
        return this->c.front();
    }

    const T& front() const
    {
        return this->c.front();
    }

    T& back()
    {
        return this->c.back();
    }

    const T& back() const
    {
        return this->c.back();
    }

    void push(const T& val)
    {
        this->c.push_back(val);
    }

    void pop()
    {
        this->c.pop_front();
    }

    mystl::size_t size() const
    {
        return this->c.size();
    }
};
} // namespace mystl
