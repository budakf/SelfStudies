#include <QCoreApplication>

#define TEST

#ifndef TEST

    int main(int argc, char *argv[]){
        QCoreApplication a(argc, argv);
        return a.exec();
    }

#endif

