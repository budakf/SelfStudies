#include <iostream>

#include "sharedptr.cpp"

using namespace std;

int main(){

    int * a = new int(15);
    SharedPtr<int> ptr{a};
    std::cout << ptr << std::endl;

    SharedPtr<int> ptr2 = ptr;

    std::cout << ptr << std::endl;
    std::cout << ptr2 << std::endl;

    return 0;

}
