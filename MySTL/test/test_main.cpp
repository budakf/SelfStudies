#include "test_myvector.cpp"
#include "test_myiterator.cpp"


int main(int argc, char *argv[]){

    TestMyIterator testMyIterator;
    TestMyVector testMyVector;

    return QTest::qExec(&testMyVector, argc, argv) || QTest::qExec(&testMyIterator, argc, argv) ;
}
