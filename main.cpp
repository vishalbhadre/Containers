#include <iostream>
#include <vector>
#include "MyVector.hpp"
#include "MyUniquePointer.hpp"
#include "MySharedPointer.hpp"

using namespace std;

class Data
{
    int id;
    public:
    Data():id(0){cout << endl << "Data constructor " << this;}
    Data(int inputid) : id(inputid){cout << endl << "Data param constructor " << this;}
    Data(const Data& obj)
    {
        id = obj.id;
        cout << endl << "Data copy constructor " << this;
    }
    Data& operator=(const Data& obj)
    {
        id = obj.id;
        cout << endl << "Data copy assignment " << this;
        return *this;
    }
    Data(Data&& obj) 
    {
        id = obj.id;

        obj.id = 0;
        cout << endl << "Data move constructor " << this;
    }
    Data& operator=(Data&& obj) 
    {
        id = obj.id;

        obj.id = 0;
        cout << endl << "Data move assignment " << this; 
        return *this;
    }
    ~Data()
    {
        cout << endl << "Data destructor " << this;
    }
    friend ostream& operator<<(ostream& os, Data& obj)
    {
        os << obj.id;
        return os;
    }
};


int main()
{   
    { 
        // Emplace
        MyVector<Data> v;

        v.Reserve(5);

        v.emplace_back(10);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.emplace_back(35);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.emplace_back(5);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }
        cout << endl << "Size : " << v.size() << "\t Capacity : " << v.capacity();
        cout << endl << "Now shirnking...";
        v.shrink_to_fit();
        cout << endl << "Size : " << v.size() << "\t Capacity : " << v.capacity();
        cout << endl << "Popped ";
        v.pop_back();
        cout << endl << "Size : " << v.size() << "\t Capacity : " << v.capacity();
    }
    cout << endl;
    { 
        cout << endl << "push and pop ";   
        // push and pop
        int ii = 10, j = 35;
        MyVector<int> v;

        v.push_back(ii);
        {
            cout << endl << "Vector : ";       
            for(uint32_t i = 0; i < v.size(); i++)
                cout << "\t" << v[i] << " " << &v[i];
        }

        v.push_back(6);
        {
            cout << endl << "Vector : ";     
            for(uint32_t i = 0; i < v.size(); i++)
                cout << "\t" << v[i] << " " << &v[i];
        }

        v.push_back(j);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.push_back(70);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.push_back(65);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.push_back(81);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.push_back(103);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.push_back(127);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.push_back(149);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.push_back(167);
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }
        
        cout << endl << "Size : " << v.size() << "\tCapacity : " << v.capacity();
        
        v.pop_back();
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        cout << endl << "Size : " << v.size() << "\tCapacity : " << v.capacity();

        v.pop_back();
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        cout << endl << "Size : " << v.size() << "\tCapacity : " << v.capacity();
    }
    cout << endl <<"pointers" ;
    {
        cout << endl << "u1 about to be created";
        MyUniquePointer<Data> u1 = make_my_unique<Data>(10);
        cout << endl << "U1 : " << u1.get();
        MyUniquePointer<Data> u2 = std::move(u1);
        cout << endl << "U1 : " << u1.get();
        cout << endl << "U2 : " << u2.get();
        cout << endl << "u1 about to be destroyed";
    }
    {
        cout << endl << "Array about to be created";
        MyUniquePointer<Data> u1(new Data[3], [](Data* ptr)
        {
            cout << endl << "Custom deleter";
            delete[] ptr;
        });
    }
    
    {
        MySharedPointer<Data> u3;
        {
            cout << endl << "shared about to be created";
            MySharedPointer<Data> u1 = make_my_shared<Data>(10);
            cout << endl << "U1 : " << u1.get();
            {
                MySharedPointer<Data> u2 = u1;
                cout << endl << "U1 : " << u1.get();
                cout << endl << "U2 : " << u2.get();
                u3 = u2;
                cout << endl << "u2 about to be destroyed";
            }
            cout << endl << "u1 about to be destroyed";
        }
        cout << endl << "u3 about to be destroyed";
    }
    cout << endl << "destroyed" << endl;

    return 0;
}