#pragma once

#include "mystl/numeric.h"
#include "mystl/vector.h"

namespace ext
{
class union_find
{
    mystl::vector<mystl::size_t> parents;

public:
    explicit union_find(const mystl::size_t n) :
        parents(n)
    {
        mystl::iota(this->parents.begin(), this->parents.end(), 0);
    }

    int find(const mystl::size_t x)
    {
        if (this->parents[x] == x)
        {
            return x;
        }

        return this->parents[x] = this->find(this->parents[x]);
    }

    void unite(const mystl::size_t x,
               const mystl::size_t y)
    {
        this->parents[this->find(x)] = this->find(y);
    }
};
} // namespace ext
