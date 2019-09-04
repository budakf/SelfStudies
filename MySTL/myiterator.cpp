#ifndef MYITERATOR_CPP
#define MYITERATOR_CPP

template <typename T>
class MyIterator{

public:
    MyIterator(T * _ptr = nullptr) : mPtr(_ptr){ }

    MyIterator(const MyIterator<T> & iterator): mPtr(iterator.mPtr){}

    ~MyIterator(){
        //delete mPtr;  it is not neccessary because iterator is not owner of the object. Only owner must destruct object.
        //              iterator is assistant class to iterate container
    }

    MyIterator<T> & operator++(){
        mPtr++;
        return *this;
    }

    MyIterator<T> operator++(int){ // Postfix
        MyIterator<T> temp = *this;
        mPtr++;
        return temp;
    }

    MyIterator<T> & operator--(){
        mPtr--;
        return *this;
    }

    MyIterator<T> operator--(int){ // Postfix
        MyIterator<T> temp = *this;
        mPtr--;
        return temp;
    }

    bool operator==(MyIterator<T> iterator){
        return mPtr == iterator.mPtr;
    }

    bool operator!=(MyIterator<T> iterator){
        return mPtr != iterator.mPtr;
    }

    T & operator*(){
        return *mPtr;
    }

    T * get(){
        return mPtr;
    }

    void advance(unsigned int number){
        mPtr+=number;
    }



private:
    T * mPtr;


};

#endif
