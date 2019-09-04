#include "test_myvector.cpp"
#include "test_myiterator.cpp"
#include "test_mylist.cpp"

int main(int argc, char *argv[]){

    TestMyIterator testMyIterator;
    TestMyVector testMyVector;
    TestMyList testMyList;

    return QTest::qExec(&testMyVector, argc, argv)
           || QTest::qExec(&testMyIterator, argc, argv)
           || QTest::qExec(&testMyList, argc, argv);
}
