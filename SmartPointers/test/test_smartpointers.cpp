#include "QObject"
#include <QtTest>

#include "sharedptr.cpp"
#include "uniqueptr.cpp"
#include "referencecounter.h"

class TestSmartPointers : public QObject{
    Q_OBJECT

public:
    TestSmartPointers(){}

private slots:

    void initTestCase(){}
    void test_referenceCounter(){
        ReferenceCounter * ref = new ReferenceCounter();
        QCOMPARE(ref->get(), 0);
        ref->set(5);
        QCOMPARE(ref->get(), 5);
        delete ref;
    }

    void test_operatorOfreferenceCounter(){
        ReferenceCounter * ref = new ReferenceCounter(4);
        QCOMPARE(ref->get(), 4);

        (*ref)--;
        QCOMPARE(ref->get(), 3);

        (*ref)++;
        QCOMPARE(ref->get(), 4);

        --(*ref);
        QCOMPARE(ref->get(), 3);

        ++(*ref);
        QCOMPARE(ref->get(), 4);
        delete ref;
    }

    void test_sharedPtr(){
        SharedPtr<int> s_ptr;
        QCOMPARE(s_ptr.get(), nullptr);
        QCOMPARE(s_ptr.use_count(), 0);

        s_ptr.set(new int{12});
        QCOMPARE(*(s_ptr.get()), 12);
        QCOMPARE(s_ptr.use_count(), 1);

        {
            SharedPtr<int> s_ptr2 = s_ptr;
            QCOMPARE(s_ptr.use_count(), 2);
            QCOMPARE(s_ptr2.use_count(), 2);
        }

        {
            SharedPtr<int> s_ptr3(s_ptr);
            QCOMPARE(s_ptr.use_count(), 2);
            QCOMPARE(s_ptr3.use_count(), 2);
        }

        QCOMPARE(s_ptr.use_count(), 1);

        s_ptr.reset();
        QCOMPARE(s_ptr.get(), nullptr);
        QCOMPARE(s_ptr.use_count(), 0);

    }

    void test_uniquePtr(){

        UniquePtr<double> u_ptr;
        QCOMPARE(u_ptr.get(), nullptr);
        if(u_ptr.isNullptr())
            std::cout<<"u_ptr is nullptr"<<std::endl;

        UniquePtr<double> u_ptr2{new double {7.65}};
        QCOMPARE(*(u_ptr2.get()), 7.65);

        UniquePtr<double> u_ptr3(new double{9.4});
        QCOMPARE(*(u_ptr3.get()), 9.4);

        UniquePtr<double> u_ptr4{ u_ptr3.release() };
        QCOMPARE(*(u_ptr4.get()), 9.4);
        QCOMPARE(u_ptr3.get(), nullptr);

    }

};

QTEST_APPLESS_MAIN(TestSmartPointers)
#include "test_smartpointers.moc"
