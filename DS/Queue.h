#pragma once

#include "LinkedList.h"
#include <cstddef>

namespace dsa
{
template<typename T>
class Queue
{
    dsa::LinkedList<T> ll;

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

    dsa::LinkedList<T> ll;

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
        if (dsa::FixedSizeQueue<T>::full() == true)
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
} // namespace dsa