#pragma once

#include "bits/stl_tree.h"
#include "functional.h"
#include "types.h"
#include "utility.h"
#include <initializer_list>
#include <stdexcept>

namespace mystl
{
template<typename Key, typename T, typename Compare = mystl::less<Key>>
class map
{
public:
    using value_type      = mystl::pair<const Key, T>;
    using key_type        = Key;
    using mapped_type     = T;
    using key_compare     = Compare;
    using size_type       = mystl::size_t;
    using difference_type = mystl::ptrdiff_t;

private:
    struct KeyOfValue
    {
        const Key& operator()(const value_type& v) const
        {
            return v.first;
        }
    };

    using tree_type      = _rb_tree<Key, value_type, KeyOfValue, Compare>;
    using iterator       = typename tree_type::iterator;
    using const_iterator = typename tree_type::const_iterator;

    tree_type _tree;

public:
    map() = default;
    map(const std::initializer_list<value_type>& init)
    {
        for (const value_type& vt : init)
            _tree.insert(init);
    }

    map& operator=(std::initializer_list<value_type>& init)
    {
        for (const value_type& vt : init)
            _tree.insert(init);
    }

    T& operator[](const Key& key)
    {
        if (iterator it = _tree.find(key);
            it != _tree.end())
        {
            return it->val.second;
        }

        value_type val = { key, T {} };
        insert(val);

        return _tree.find(key)->val.second;
    }

    bool contains(const Key& key) const
    {
        return _tree.find(key) != _tree.end();
    }

    T& at(const Key& key)
    {
        iterator it = _tree.find(key);
        if (it == nullptr)
            throw std::out_of_range("key not found");
        return it->val.second;
    }

    const T& at(const Key& key) const
    {
        iterator it = _tree.find(key);
        if (it == nullptr)
            throw std::out_of_range("key not found");
        return it->val.second;
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

    mystl::size_t erase(const Key& key)
    {
        return _tree.erase(key);
    }

    mystl::size_t size() const
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