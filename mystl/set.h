#pragma once

#include "bits/stl_tree.h"
#include "functional.h"
#include "types.h"
#include "utility.h"
#include <initializer_list>

namespace mystl
{
template<typename Key, typename Compare = mystl::less<Key>>
class set
{
public:
    using value_type      = Key;
    using key_type        = Key;
    using key_compare     = Compare;
    using value_compare   = Compare;
    using size_type       = mystl::size_t;
    using difference_type = mystl::ptrdiff_t;

private:
    struct KeyOfValue
    {
        const Key& operator()(const value_type& v) const
        {
            return v;
        }
    };

    using tree_type      = _rb_tree<Key, value_type, KeyOfValue, Compare>;
    using iterator       = typename tree_type::iterator;
    using const_iterator = typename tree_type::const_iterator;

    tree_type _tree;

public:
    set() = default;
    set(const std::initializer_list<Key>& init)
    {
        for(const Key& k : init)
            insert(k);
    }

    set& operator=(const std::initializer_list<Key>& init)
    {
        for (const Key& k : init)
            insert(k);
    }

    bool contains(const Key& key) const
    {
        return _tree.find(key) != _tree.end();
    }

    const_iterator begin() const
    {
        return _tree.begin();
    }

    const_iterator end() const
    {
        return _tree.end();
    }

    iterator begin()
    {
        return _tree.begin();
    }

    iterator end()
    {
        return _tree.end();
    }

    iterator find(const Key& key)
    {
        return _tree.find(key);
    }

    const_iterator find(const Key& key) const
    {
        return _tree.find(key);
    }

    iterator upper_bound(const Key& key)
    {
        return _tree.upper_bound(key);
    }

    const_iterator upper_bound(const Key& key) const
    {
        return _tree.upper_bound(key);
    }

    iterator lower_bound(const Key& key)
    {
        return _tree.lower_bound(key);
    }

    const_iterator lower_bound(const Key& key) const
    {
        return _tree.lower_bound(key);
    }

    mystl::pair<iterator, bool> insert(const value_type& val)
    {
        return _tree.insert(val);
    }

    size_type erase(const Key& key)
    {
        return _tree.erase(key);
    }

    size_type size() const
    {
        return _tree.size();
    }

    bool empty() const
    {
        return _tree.empty();
    }

    void clear()
    {
        _tree.clear();
    }
};
} // namespace mystl