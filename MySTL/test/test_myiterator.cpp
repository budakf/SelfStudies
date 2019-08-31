#ifndef TEST_MYITERATOR_CPP
#define TEST_MYITERATOR_CPP

#include <QtTest/QtTest>
#include "myVector.cpp"

class TestMyIterator: public QObject{

    Q_OBJECT

public:
    TestMyIterator(){}

private slots:

    void initTestCase(){

    }

    void test_iteratorOverMyVector(){
        MyVector<int> array{10, 5};
        MyIterator<int> it = array.begin();
        unsigned int i=0;

        for(; it!=array.end(); it++){
            QCOMPARE(*it, array.at(i));
            i++;
        }
    }

    void test_advance(){
        MyVector<int> array{10, 5};
        MyIterator<int> it = array.begin();
        unsigned int i = 0;
        for(auto & element : array){
            element = i;
            i++;
        }

        it.advance(5);
        QCOMPARE(*it,array[5]);
    }

};

#include "test_myiterator.moc"

#endif
