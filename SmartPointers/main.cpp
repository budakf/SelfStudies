#include <iostream>
#include <QtTest/QtTest>

#include "sharedptr.cpp"
#include "uniqueptr.cpp"

using namespace std;

#define TEST

#ifndef TEST
    int main(){

        //int * a = new int(15);
        SharedPtr<int> ptr{new int(15)};
        std::cout << ptr;

        SharedPtr<int> ptr2 = ptr;

        std::cout << ptr << ptr2;

        SharedPtr<int> pptr{nullptr};
        {
            SharedPtr<int> pptr2 = pptr;
        }

    //    int * a = new int(12);
    //    UniquePtr<int> uPtr{a};
    //    UniquePtr<int> uPtr2{std::move(uPtr)};

    //    if(!uPtr.isNullptr())
    //         std::cout<< uPtr;

    //    std::cout<< uPtr2;


        return 0;

    }


#endif

