#include <iostream>
#include <functional>
using namespace std;

#ifndef __MYSHAREDPOINTER__
#define __MYSHAREDPOINTER__

class Counter
{
    uint32_t ref_count_{1};
    public:
    uint32_t getrefcount()const { return ref_count_;}
    void increaserefcount(){ ref_count_++;}
    void decreaserefcount(){ ref_count_--;}
};

template<typename T>
class MySharedPointer
{
    using CallBackDeleterType = std::function<void(T*)>;
    
public: // functions
    MySharedPointer(T* temp = nullptr, CallBackDeleterType call = nullptr)
    {
        ptr_ = temp;
        deleter_ = call;
        if(nullptr != ptr_)
        ref_ = new Counter();
    }
    MySharedPointer(const MySharedPointer& obj)
    {
        ptr_ = obj.ptr_;
        deleter_ = obj.deleter_;
        ref_ = obj.ref_;
        if(nullptr != ref_)
        ref_->increaserefcount();
    }
    MySharedPointer& operator=(const MySharedPointer& obj)
    {
        ptr_ = obj.ptr_;
        deleter_ = obj.deleter_;
        ref_ = obj.ref_;
        if(nullptr != ref_)
        ref_->increaserefcount();
    }
    MySharedPointer(MySharedPointer&& obj)
    {
        ptr_ = obj.ptr_;
        deleter_ = obj.deleter_;
        ref_ = obj.ref_;

        obj.ptr_ = nullptr;
        obj.deleter_ = nullptr;
        obj.ref_ = nullptr;
    }
    MySharedPointer& operator=(const MySharedPointer&& obj)
    {
        ptr_ = obj.ptr_;
        deleter_ = obj.deleter_;
        ref_ = obj.ref_;

        obj.ptr_ = nullptr;
        obj.deleter_ = nullptr;
        obj.ref_ = nullptr;
        return *this;
    }
    ~MySharedPointer()
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
    void swap(MySharedPointer& temp)
    {
        T* t = ptr_;
        CallBackDeleterType d = deleter_;

        ptr_ = temp.ptr_;
        deleter_ = temp.deleter_;

        temp.ptr_ = t;
        temp.deleter_ = d;
    }
    uint32_t use_count()
    {
        if(nullptr != ref_)
        return ref_->getrefcount();
        else
        return 0;
    }
    private:
    T* ptr_{nullptr};
    CallBackDeleterType deleter_{nullptr};
    Counter *ref_{nullptr};

    void DeleteMe()
    {
        if(nullptr != ref_)
        {
            ref_->decreaserefcount();
            if(0 == ref_->getrefcount())
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
                delete ref_;
                ref_ = nullptr;
            }
        }
    }
};


template<typename T, typename...Args>
MySharedPointer<T> make_my_shared(Args&&...args)
{
    MySharedPointer<T> temp(new T(forward<Args>(args)...));
    return temp;
}


#endif // __MYSHAREDPOINTER__