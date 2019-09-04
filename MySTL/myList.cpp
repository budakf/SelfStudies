#ifndef MYLIST_CPP
#define MYLIST_CPP

#include <iostream>

#include "myIterator.cpp"

template <typename T>
struct Node{

    T * mData;
    Node<T> * next;
    Node(T * pData) : mData(pData), next(nullptr){}

};

template <typename T>
class MyList{

public:
    explicit MyList(Node<T> * pHead = nullptr) : mHead(pHead){
        mLength = (mHead == nullptr) ? 0 : 1;
    }

    Node<T> * front(){
        return mHead;
    }

    Node<T> * back(){
        Node<T> * currentNode = mHead;
        while(currentNode && currentNode->next){
            currentNode = currentNode->next;
        }
        return currentNode;
    }

    unsigned int length(){
        return mLength;
    }

    void pushBack(Node<T> * newNode){
        if(mHead == nullptr){
            mHead = newNode;
        }
        else{
            Node<T> * currentNode = mHead;
            while(currentNode->next){
                currentNode = currentNode->next;
            }
            currentNode->next = newNode;
        }
        mLength++;
    }

    MyIterator< Node<T> > * begin(){
        return makeIterator(mHead);
    }

    MyIterator< Node<T> > * end(){
        return makeIterator(back());
    }


private:
    Node<T> * mHead;
    unsigned int mLength;
    MyIterator< Node<T> > * makeIterator(Node<T> * node){
        MyIterator< Node<T> > * it = new MyIterator< Node<T> >{node};
        return it;
    }


};

#endif
