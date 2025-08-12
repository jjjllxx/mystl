#pragma once

#include "iterator.h"
#include <initializer_list>

namespace mystl
{
template<typename T>
class forward_list
{
    struct forward_list_node
    {
        T val;

        forward_list_node* next;

        forward_list_node(const T& val, forward_list_node* node) :
            val(val),
            next(node)
        {
        }
    };

    forward_list_node* dummy_head;

public:
    class iterator
    {
        forward_list_node* node;

    public:
        using value_type        = T;
        using difference_type   = mystl::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = mystl::forward_iterator_tag;

        iterator() :
            node(nullptr)
        {
        }

        explicit iterator(forward_list_node* n) :
            node(n)
        {
        }

        reference operator*() const
        {
            return node->val;
        }

        pointer operator->() const
        {
            return &(node->val);
        }

        iterator& operator++()
        {
            node = node->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const
        {
            return this->node == other.node;
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        friend forward_list;
    };

    class const_iterator
    {
        forward_list_node* node;

    public:
        using value_type        = T;
        using difference_type   = mystl::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = mystl::forward_iterator_tag;

        const_iterator() :
            node(nullptr)
        {
        }

        explicit const_iterator(forward_list_node* n) :
            node(n)
        {
        }

        reference operator*() const
        {
            return node->val;
        }

        pointer operator->() const
        {
            return &(node->val);
        }

        const_iterator& operator++()
        {
            node = node->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const
        {
            return this->node == other.node;
        }

        bool operator!=(const const_iterator& other) const
        {
            return !(*this == other);
        }

        friend forward_list;
    };

    forward_list() :
        dummy_head(new forward_list_node { T {}, nullptr })
    {
    }

    forward_list(const mystl::size_t n, const T& val) :
        dummy_head(new forward_list_node { T {}, nullptr })
    {
        forward_list_node* pre = this->dummy_head;
        for (mystl::size_t idx = 0; idx < n; ++idx)
        {
            forward_list_node* node = new forward_list_node { val, nullptr };
            pre->next               = node;
            pre                     = node;
        }
    }

    forward_list(const std::initializer_list<T>& items) :
        dummy_head(new forward_list_node { T {}, nullptr })
    {
        forward_list_node* pre = this->dummy_head;

        for (const T& val : items)
        {
            forward_list_node* node = new forward_list_node { val, nullptr };
            pre->next               = node;
            pre                     = node;
        }
    }

    ~forward_list()
    {
        forward_list_node* cur = this->dummy_head;
        forward_list_node* nxt = nullptr;
        while (cur != nullptr)
        {
            nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

    bool empty() const
    {
        return this->dummy_head->next == nullptr;
    }

    void push_front(const T& val)
    {
        forward_list_node* newHead = new forward_list_node { val, this->dummy_head->next };
        this->dummy_head->next     = newHead;
    }

    T pop_front()
    {
        const T            front   = this->dummy_head->next->val;
        forward_list_node* preHead = this->dummy_head->next;
        this->dummy_head->next     = preHead->next;

        delete preHead;

        return front;
    }

    const T& front() const
    {
        return this->dummy_head->next->val;
    }

    iterator begin() const
    {
        return iterator { this->dummy_head->next };
    }

    iterator end() const
    {
        return iterator { nullptr };
    }

    iterator before_begin() const
    {
        return iterator { this->dummy_head };
    }

    iterator insert_after(const iterator& pos, const T& val)
    {
        forward_list_node* node = new forward_list_node(val, pos.node->next);
        pos.node->next          = node;

        return iterator { node };
    }

    iterator erase_after(const iterator& pos)
    {
        forward_list_node* target = pos.node->next;
        pos.node->next            = pos.node->next->next;
        delete target;

        return iterator { pos.node->next };
    }

    mystl::size_t remove(const T& val)
    {
        mystl::size_t cnt = 0;

        forward_list_node* pre = this->dummy_head;
        forward_list_node* cur = this->dummy_head->next;

        while (cur != nullptr)
        {
            if (cur->val == val)
            {
                pre->next = cur->next;
                delete cur;
                cur = pre->next;
                ++cnt;
            }
            else
            {
                pre = cur;
                cur = cur->next;
            }
        }

        return cnt;
    }

    void reverse()
    {
        if (this->dummy_head->next != nullptr && this->dummy_head->next->next != nullptr)
        {
            forward_list_node* pre = nullptr;
            forward_list_node* cur = this->dummy_head->next;
            forward_list_node* nxt = this->dummy_head->next->next;
            while (cur != nullptr)
            {
                nxt       = cur->next;
                cur->next = pre;
                pre       = cur;
                cur       = nxt;
            }
            this->dummy_head->next = pre;
        }
    }

    void clear()
    {
        while (this->empty() == false)
        {
            this->pop_front();
        }
    }
};
} // namespace mystl