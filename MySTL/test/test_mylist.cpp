#ifndef TEST_MYLIST_CPP
#define TEST_MYLIST_CPP

#include <QObject>
#include <QtTest/QtTest>
#include "myList.cpp"

class TestMyList : public QObject{

    Q_OBJECT
    MyList<int> intList{};

private slots:

    void test_constructor(){
        int * data = new int{23};
        Node<int> *node = new Node<int>{data};
        MyList<int> intList2{node};
        QCOMPARE(intList2.length(), 1);
        QCOMPARE(*(intList2.front()->mData), 23);
    }

    void test_front(){
        QCOMPARE(intList.front(), nullptr);

        int * data = new int{223};
        Node<int> * newNode = new Node<int>{data};
        MyList<int> intList2{newNode};
        QCOMPARE(intList2.front(), newNode);
    }

    void test_back(){
        QCOMPARE(intList.back(), nullptr);

        int * data = new int{223};
        Node<int> * newNode = new Node<int>{data};
        MyList<int> intList2{newNode};
        QCOMPARE(intList2.back(), newNode);

        int * data2 = new int{223};
        Node<int> * newNode2 = new Node<int>{data2};
        intList2.pushBack(newNode2);
        QCOMPARE(intList2.back(), newNode2);
    }

    void test_pushBack(){
        int * data = new int{76};
        Node<int> *node = new Node<int>{data};
        intList.pushBack(node);
        QCOMPARE(intList.length(), 1);
        QCOMPARE(*(intList.front()->mData), 76);

        int * data2 = new int{726};
        Node<int> *node2 = new Node<int>{data2};
        intList.pushBack(node2);
        QCOMPARE(intList.length(), 2);
        QCOMPARE(*(intList.front()->next->mData), 726);
    }

    void test_begin_end(){
        int * data = new int{76};
        Node<int> *node = new Node<int>{data};
        MyList<int> intList2{node};
        QCOMPARE(intList2.length(), 1);
        QCOMPARE(*(intList2.begin()->get()->mData), 76);
        QCOMPARE(*(intList2.end()->get()->mData), 76);

        int * data2 = new int{726};
        Node<int> *node2 = new Node<int>{data2};
        intList2.pushBack(node2);
        QCOMPARE(intList2.length(), 2);
        QCOMPARE(*(intList2.end()->get()->mData), 726);

    }


};

#include "test_mylist.moc"

#endif
