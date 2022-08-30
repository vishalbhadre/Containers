#include <iostream>
#include <cstring>
#include <initializer_list>

using namespace std;

#ifndef __MYARRAY__
#define __MYARRAY__

template<typename T, size_t N>
class MyArray
{
public: // functions
    MyArray(std::initializer_list<T>&& inputs);

    T& operator[](size_t d);
    T& at(size_t d);
    T* data();

    ~MyArray();
    
    uint32_t size() const {return size_;}
private: // members
    uint32_t size_{0};
    T data_[N];
};

template<typename T, size_t N>
MyArray<T, N>::MyArray(std::initializer_list<T>&& inputs)
{
    size_ = N;
    auto index = 0;    
    for(auto itr = inputs.begin(); itr != inputs.end(); itr++, index++)
    {
        memcpy(data_+index, itr, sizeof(T));
    }
}

template<typename T, size_t N>
T* MyArray<T, N>::data()
{
    return &data_;
}

template<typename T, size_t N>
T& MyArray<T, N>::at(size_t index)
{
    return data_[index];
}

template<typename T, size_t N>
T& MyArray<T, N>::operator[](size_t index)
{
    return data_[index];
}

template<typename T, size_t N>
MyArray<T, N>::~MyArray()
{
}


#endif // __MYARRAY__