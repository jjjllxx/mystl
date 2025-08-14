#pragma once

#include "utility.h"
#include "deque.h"

namespace mystl
{
template<typename T, typename Container = mystl::deque<T>>
class stack
{
    Container c;

public:
    stack() = default;

    explicit stack(const Container& c) :
        c(c)
    {
    }

    explicit stack(Container&& c) noexcept :
        c(mystl::move(c))
    {
    }

    stack(const stack& other) :
        c(other.c)
    {
    }

    stack(stack&& other) :
        c(mystl::move(other.c))
    {
    }

    stack& operator=(const stack& other)
    {
        this->c = other.c;

        return *this;
    }

    stack& operator=(stack&& other) noexcept
    {
        if (this != &other)
        {
            this->c = mystl::move(other.c);
        }

        return *this;
    }

    void push(const T& value)
    {
        this->c.push_back(value);
    }

    void pop()
    {
        this->c.pop_back();
    }

    T& top()
    {
        return this->c.back();
    }

    const T& top() const
    {
        return this->c.back();
    }

    bool empty() const
    {
        return this->c.empty();
    }

    mystl::size_t size() const
    {
        return this->c.size();
    }
};
} // namespace mystl
