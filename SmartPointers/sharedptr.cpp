#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include<iostream>

#include "referencecounter.h"

template <typename T>
class SharedPtr{
    public:
        explicit SharedPtr(T * _ptr = nullptr){
            mPtr = _ptr;
            mCounter = new ReferenceCounter();
            if(mPtr)
                (*mCounter)++;
        }

        SharedPtr(SharedPtr<T> & sPtr){
            mPtr = sPtr.get();
            mCounter = sPtr.mCounter;
            (*(sPtr.mCounter))++;
        }

        ~SharedPtr(){
            --(*mCounter);
            if(mCounter->get() == 0) {
                delete mPtr;
                delete mCounter;
            }
        }

        T * get() const { return mPtr;}
        int use_count() const { return mCounter->get();}

        friend std::ostream & operator<<(std::ostream & os , SharedPtr<T> & sPtr ){
            os << sPtr.get() << "  " << *(sPtr.get()) << "  " << *(sPtr.mCounter) << std::endl;
            return os;
        }

        void set(T * sPtr){
            if(mPtr){
                delete mPtr;
                delete mCounter;
            }

            mPtr = sPtr;
            mCounter = new ReferenceCounter();
            if(mPtr)
                (*mCounter)++;
        }

        void reset(){
            this->set(nullptr);
        }

    private:
        ReferenceCounter *mCounter = nullptr;
        T * mPtr = nullptr;
};

#endif // SHAREDPTR_H
