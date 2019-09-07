#ifndef MYLIST_CPP
#define MYLIST_CPP

#include <iostream>

#include "myIterator.cpp"

template <typename T>
struct Node{

    T * mData;
    Node<T> * next;
    Node(T * pData) : mData(pData), next(nullptr){}
    ~Node(){
        delete mData;
    }

};

template <typename T>
class MyList{

public:
    explicit MyList(Node<T> * pHead = nullptr) : mHead(pHead){
        mLength = (mHead == nullptr) ? 0 : 1;
    }

    ~MyList(){ // Destructs node recursively
        destructNodes(mHead);
        delete mHead;
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

    void insert(Node<T> * newNode, unsigned int pIndex){
        if(pIndex >= mLength)
            pushBack(newNode);

        else if(pIndex == 0){
            newNode->next = mHead;
            mHead = newNode;
            mLength++;
        }
        else{
            Node<T> * temp = mHead;
            for(unsigned int i = 0; i < (pIndex-1); i++){
                temp = temp->next;
            }
            Node<T> * oldNodeAtPIndex = temp->next;
            temp->next = newNode;
            newNode->next = oldNodeAtPIndex;
            mLength++;
        }

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

    void destructNodes(Node<T> * node){
        Node<T> * currentNode = node->next;
        while(currentNode){
            destructNodes(currentNode);
            currentNode = currentNode->next;
        }
    }

};

#endif
