#pragma once

#include "iterator.h"
#include "utility.h"

#include <initializer_list>

namespace mystl
{
template<typename T>
class list
{
    struct list_node
    {
        T val;

        list_node* prev;
        list_node* next;

        list_node(const T&   v,
                  list_node* p,
                  list_node* n) :
            val(v),
            prev(p),
            next(n)
        {
        }
    };

public:
    class iterator
    {
        list_node* node;

    public:
        using value_type        = T;
        using difference_type   = mystl::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = mystl::bidirectional_iterator_tag;

        iterator() :
            node(nullptr)
        {
        }

        explicit iterator(list_node* n) :
            node(n)
        {
        }

        reference operator*() const
        {
            return this->node->val;
        }

        pointer operator->() const
        {
            return &(this->node->val);
        }

        iterator& operator++()
        {
            this->node = this->node->next;
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
            this->node = this->node->prev;
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
            return this->node == other.node;
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        friend class list;
    };

    class const_iterator
    {
        list_node* node;

    public:
        using value_type        = T;
        using difference_type   = mystl::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = mystl::bidirectional_iterator_tag;

        const_iterator() :
            node(nullptr)
        {
        }

        explicit const_iterator(list_node* n) :
            node(n)
        {
        }

        reference operator*() const
        {
            return this->node->val;
        }

        pointer operator->() const
        {
            return &(this->node->val);
        }

        const_iterator& operator++()
        {
            this->node = this->node->next;
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
            this->node = this->node->prev;
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
            return this->node == other.node;
        }

        bool operator!=(const const_iterator& other) const
        {
            return !(*this == other);
        }

        friend class list;
    };

private:
    mystl::size_t sz;

    list_node* dummy;

public:
    list() :
        sz(0),
        dummy(new list_node { T {}, nullptr, nullptr })
    {
        this->dummy->next = this->dummy;
        this->dummy->prev = this->dummy;
    }

    list(const mystl::size_t n, const T& val) :
        sz(n),
        dummy(new list_node { T {}, nullptr, nullptr })
    {
        list_node* pre = this->dummy;
        for (mystl::size_t idx = 0; idx < n; ++idx)
        {
            list_node* node = new list_node { val, pre, nullptr };
            pre->next       = node;
            pre             = node;
        }
        pre->next         = this->dummy;
        this->dummy->prev = pre;
    }

    list(const std::initializer_list<T>& items) :
        sz(items.size()),
        dummy(new list_node { T {}, nullptr, nullptr })
    {
        list_node* pre = this->dummy;
        for (const T& val : items)
        {
            list_node* node = new list_node { val, pre, nullptr };
            pre->next       = node;
            pre             = node;
        }
        pre->next         = this->dummy;
        this->dummy->prev = pre;
    }

    ~list()
    {
        list_node* cur = this->dummy->next;
        list_node* nxt = nullptr;
        while (cur != this->dummy)
        {
            nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        delete this->dummy;
    }

    mystl::size_t size() const
    {
        return this->sz;
    }

    bool empty() const
    {
        return this->sz == 0;
    }
    
    T& front()
    {
        return this->dummy->next->val;
    }

    const T& front() const
    {
        return this->dummy->next->val;
    }

    T& back()
    {
        return this->dummy->prev->val;
    }

    const T& back() const
    {
        return this->dummy->prev->val;
    }

    void push_front(const T& val)
    {
        list_node* newHead  = new list_node { val, this->dummy, dummy->next };
        this->dummy->next   = newHead;
        newHead->next->prev = newHead;
        this->sz++;
    }

    T pop_front()
    {
        const T    front = this->dummy->next->val;
        list_node* head  = this->dummy->next;
        dummy->next      = head->next;
        head->next->prev = dummy;

        delete head;
        this->sz--;

        return front;
    }

    void push_back(const T& val)
    {
        list_node* newTail  = new list_node { val, this->dummy->prev, this->dummy };
        this->dummy->prev   = newTail;
        newTail->prev->next = newTail;
        this->sz++;
    }

    T pop_back()
    {
        const T    back  = this->dummy->prev->val;
        list_node* tail  = this->dummy->prev;
        dummy->prev      = tail->prev;
        tail->prev->next = dummy;

        delete tail;
        this->sz--;

        return back;
    }

    iterator begin() 
    {
        return iterator { this->dummy->next };
    }

    iterator end() 
    {
        return iterator { this->dummy };
    }

    const_iterator begin() const
    {
        return const_iterator { this->dummy->next };
    }

    const_iterator end() const
    {
        return const_iterator { this->dummy };
    }

    iterator insert(const iterator& pos, const T& val)
    {
        list_node* node  = new list_node(val, pos.node->prev, pos.node);
        node->prev->next = node;
        node->next->prev = node;
        ++this->sz;
        return iterator { node };
    }

    iterator erase(const iterator& pos)
    {
        if (pos.node == this->dummy)
        {
            return iterator { dummy };
        }

        list_node* target  = pos.node;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        const iterator it { target->next };

        delete target;
        --this->sz;

        return it;
    }

    mystl::size_t remove(const T& val)
    {
        mystl::size_t cnt = 0;
        list_node*  cur = this->dummy->next;

        while (cur != dummy)
        {
            if (cur->val == val)
            {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                list_node* nxt  = cur->next;
                delete cur;
                ++cnt;
                cur = nxt;
            }
            else
            {
                cur = cur->next;
            }
        }

        this->sz -= cnt;

        return cnt;
    }

    void clear()
    {
        while (this->empty() == false)
        {
            this->pop_front();
        }
    }

    void reverse()
    {
        list_node* node = this->dummy->next;
        while (node != this->dummy)
        {
            mystl::swap(node->prev, node->next);
            node = node->prev;
        }

        mystl::swap(this->dummy->next, this->dummy->prev);
    }
};
} // namespace mystl