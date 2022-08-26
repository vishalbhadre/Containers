#include <iostream>
#include <vector>
#include "containers/MyVector.hpp"

using namespace std;

class Data
{
    int id;
    string name;
    public:
    Data():id(0), name(""){cout << endl << "Data constructor " << this;}
    Data(int inputid, string inputname) : id(inputid), name(inputname){cout << endl << "Data param constructor " << this;}
    Data(const Data& obj)
    {
        id = obj.id;
        cout << endl << "Data copy constructor " << this;
    }
    ~Data(){cout << endl << "Data destructor " << this;}
    friend ostream& operator<<(ostream& os, Data& obj)
    {
        os << obj.id << "  " << obj.name;
        return os;
    }
};


int main()
{   
    { 
        // Emplace
        MyVector<Data> v;

        v.Reserve(5);

        v.emplace_back(10, "vishal");
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.emplace_back(35, "tushar");
        {
        cout << endl << "Vector : ";     
        for(uint32_t i = 0; i < v.size(); i++)
            cout << "\t" << v[i] << " " << &v[i];
        }

        v.emplace_back(5, "ashish");
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

    return 0;
}