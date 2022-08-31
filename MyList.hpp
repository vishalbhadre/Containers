#include <iostream>
#include <memory>
#include <stack>

using namespace std;

#ifndef __MYLIST__
#define __MYLIST__

template<typename T>
class MyList
{
    struct Node
    {
        T data;
        std::shared_ptr<Node> next{nullptr}, prev{nullptr};
        Node(T obj)
        {
            data = obj;
        }
    };
public: // functions
    MyList();
    
    T& front();
    T& back();

    void push_front(T );
    void pop_front();
    void push_back(T );
    void pop_back();
    
    bool empty();
    ~MyList();

private: // members
    std::shared_ptr<Node> head_{nullptr}, tail_{nullptr};
};

template<typename T>
MyList<T>::MyList()
{
}

template<typename T>
T& MyList<T>::front()
{
    if(nullptr != head_)
    {
        std::shared_ptr<Node> temp = head_;
        return temp.get()->data;
    }
}

template<typename T>
T& MyList<T>::back()
{
    if(nullptr != tail_)
    {
        std::shared_ptr<Node> temp = tail_;
        return temp.get()->data;
    }
}

template<typename T>
void MyList<T>::push_front(T obj)
{
    std::shared_ptr<Node> temp = ::make_shared<Node>(obj);
    if(nullptr == head_)
    {
        head_ = temp;
        tail_ = head_;
    }    
    else
    {
        temp->next = head_;
        head_->prev = temp;
        head_ = temp;
    }
}

template<typename T>
void MyList<T>::pop_front()
{
    std::shared_ptr<Node> temp = head_;
    if(nullptr != head_)
    {
        head_ = head_->next;

        temp->prev = temp->next = nullptr;

        if(nullptr != head_)
            head_->prev = nullptr;
        else
            tail_ = nullptr;
    }
}

template<typename T>
void MyList<T>::push_back(T obj)
{
    std::shared_ptr<Node> temp = ::make_shared<Node>(obj);
    if(nullptr == tail_)
    {
        head_ = temp;
        tail_ = temp;
    }    
    else
    {
        tail_->next = temp;
        temp->prev = tail_;
        tail_ = temp;
    }
}

template<typename T>
void MyList<T>::pop_back()
{
    std::shared_ptr<Node> temp = tail_;
    if(nullptr != tail_)
    {
        tail_ = tail_->prev;
        temp->prev = temp->next = nullptr;
        if(nullptr != tail_)
            tail_->next = nullptr;
        else
            head_ = nullptr;
    }
}

template<typename T>
bool MyList<T>::empty()
{
    return (nullptr == head_)? true: false;
}

template<typename T>
MyList<T>::~MyList()
{
    if(nullptr != head_)
        head_ = nullptr;
    if(nullptr != tail_)
        tail_ = nullptr;    
}

#endif // __MYLIST__