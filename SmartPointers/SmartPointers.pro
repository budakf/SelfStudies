TEMPLATE = app
QT -= gui

QT +=  core testlib
CONFIG += testcase console c++17
CONFIG -= app_bundle
TARGET = SmartPointers



SOURCES += \
        main.cpp \
        referencecounter.cpp \
        sharedptr.cpp \
        uniqueptr.cpp \
        test/test_smartpointers.cpp


HEADERS += \
    referencecounter.h
