#pragma once

#include "list.h"
#include <cstddef>

namespace mystl
{
template<typename T>
class queue
{
    mystl::list<T> ll;

public:
    bool empty() const
    {
        return this->ll.empty();
    }

    void enqueue(const T& val)
    {
        this->ll.push_back(val);
    }

    T dequeue()
    {
        return this->ll.pop_front();
    }

    std::size_t size() const
    {
        return this->ll.size();
    }
};

template<typename T>
class FixedSizeQueue
{
    std::size_t cap;

    mystl::list<T> ll;

public:
    FixedSizeQueue(const std::size_t cap) :
        cap(cap)
    {
    }

    bool empty() const
    {
        return this->ll.empty();
    }

    bool full() const
    {
        return this->ll.size() == this->cap;
    }

    void enqueue(const T& val)
    {
        if (mystl::FixedSizeQueue<T>::full() == true)
        {
            throw std::overflow_error("enqueue() called on full queue");
        }

        this->ll.push_back(val);
    }
    
    T dequeue()
    {
        return this->ll.pop_front();
    }
};
} // namespace mystl