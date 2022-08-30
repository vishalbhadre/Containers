#include <iostream>
#include <memory>
#include <stack>

using namespace std;

#ifndef __MYFORWARDLIST__
#define __MYFORWARDLIST__

template<typename T>
class MyForwardList
{
    struct Node
    {
        T data;
        std::shared_ptr<Node> next;
        Node(T obj)
        {
            data = obj;
        }
    };
public: // functions
    MyForwardList();
    
    T& front();
    void push_front(T );
    void pop_front();
    void Reverse();
    
    bool empty();
    ~MyForwardList();

private: // members
    std::shared_ptr<Node> head_{nullptr};
};

template<typename T>
MyForwardList<T>::MyForwardList()
{
}

template<typename T>
T& MyForwardList<T>::front()
{
    if(nullptr != head_)
    {
        std::shared_ptr<Node> temp = head_;
        return temp.get()->data;
    }
}

template<typename T>
void MyForwardList<T>::push_front(T obj)
{
    std::shared_ptr<Node> temp = ::make_shared<Node>(obj);
    if(nullptr == head_)
        head_ = temp;
    else
    {
        temp->next = head_;
        head_ = temp;
    }
}

template<typename T>
void MyForwardList<T>::pop_front()
{
    std::shared_ptr<Node> temp = head_;
    if(nullptr != head_)
    head_ = head_->next;
}

template<typename T>
void MyForwardList<T>::Reverse()
{
    std::stack<std::shared_ptr<Node>> s;
    std::shared_ptr<Node> temp = head_;
    while(temp)
    {
        s.push(temp);
        temp = temp->next;
    }
    head_ = nullptr;
    std::shared_ptr<Node> curr = nullptr;
    while(!s.empty())
    {
        temp = s.top();
        s.pop();
        
        if(nullptr == head_)
        {
            head_ = temp;
            curr = head_;
        }    
        else
        {
            curr->next = temp;
            curr = curr->next;
        }
    }
}

template<typename T>
bool MyForwardList<T>::empty()
{
    return (nullptr == head_)? true: false;
}

template<typename T>
MyForwardList<T>::~MyForwardList()
{
    if(nullptr != head_)
    {
        head_ = nullptr;
    }
}

#endif // __MYFORWARDLIST__