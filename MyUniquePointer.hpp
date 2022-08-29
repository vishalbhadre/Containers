#include <iostream>
#include <functional>
using namespace std;

#ifndef __MYUNIQUEPOINTER__
#define __MYUNIQUEPOINTER__

template<typename T>
class MyUniquePointer
{
    using CallBackDeleterType = std::function<void(T*)>;
    
public: // functions
    MyUniquePointer(T* temp, CallBackDeleterType call = nullptr)
    {
        ptr_ = temp;
        deleter_ = call;
    }
    MyUniquePointer(const MyUniquePointer& ) = delete;
    MyUniquePointer& operator=(const MyUniquePointer& ) = delete;
    MyUniquePointer(MyUniquePointer&& obj)
    {
        ptr_ = obj.ptr_;
        deleter_ = obj.deleter_;

        obj.ptr_ = nullptr;
        obj.deleter_ = nullptr;
    }
    MyUniquePointer& operator=(const MyUniquePointer&& obj)
    {
        ptr_ = obj.ptr_;
        deleter_ = obj.deleter_;

        obj.ptr_ = nullptr;
        obj.deleter_ = nullptr;
        return *this;
    }
    ~MyUniquePointer()
    {
        DeleteMe();
    }
    T* get()
    {
        return ptr_;
    }
    T* operator->()
    {
        return ptr_;
    }
    T& operator*()
    {
        return *ptr_;
    }
    operator bool()
    {
        return (nullptr == ptr_)? false:true;
    }
    T* release()
    {
        T* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }    
    void reset(T* temp)
    {
        DeleteMe();
        ptr_ = temp;
    }
    void swap(MyUniquePointer& temp)
    {
        T* t = ptr_;
        CallBackDeleterType d = deleter_;

        ptr_ = temp.ptr_;
        deleter_ = temp.deleter_;

        temp.ptr_ = t;
        temp.deleter_ = d;
    }
    private:
    T* ptr_{nullptr};
    CallBackDeleterType deleter_{nullptr};

    void DeleteMe()
    {
        if(nullptr != deleter_)
        {
            if(nullptr != ptr_)
            {
                deleter_(ptr_);
            }
        }
        else
        {
            if(nullptr != ptr_)
            {
                delete ptr_;
                ptr_ = nullptr;
            }
        }
    }
};


template<typename T, typename...Args>
MyUniquePointer<T> make_my_unique(Args&&...args)
{
    MyUniquePointer<T> temp(new T(forward<Args>(args)...));
    return temp;
}


#endif // __MYUNIQUEPOINTER__