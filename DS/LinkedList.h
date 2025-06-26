#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace dsa
{
template<typename T>
struct ListNode
{
    T val;

    dsa::ListNode<T>* next;
};

template<typename T>
class LinkedList
{
    std::size_t sz;

    dsa::ListNode<T>* head;
    dsa::ListNode<T>* tail;

    dsa::ListNode<T>* find_node(const std::size_t idx) const
    {
        {
            if (idx >= this->sz)
            {
                throw std::out_of_range("Index out of range in LinkedList::find_node()");
            }

            dsa::ListNode<T>* node = this->head;

            for (std::size_t i = 0; i < idx; ++i)
            {
                node = node->next;
            }

            return node;
        }
    }

public:
    LinkedList() :
        sz(0),
        head(nullptr),
        tail(nullptr)
    {
    }

    LinkedList(const std::initializer_list<T>& items) :
        sz(items.size())
    {
        dsa::ListNode<T>* pre = nullptr;
        for (std::size_t idx = 0; idx < items.size(); ++idx)
        {
            dsa::ListNode<T>* node = new dsa::ListNode<T>;
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

    ~LinkedList()
    {
        dsa::ListNode<T>* cur = this->head;
        dsa::ListNode<T>* nxt = nullptr;
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
        return dsa::LinkedList<T>::find_node(idx)->val;
    }

    T& at(const std::size_t idx)
    {
        return dsa::LinkedList<T>::find_node(idx)->val;
    }

    const T& value_n_from_end(const std::size_t idx) const
    {
        if (idx >= this->sz)
        {
            throw std::out_of_range("Index out of range in LinkedList::value_n_from_end()");
        }

        return dsa::LinkedList<T>::at(this->sz - idx - 1);
    }

    void push_front(const T& val)
    {
        dsa::ListNode<T>* newHead = new ListNode<T>;
        newHead->val              = val;
        newHead->next             = this->head;
        this->head                = newHead;

        if (dsa::LinkedList<T>::empty() == true)
        {
            this->tail = this->head;
        }

        this->sz++;
    }

    T pop_front()
    {
        if (dsa::LinkedList<T>::empty() == true)
        {
            throw std::out_of_range("pop_front() called on empty linked list");
        }

        const T           front   = this->head->val;
        dsa::ListNode<T>* preHead = this->head;
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
        if (dsa::LinkedList<T>::empty() == true)
        {
            dsa::LinkedList<T>::push_front(val);
        }
        else
        {
            dsa::ListNode<T>* newTail = new ListNode<T>;
            newTail->val              = val;
            newTail->next             = nullptr;

            this->tail->next = newTail;
            this->tail       = newTail;
            this->sz++;
        }
    }

    T pop_back()
    {
        if (dsa::LinkedList<T>::empty() == true)
        {
            throw std::out_of_range("pop_back() called on empty linked list");
        }

        if (this->sz == 1)
        {
            return dsa::LinkedList<T>::pop_front();
        }

        dsa::ListNode<T>* node = dsa::LinkedList<T>::find_node(dsa::LinkedList<T>::size() - 2);

        node->next   = nullptr;
        const T back = this->head->val;
        delete this->tail;
        this->tail = node;
        this->sz--;

        return back;
    }

    const T& front() const
    {
        if (dsa::LinkedList<T>::empty() == true)
        {
            throw std::out_of_range("front() called on empty linked list");
        }

        return this->head->val;
    }

    const T& back() const
    {
        if (dsa::LinkedList<T>::empty() == true)
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
            throw std::out_of_range("Index out of range in LinkedList::insert()");
        }

        if (idx == 0)
        {
            return dsa::LinkedList<T>::push_front(val);
        }

        if (idx == this->sz)
        {
            return dsa::LinkedList<T>::push_back(val);
        }

        dsa::ListNode<T>* preNode = dsa::LinkedList<T>::find_node(idx - 1);
        dsa::ListNode<T>* newNode = new ListNode<T>;
        newNode->val              = val;
        newNode->next             = preNode->next;
        preNode->next             = newNode;
        this->sz++;
    }

    void erase(const std::size_t idx)
    {
        if (idx >= this->sz)
        {
            throw std::out_of_range("Index out of range in LinkedList::erase()");
        }

        if (idx == 0)
        {
            dsa::LinkedList<T>::pop_front();
        }
        else if (idx == this->sz - 1)
        {
            dsa::LinkedList<T>::pop_back();
        }
        else
        {
            dsa::ListNode<T>* preNode = dsa::LinkedList<T>::find_node(idx - 1);
            dsa::ListNode<T>* curNode = preNode->next;
            preNode->next             = curNode->next;
            delete curNode;
            this->sz--;
        }
    }

    void remove(const T& val)
    {
        while (this->head != nullptr && this->head->val == val)
        {
            dsa::LinkedList<T>::pop_front();
        }

        if (dsa::LinkedList<T>::empty() == true)
        {
            return;
        }

        dsa::ListNode<T>* pre = this->head;
        dsa::ListNode<T>* cur = this->head->next;

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
        if (dsa::LinkedList<T>::empty() == false)
        {
            dsa::ListNode<T>* pre = nullptr;
            dsa::ListNode<T>* cur = this->head;
            dsa::ListNode<T>* nxt = this->head->next;
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
} // namespace dsa