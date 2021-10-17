#ifndef MYVECTOR_CPP
#define MYVECTOR_CPP

#include <iostream>

//template<typename T>
//class MyIterator;

#include "myIterator.cpp"

template <typename T>
class MyVector{

public:
    explicit MyVector(unsigned int pCapacity = 0)
        : mSize(new unsigned int {0}), mCapacity(new unsigned int {pCapacity}),
          mArray(new T[pCapacity]){
        for(unsigned int i = 0; i < *mSize; i++){
            mArray[i] = 0;
        }
    }

    MyVector(unsigned int pCapacity, T pValue)
        : mSize(new unsigned int {pCapacity}) , mCapacity(new unsigned int {pCapacity}),
          mArray(new T[pCapacity]){
        for(unsigned int i = 0; i < *mSize; i++){
            mArray[i] = pValue;
        }
    }

    void pushBack(T &pElement){
        (*mSize)++;
        if( (*mSize) > (*mCapacity) ){
            enhanceCapacity();
        }
        mArray[(*mSize)-1] = pElement;
    }

    T & operator[](unsigned int pIndex){
        try {
            return mArray[pIndex];
        } catch (std::exception e) {
            std::cout<<e.what();
        }
    }

    bool insert(const T & pElement, unsigned int pIndex){
        if(pIndex > *mSize) return false;

        (*mSize)++;
        if(pIndex < (*mSize)-1 )
            rightShift(pIndex);
        mArray[pIndex] = pElement;
        return true;
    }

    T * data(){
        return mArray;
    }

    const T & at(unsigned int pIndex){
        return mArray[pIndex];
    }

    unsigned int size(){
        return *mSize;
    }

    unsigned int capacity(){
        return *mCapacity;
    }

    bool isEmpty(){
        return (*mSize) == 0;
    }

    bool erase(unsigned int pIndex){
        if(pIndex >= *mSize) return false;

        (*mSize)--;
        leftShift(pIndex);

    }

    void clear(){
        delete [] mArray;
        delete mSize;
        delete mCapacity;
        mArray = new T [0];
        mSize = new unsigned int {0};
        mCapacity = new unsigned int {0};
    }

    MyIterator<T> begin(){
        return makeIterator(0);
    }

    MyIterator<T> end(){
        return makeIterator(*mSize);
    }

    ~MyVector(){
        delete [] mArray;
        delete mSize;
        delete mCapacity;
    }


private:
    T * mArray = nullptr;
    unsigned int * mSize = nullptr;
    unsigned int * mCapacity = nullptr;

    template <typename U>
    void swap(U & first, U & second){
        U & temp = first;
        first = second;
        second = temp;
    }

    void enhanceCapacity(){
        *mCapacity = (*mSize) * 2;
        T * temporaryStorage = new T [*mCapacity];
        this->swap(temporaryStorage, mArray);

         for(unsigned int i = 0; i < (*mSize)-1; i++){
            mArray[i] = temporaryStorage[i];
        }
    }

    void leftShift(unsigned int pIndex){  // assist function for erase operation
        for(unsigned int i = pIndex; i < *mSize ; i++){
            mArray[i] = mArray[i+1];
        }
    }

    void rightShift(unsigned int pIndex){  // assist function for insert operation
        if(*mSize > *mCapacity)
            enhanceCapacity();
        for(unsigned int i = (*mSize)-1; i > pIndex ; i--){
            mArray[i] = mArray[i-1];
        }
    }

    MyIterator<T> makeIterator(unsigned int pIndex){
        MyIterator<T> it{ &mArray[pIndex] };
        return it;
    }


};

#endif
