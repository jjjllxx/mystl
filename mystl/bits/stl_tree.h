#pragma once

#include "mystl/iterator.h"
#include "mystl/types.h"
#include "mystl/utility.h"

namespace mystl
{
template<typename Key, typename Value, typename KeyOfValue, typename Compare>
class _rb_tree
{
    struct _rbt_node
    {
        bool  is_red;
        Value val;

        _rbt_node* parent;
        _rbt_node* left;
        _rbt_node* right;

        _rbt_node(const Value& val, _rbt_node* parent) :
            is_red(true),
            val(val),
            parent(parent),
            left(nullptr),
            right(nullptr)
        {
        }
    };

    _rbt_node* _root;
    _rbt_node* _header;

    mystl::size_t _size;
    KeyOfValue    _key_of_value;
    Compare       _comp;

public:
    class iterator
    {
        _rbt_node* _ptr;

    public:
        using iterator_category = bidirectional_iterator_tag;
        using value_type        = Value;
        using reference         = Value&;
        using pointer           = Value*;

        iterator(_rbt_node* p) :
            _ptr(p)
        {
        }

        reference operator*()
        {
            return _ptr->val;
        }

        pointer operator->()
        {
            return &_ptr->val;
        }

        iterator& operator++()
        {
            if (_ptr->right != nullptr)
            {
                _ptr = _ptr->right;
                while (_ptr->left != nullptr)
                    _ptr = _ptr->left;
            }
            else
            {
                _rbt_node* p = _ptr->parent;
                while (_ptr == p->right)
                {
                    _ptr = p;
                    p    = p->parent;
                }

                _ptr = p;
            }

            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--()
        {
            if (_ptr->left != nullptr)
            {
                _ptr = _ptr->left;
                while (_ptr->right != nullptr)
                    _ptr = _ptr->right;
            }
            else
            {
                _rbt_node* p = _ptr->parent;
                while (_ptr == p->left)
                {
                    _ptr = p;
                    p    = p->parent;
                }

                _ptr = p;
            }

            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const
        {
            return _ptr == other._ptr;
        }

        bool operator!=(const iterator& other) const
        {
            return _ptr != other._ptr;
        }

        friend _rb_tree;
    };

    class const_iterator
    {
        const _rbt_node* _ptr;

    public:
        using iterator_category = bidirectional_iterator_tag;
        using value_type        = Value;
        using reference         = const Value&;
        using pointer           = const Value*;

        const_iterator(const _rbt_node* p) :
            _ptr(p)
        {
        }

        reference operator*()
        {
            return _ptr->val;
        }

        pointer operator->()
        {
            return &_ptr->val;
        }

        const_iterator& operator++()
        {
            if (_ptr->right != nullptr)
            {
                _ptr = _ptr->right;
                while (_ptr->left != nullptr)
                    _ptr = _ptr->left;
            }
            else
            {
                _rbt_node* p = _ptr->parent;
                while (_ptr == p->right)
                {
                    _ptr = p;
                    p    = p->parent;
                }

                _ptr = p;
            }

            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const_iterator& operator--()
        {
            if (_ptr->left != nullptr)
            {
                _ptr = _ptr->left;
                while (_ptr->right != nullptr)
                    _ptr = _ptr->right;
            }
            else
            {
                _rbt_node* p = _ptr->parent;
                while (_ptr == p->left)
                {
                    _ptr = p;
                    p    = p->parent;
                }

                _ptr = p;
            }

            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const
        {
            return _ptr == other._ptr;
        }

        bool operator!=(const const_iterator& other) const
        {
            return _ptr != other._ptr;
        }

        friend _rb_tree;
    };

    _rb_tree() :
        _root(nullptr),
        _header(new _rbt_node{Value {}, nullptr}),
        _size(0),
        _key_of_value(KeyOfValue {}),
        _comp(Compare {})
    {
        _header->is_red = false;
        _header->left   = _header;
        _header->right  = _header;
    }

    ~_rb_tree()
    {
        clear();
        delete _header;
    }

    _rb_tree(const _rb_tree& other) :
        _header(new _rbt_node { Value {}, nullptr }),
        _root(nullptr),
        _size(0)
    {
        _header->parent = nullptr;
        _header->left   = _header;
        _header->right  = _header;
        _header->is_red = false;

        if (other._root != nullptr)
        {
            _root           = _copy_subtree(other._root, _header);
            _header->parent = _root;
            _header->left   = _minimum(_root);
            _header->right  = _maximum(_root);
            _size           = other._size;
        }
    }

    _rb_tree& operator=(const _rb_tree& other)
    {
        if (this != &other)
        {
            clear();
            if (other._root != nullptr)
            {
                _root           = _copy_subtree(other._root, _header);
                _header->parent = _root;
                _header->left   = _minimum(_root);
                _header->right  = _maximum(_root);
                _size           = other._size;
            }
        }

        return *this;
    }

    _rb_tree(_rb_tree&& other) noexcept :
        _root(nullptr),
        _size(0),
        _comp(mystl::move(other._comp)),
        _key_of_value(mystl::move(other._key_of_value))
    {
        _header = other._header;
        _root   = other._root;
        _size   = other._size;

        if (_root != nullptr)
        {
            _header->parent = _root;
            _header->left   = _minimum(_root);
            _header->right  = _maximum(_root);
        }
        else
        {
            _header->parent = nullptr;
            _header->left   = _header;
            _header->right  = _header;
        }

        other._header         = new _rbt_node { Value {}, nullptr };
        other._header->is_red = false;
        other._header->left   = other._header;
        other._header->right  = other._header;
        other._header->parent = nullptr;
        other._root           = nullptr;
        other._size           = 0;
    }

    _rb_tree& operator=(_rb_tree&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            _comp         = mystl::move(other._comp);
            _key_of_value = mystl::move(other._key_of_value);

            _header = other._header;
            _root   = other._root;
            _size   = other._size;

            if (other._root != nullptr)
            {
                _header->parent = _root;
                _header->left   = _minimum(_root);
                _header->right  = _maximum(_root);
            }
            else
            {
                _header->parent = nullptr;
                _header->left   = _header;
                _header->right  = _header;
            }

            other._header         = new _rbt_node { Value {}, nullptr };
            other._header->is_red = false;
            other._header->left   = other._header;
            other._header->right  = other._header;
            other._header->parent = nullptr;
            other._root           = nullptr;
            other._size           = 0;
        }

        return *this;
    }

    mystl::size_t size() const noexcept
    {
        return _size;
    }

    bool empty() const noexcept
    {
        return _size == 0;
    }

    mystl::pair<iterator, bool> insert(const Value& val)
    {
        _rbt_node* pa  = _header;
        _rbt_node* cur = _root;

        while (cur != nullptr)
        {
            pa = cur;
            if (_comp(_key_of_value(val), _key_of_value(cur->val)))
                cur = cur->left;
            else if (_comp(_key_of_value(cur->val), _key_of_value(val)))
                cur = cur->right;
            else
                return { iterator { cur }, false };
        }

        _rbt_node* new_node = new _rbt_node { val, pa };
        if (pa == _header)
            _root = new_node;
        else if (_comp(_key_of_value(val), _key_of_value(pa->val)))
            pa->left = new_node;
        else
            pa->right = new_node;

        _insert_fixup(new_node);
        _header->parent = _root;
        ++_size;

        if (_header->left == _header || _comp(_key_of_value(val), _key_of_value(_header->left->val)))
            _header->left = new_node;

        if (_header->right == _header || _comp(_key_of_value(_header->right->val), _key_of_value(val)))
            _header->right = new_node;

        return { iterator { new_node }, true };
    }

    mystl::size_t erase(const Key& key)
    {
        _rbt_node* z = find(key)._ptr;
        if (z == _header)
            return 0;

        _rbt_node* y        = z;
        _rbt_node* x        = nullptr;
        _rbt_node* x_pa     = nullptr;
        bool       is_y_red = y->is_red;

        if (z->left == nullptr)
        {
            x = z->right;
            _transplant(z, z->right);
            x_pa = z->parent;
        }
        else if (z->right == nullptr)
        {
            x = z->left;
            _transplant(z, z->left);
            x_pa = z->parent;
        }
        else
        {
            y        = _minimum(z->right);
            is_y_red = y->is_red;
            x        = y->right;

            if (y->parent == z)
            {
                if (x != nullptr)
                    x->parent = y;
                x_pa = y;
            }
            else
            {
                _transplant(y, y->right);
                y->right         = z->right;
                y->right->parent = y;
                x_pa             = y->parent;
            }

            _transplant(z, y);
            y->left         = z->left;
            y->left->parent = y;
            y->is_red       = z->is_red;
        }

        if (_header->left == z)
            _header->left = _root ? _minimum(_root) : _header;
        if (_header->right == z)
            _header->right = _root ? _maximum(_root) : _header;

        delete z;
        --_size;

        if (is_y_red == false)
            _erase_fixup(x, x_pa);

        return 1;
    }

    void clear()
    {
        _destroy(_root);
        _root = nullptr;
        _size = 0;

        _header->parent = nullptr;
        _header->left   = _header;
        _header->right  = _header;
    }

    iterator find(const Key& key)
    {
        _rbt_node* cur = _root;
        while (cur != nullptr)
            if (const Key& cur_key = _key_of_value(cur->val);
                _comp(key, cur_key))
                cur = cur->left;
            else if (_comp(cur_key, key))
                cur = cur->right;
            else
                return iterator { cur };

        return end();
    }

    const_iterator find(const Key& key) const
    {
        _rbt_node* cur = _root;
        while (cur != nullptr)
            if (const Key& cur_key = _key_of_value(cur->val);
                _comp(key, cur_key))
                cur = cur->left;
            else if (_comp(cur_key, key))
                cur = cur->right;
            else
                return const_iterator { cur };

        return end();
    }

    const_iterator lower_bound(const Key& key) const
    {
        _rbt_node* cur = _root;
        _rbt_node* res = nullptr;
        while (cur != nullptr)
            if (const Key& cur_key = _key_of_value(cur->val);
                _comp(key, cur_key))
            {
                if (res == nullptr || _comp(cur_key, _key_of_value(res->val)))
                    res = cur;
                cur = cur->left;
            }
            else if (_comp(cur_key, key))
                cur = cur->right;
            else
                return const_iterator { cur };

        return res == nullptr ? end() : const_iterator { res };
    }

    iterator lower_bound(const Key& key)
    {
        _rbt_node* cur = _root;
        _rbt_node* res = nullptr;
        while (cur != nullptr)
            if (const Key& cur_key = _key_of_value(cur->val);
                _comp(key, cur_key))
            {
                if (res == nullptr || _comp(cur_key, _key_of_value(res->val)))
                    res = cur;
                cur = cur->left;
            }
            else if (_comp(cur_key, key))
                cur = cur->right;
            else
                return iterator { cur };

        return res == nullptr ? end() : iterator { res };
    }

    const_iterator upper_bound(const Key& key) const
    {
        _rbt_node* cur = _root;
        _rbt_node* res = nullptr;
        while (cur != nullptr)
            if (const Key& cur_key = _key_of_value(cur->val);
                _comp(key, cur_key))
            {
                if (res == nullptr || _comp(cur_key, _key_of_value(res->val)))
                    res = cur;
                cur = cur->left;
            }
            else
                cur = cur->right;

        return res == nullptr ? end() : const_iterator { res };
    }

    iterator upper_bound(const Key& key)
    {
        _rbt_node* cur = _root;
        _rbt_node* res = nullptr;
        while (cur != nullptr)
            if (const Key& cur_key = _key_of_value(cur->val);
                _comp(key, cur_key))
            {
                if (res == nullptr || _comp(cur_key, _key_of_value(res->val)))
                    res = cur;
                cur = cur->left;
            }
            else
                cur = cur->right;

        return res == nullptr ? end() : iterator { res };
    }

    iterator begin()
    {
        return iterator { _header->left };
    }

    iterator end()
    {
        return iterator { _header };
    }

    const_iterator begin() const
    {
        return const_iterator { _header->left };
    }

    const_iterator end() const
    {
        return const_iterator { _header };
    }

private:
    void _transplant(_rbt_node* u, _rbt_node* v)
    {
        if (u->parent == _header)
            _root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v != nullptr)
            v->parent = u->parent;
    }

    _rbt_node* _minimum(_rbt_node* n)
    {
        while (n && n->left)
            n = n->left;
        return n;
    }

    _rbt_node* _maximum(_rbt_node* n)
    {
        while (n && n->right)
            n = n->right;
        return n;
    }

    void _left_rotate(_rbt_node* x)
    {
        _rbt_node* y = x->right;
        x->right     = y->left;
        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == _header)
        {
            _root           = y;
            _header->parent = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left   = x;
        x->parent = y;
    }

    void _right_rotate(_rbt_node* x)
    {
        _rbt_node* y = x->left;
        x->left      = y->right;
        if (y->right != nullptr)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == _header)
        {
            _root           = y;
            _header->parent = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->right  = x;
        x->parent = y;
    }

    void _insert_fixup(_rbt_node* x)
    {
        while (x != _root && x->parent->is_red)
        {
            _rbt_node* pa = x->parent;
            _rbt_node* gp = pa->parent;

            if (pa == gp->left)
            {
                _rbt_node* pb = gp->right;

                if (pb != nullptr && pb->is_red)
                {
                    pa->is_red = false;
                    pb->is_red = false;
                    gp->is_red = true;
                    x          = gp;
                }
                else
                {
                    if (x == pa->right)
                    {
                        x = pa;
                        _left_rotate(x);
                        pa = x->parent;
                    }

                    pa->is_red = false;
                    gp->is_red = true;
                    _right_rotate(gp);
                }
            }
            else
            {
                _rbt_node* pb = gp->left;

                if (pb != nullptr && pb->is_red)
                {
                    pa->is_red = false;
                    pb->is_red = false;
                    gp->is_red = true;
                    x          = gp;
                }
                else
                {
                    if (x == pa->left)
                    {
                        x = pa;
                        _right_rotate(x);
                        pa = x->parent;
                    }

                    pa->is_red = false;
                    gp->is_red = true;
                    _left_rotate(gp);
                }
            }
        }

        _root->is_red = false;
    }

    void _erase_fixup(_rbt_node* x, _rbt_node* x_pa)
    {
        while (x != _root && (!x || !x->is_red))
        {
            if (x == x_pa->left)
            {
                _rbt_node* w = x_pa->right;
                if (w && w->is_red == true)
                {
                    w->is_red    = false;
                    x_pa->is_red = true;
                    _left_rotate(x_pa);
                    w = x_pa->right;
                }
                if ((w->left == nullptr || w->left->is_red == false) && (w->right == nullptr || w->right->is_red == false))
                {
                    w->is_red = true;
                    x         = x_pa;
                    x_pa      = x->parent;
                }
                else
                {
                    if (w->right == nullptr || w->right->is_red == false)
                    {
                        if (w->left)
                            w->left->is_red = false;
                        w->is_red = true;
                        _right_rotate(w);
                        w = x_pa->right;
                    }
                    w->is_red    = x_pa->is_red;
                    x_pa->is_red = false;
                    if (w->right != nullptr)
                        w->right->is_red = false;
                    _left_rotate(x_pa);
                    x = _root;
                    break;
                }
            }
            else
            {
                _rbt_node* w = x_pa->left;
                if (w != nullptr && w->is_red == true)
                {
                    w->is_red    = false;
                    x_pa->is_red = true;
                    _right_rotate(x_pa);
                    w = x_pa->left;
                }
                if ((w->right == nullptr || w->right->is_red == false) && (w->left == nullptr || w->left->is_red == false))
                {
                    w->is_red = true;
                    x         = x_pa;
                    x_pa      = x->parent;
                }
                else
                {
                    if (w->left == nullptr || w->left->is_red == false)
                    {
                        if (w->right != nullptr)
                            w->right->is_red = false;
                        w->is_red = true;
                        _left_rotate(w);
                        w = x_pa->left;
                    }
                    w->is_red    = x_pa->is_red;
                    x_pa->is_red = false;
                    if (w->left)
                        w->left->is_red = false;
                    _right_rotate(x_pa);
                    x = _root;
                    break;
                }
            }
        }

        if (x != nullptr)
            x->is_red = false;
    }

    _rbt_node* _copy_subtree(_rbt_node* x,
                             _rbt_node* parent)
    {
        if (x == nullptr)
            return nullptr;

        _rbt_node* n = new _rbt_node(x->val, parent);
        n->is_red    = x->is_red;
        n->left      = _copy_subtree(x->left, n);
        n->right     = _copy_subtree(x->right, n);

        return n;
    }

    void _destroy(_rbt_node* x)
    {
        if (x != nullptr && x != _header)
        {
            _destroy(x->left);
            _destroy(x->right);
            delete x;
        }
    }
};
} // namespace mystl
