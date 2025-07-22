#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace mystl
{
template<typename T>
struct list_node
{
    T val;

    mystl::list_node<T>* next;
};

template<typename T>
class list
{
    std::size_t sz;

    mystl::list_node<T>* head;
    mystl::list_node<T>* tail;

    mystl::list_node<T>* find_node(const std::size_t idx) const
    {
        {
            if (idx >= this->sz)
            {
                throw std::out_of_range("Index out of range in list::find_node()");
            }

            mystl::list_node<T>* node = this->head;

            for (std::size_t i = 0; i < idx; ++i)
            {
                node = node->next;
            }

            return node;
        }
    }

public:
    list() :
        sz(0),
        head(nullptr),
        tail(nullptr)
    {
    }

    list(const std::initializer_list<T>& items) :
        sz(items.size())
    {
        mystl::list_node<T>* pre = nullptr;
        for (std::size_t idx = 0; idx < items.size(); ++idx)
        {
            mystl::list_node<T>* node = new mystl::list_node<T>;
            node->val              = *(items.begin() + idx);
            node->next             = nullptr;

            if (idx == 0)
            {
                this->head = node;
            }
            else
            {
                pre->next = node;
            }

            pre = node;

            if (idx == items.size() - 1)
            {
                this->tail = node;
            }
        }
    }

    ~list()
    {
        mystl::list_node<T>* cur = this->head;
        mystl::list_node<T>* nxt = nullptr;
        while (cur != nullptr)
        {
            nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

    std::size_t size() const
    {
        return this->sz;
    }

    bool empty() const
    {
        return this->sz == 0;
    }

    const T& at(const std::size_t idx) const
    {
        return mystl::list<T>::find_node(idx)->val;
    }

    T& at(const std::size_t idx)
    {
        return mystl::list<T>::find_node(idx)->val;
    }

    const T& value_n_from_end(const std::size_t idx) const
    {
        if (idx >= this->sz)
        {
            throw std::out_of_range("Index out of range in list::value_n_from_end()");
        }

        return mystl::list<T>::at(this->sz - idx - 1);
    }

    void push_front(const T& val)
    {
        mystl::list_node<T>* newHead = new list_node<T>;
        newHead->val              = val;
        newHead->next             = this->head;
        this->head                = newHead;

        if (mystl::list<T>::empty() == true)
        {
            this->tail = this->head;
        }

        this->sz++;
    }

    T pop_front()
    {
        if (mystl::list<T>::empty() == true)
        {
            throw std::out_of_range("pop_front() called on empty linked list");
        }

        const T           front   = this->head->val;
        mystl::list_node<T>* preHead = this->head;
        this->head                = this->head->next;

        if (this->sz == 1)
        {
            this->tail = nullptr;
        }

        delete preHead;
        this->sz--;

        return front;
    }

    void push_back(const T& val)
    {
        if (mystl::list<T>::empty() == true)
        {
            mystl::list<T>::push_front(val);
        }
        else
        {
            mystl::list_node<T>* newTail = new list_node<T>;
            newTail->val              = val;
            newTail->next             = nullptr;

            this->tail->next = newTail;
            this->tail       = newTail;
            this->sz++;
        }
    }

    T pop_back()
    {
        if (mystl::list<T>::empty() == true)
        {
            throw std::out_of_range("pop_back() called on empty linked list");
        }

        if (this->sz == 1)
        {
            return mystl::list<T>::pop_front();
        }

        mystl::list_node<T>* node = mystl::list<T>::find_node(mystl::list<T>::size() - 2);

        node->next   = nullptr;
        const T back = this->head->val;
        delete this->tail;
        this->tail = node;
        this->sz--;

        return back;
    }

    const T& front() const
    {
        if (mystl::list<T>::empty() == true)
        {
            throw std::out_of_range("front() called on empty linked list");
        }

        return this->head->val;
    }

    const T& back() const
    {
        if (mystl::list<T>::empty() == true)
        {
            throw std::out_of_range("back() called on empty linked list");
        }

        return this->tail->val;
    }

    void insert(const std::size_t idx,
                const T&          val)
    {
        if (idx > this->sz)
        {
            throw std::out_of_range("Index out of range in list::insert()");
        }

        if (idx == 0)
        {
            return mystl::list<T>::push_front(val);
        }

        if (idx == this->sz)
        {
            return mystl::list<T>::push_back(val);
        }

        mystl::list_node<T>* preNode = mystl::list<T>::find_node(idx - 1);
        mystl::list_node<T>* newNode = new list_node<T>;
        newNode->val              = val;
        newNode->next             = preNode->next;
        preNode->next             = newNode;
        this->sz++;
    }

    void erase(const std::size_t idx)
    {
        if (idx >= this->sz)
        {
            throw std::out_of_range("Index out of range in list::erase()");
        }

        if (idx == 0)
        {
            mystl::list<T>::pop_front();
        }
        else if (idx == this->sz - 1)
        {
            mystl::list<T>::pop_back();
        }
        else
        {
            mystl::list_node<T>* preNode = mystl::list<T>::find_node(idx - 1);
            mystl::list_node<T>* curNode = preNode->next;
            preNode->next             = curNode->next;
            delete curNode;
            this->sz--;
        }
    }

    void remove(const T& val)
    {
        while (this->head != nullptr && this->head->val == val)
        {
            mystl::list<T>::pop_front();
        }

        if (mystl::list<T>::empty() == true)
        {
            return;
        }

        mystl::list_node<T>* pre = this->head;
        mystl::list_node<T>* cur = this->head->next;

        while (cur != nullptr)
        {
            if (cur->val == val)
            {
                pre->next = cur->next;
                delete cur;
                cur = pre->next;
                this->sz--;
            }
            else
            {
                pre = cur;
                cur = cur->next;
            }
        }

        this->tail = pre;
    }

    void reverse()
    {
        if (mystl::list<T>::empty() == false)
        {
            mystl::list_node<T>* pre = nullptr;
            mystl::list_node<T>* cur = this->head;
            mystl::list_node<T>* nxt = this->head->next;
            while (cur != nullptr)
            {
                nxt       = cur->next;
                cur->next = pre;
                pre       = cur;
                cur       = nxt;
            }

            this->tail = this->head;
            this->head = pre;
        }
    }
};
} // namespace mystl