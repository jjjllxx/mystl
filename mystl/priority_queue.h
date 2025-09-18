#pragma once

#include "algorithm.h"
#include "functional.h"
#include "vector.h"

namespace mystl
{
template<typename T, class Container = mystl::vector<T>, typename Compare = mystl::less<T>>
class priority_queue
{
    Container c;
    Compare   comp;

public:
    priority_queue() = default;

    priority_queue(const priority_queue& other) :
        c(other.c)
    {
        mystl::make_heap(this->c.begin(), this->c.end(), this->comp);
    }

    priority_queue(priority_queue&& other) noexcept :
        c(mystl::move(other.c))
    {
        mystl::make_heap(this->c.begin(), this->c.end(), this->comp);
    }

    priority_queue(const Container& c) :
        c(c)
    {
        mystl::make_heap(this->c.begin(), this->c.end(), this->comp);
    }

    priority_queue(Container&& c) noexcept:
        c(mystl::move(c))
    {
        mystl::make_heap(this->c.begin(), this->c.end(), this->comp);
    }

    priority_queue& operator=(const priority_queue& other) noexcept
    {
        if (this != &other)
        {
            this->c = mystl::move(other.c);
            mystl::make_heap(this->c.begin(), this->c.end(), this->comp);
        }

        return *this;
    }

    priority_queue& operator=(priority_queue&& other) noexcept
    {
        if (this != &other)
        {
            this->c = mystl::move(other.c);
            mystl::make_heap(this->c.begin(), this->c.end(), this->comp);
        }

        return *this;
    }

    mystl::size_t size() const
    {
        return this->c.size();
    }

    bool empty() const
    {
        return this->c.empty();
    }

    T top() const
    {
        return this->c.front();
    }

    void push(const T& val)
    {
        this->c.push_back(val);
        mystl::push_heap(this->c.begin(), this->c.end(), this->comp);
    }

    void pop()
    {
        mystl::pop_heap(this->c.begin(), this->c.end(), this->comp);
        this->c.pop_back();
    }
};
} // namespace mystl