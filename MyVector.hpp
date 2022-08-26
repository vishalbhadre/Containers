#include <iostream>

using namespace std;

#ifndef __MYVECTOR__
#define __MYVECTOR__

template<typename T>
class MyVector
{
public: // functions
    MyVector();
    void Reserve(uint32_t size);
    template<typename...Args>
    void emplace_back(Args&&...args);

    void push_back(T );
    void pop_back();
    void shrink_to_fit();
    T& operator[](uint32_t index);
    bool empty();
    ~MyVector();

    uint32_t size() const {return size_;}
    uint32_t capacity() const {return capacity_;}
private: // members
    uint32_t size_{0};
    uint32_t capacity_{1};
    T* ptr_{nullptr};
};

template<typename T>
MyVector<T>::MyVector()
{
    ptr_ = new T[capacity_];
}

template<typename T>
void MyVector<T>::Reserve(uint32_t size)
{
    if(nullptr != ptr_)
    {
        delete[] ptr_;
    }
    capacity_ = size;
    ptr_ = new T[capacity_];
}

template<typename T>
template<typename...Args>
void MyVector<T>:: emplace_back(Args&&...args)
{
    if(size_ < capacity_ )
    {
        new (ptr_+size_) T(std::forward<Args>(args)...);
        size_++;
    }
}

template<typename T>
void MyVector<T>::push_back(T obj)
{
    if(size_ < capacity_ )
    {
        new (ptr_+size_) T(obj);
        size_++;
    }
    else
    {
        capacity_ *= 2;
        T* newptr = new T[capacity_];

        for(uint32_t index = 0; index < size_; index++)
        {
            newptr[index] = ptr_[index];
        }

        delete[] ptr_;
        ptr_ = newptr;

        new (ptr_+size_) T(obj);
        size_++;
    }
}

template<typename T>
void MyVector<T>::pop_back()
{
    if(size_ <= capacity_ )
    {
        size_--;
        T* temp = ptr_ + size_;
        temp->~T();
    }
}

template<typename T>
T& MyVector<T>::operator[](uint32_t index)
{
    return ptr_[index];
}

template<typename T>
bool MyVector<T>::empty()
{
    return (size_ == 0)? true: false;
}

template<typename T>
void MyVector<T>:: shrink_to_fit()
{
    if(size_ < capacity_ )
    {
        int size = sizeof(T)*size_;
        T* temp = (T*) malloc(size);

        for(uint32_t i = 0; i < size_; i++)
        {
            new (temp+i) T(ptr_[i]);
        }
        delete[] ptr_;
        ptr_ = temp;
    }
    capacity_ = size_;
}

template<typename T>
MyVector<T>::~MyVector()
{
    if(nullptr != ptr_)
    {
        delete[] ptr_;
        ptr_ = nullptr;
    }
    size_ = 0;
    capacity_ = 1;
}

#endif // __MYVECTOR__