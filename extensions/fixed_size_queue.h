#include "mystl/deque.h"
#include <stdexcept>

namespace ext {
template<typename T, class Container = mystl::deque<T>>
class fixed_size_queue
{
    mystl::size_t cap;

    Container c;

public:
    fixed_size_queue(const mystl::size_t cap) :
        cap(cap)
    {
    }

    bool empty() const
    {
        return this->c.empty();
    }

    bool full() const
    {
        return this->c.size() == this->cap;
    }

    void push(const T& val)
    {
        if (this->full() == true)
        {
            throw std::overflow_error("push() called on full queue");
        }

        this->c.push_back(val);
    }

    T& front()
    {
        return this->c.front();
    }

    const T& front() const
    {
        return this->c.front();
    }

    void pop()
    {
        this->c.pop_front();
    }
};
}