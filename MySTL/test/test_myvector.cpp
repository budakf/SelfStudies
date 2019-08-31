#ifndef TEST_MYVECTOR_CPP
#define TEST_MYVECTOR_CPP

#include <QtTest/QtTest>
#include <iomanip>

#include "myVector.cpp"

class TestMyVector : public QObject{

    Q_OBJECT

public:
    TestMyVector(){ }

private slots:

    void initTestCase(){}

    void test_sizeAndCapacity(){

        MyVector<int> intArray{};
        QCOMPARE(intArray.size(), 0);
        QCOMPARE(intArray.capacity(), 0);

        int element = 34;
        intArray.pushBack(element);
        QCOMPARE(intArray.size(), 1);
        QCOMPARE(intArray.capacity(), 2);
     }

    void test_atFunction(){

        MyVector<int> intArray{10, 5};
        for(unsigned int i = 0; i<10; i++){
            QCOMPARE(intArray[i], 5);
            QCOMPARE(intArray.at(i), 5);
        }
    }

    void test_pushBackAndInsert(){

        MyVector<int> intArray;

        int var = 12;
        int var2 = 775;
        int var3 = 90;
        int var4 = 76;
        int var5 = 6;

        intArray.pushBack(var);
        QCOMPARE(intArray[0], 12);
        QCOMPARE(intArray.at(0), 12);
        QCOMPARE(intArray.size(), 1);
        QCOMPARE(intArray.capacity(), 2);

        intArray.pushBack(var2);
        QCOMPARE(intArray[1], 775);
        QCOMPARE(intArray.at(1), 775);
        QCOMPARE(intArray.size(), 2);
        QCOMPARE(intArray.capacity(), 2);

        intArray.pushBack(var3);
        QCOMPARE(intArray[2], 90);
        QCOMPARE(intArray.at(2), 90);
        QCOMPARE(intArray.size(), 3);
        QCOMPARE(intArray.capacity(), 6);
        intArray.insert(var4, 2);
        QCOMPARE(intArray[2], 76);
        QCOMPARE(intArray.at(2), 76);
        QCOMPARE(intArray.size(), 4);
        QCOMPARE(intArray.capacity(), 6);

        QCOMPARE(intArray.insert(var5, 77), false);
        QCOMPARE(intArray.insert(var5, -1), false);

//        for(unsigned int i = 0; i < dynamicArray.size(); i++)
//            std::cout<<dynamicArray.get(i)<<std::endl;

    }

    void test_isEmpty(){
        MyVector<int> intArray{};
        QCOMPARE(intArray.isEmpty(), true);
        int element = 8;
        intArray.pushBack(element);
        QCOMPARE(intArray.isEmpty(), false);
    }

    void test_clear(){
        MyVector<int> intArray{10, 5};
        intArray.clear();
        QCOMPARE(intArray.isEmpty(), true);
        QCOMPARE(intArray.size(), 0);
        QCOMPARE(intArray.capacity(), 0);

        int element = 88;
        intArray.pushBack(element);
        QCOMPARE(intArray.size(), 1);
        QCOMPARE(intArray.capacity(), 2);
    }

    void test_erase(){
        MyVector<int> intArray{10, 5};
        for(unsigned int i = 0; i<10; i++){
            intArray[i] += i;
        }
        intArray.erase(0);  // 5
        intArray.erase(intArray.size()-1); // 14
        intArray.erase(4);  // 10
        for(auto i : intArray)
            std::cout<<i<<" ";
    }


};

#include "test_myvector.moc"

#endif
