#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T20:05:23
#
#-------------------------------------------------

INCLUDEPATH += $$PWD/../src

QT       += testlib quick concurrent


TARGET = tst_aaaprobabiliytesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    tst_aaaprobabiliytest.cpp \
    ../src/AAAProbability.cpp \
    ../src/UnitArmy.cpp \
    ../src/Infantry.cpp \
    ../src/Tank.cpp \
    ../src/ListModelBase.cpp \
    ../src/Result.cpp \
    ../src/HashModelBase.cpp \
    ../src/SortModel.cpp \
    ../src/Bomber.cpp \
    ../src/Fighter.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../src/UnitArmy.h \
    ../src/AAAProbability.h \
    ../src/Infantry.h \
    ../src/IUnit.h \
    ../src/Tank.h \
    ../src/ListModelBase.h \
    ../src/result.h \
    ../src/HashModelBase.h \
    ../src/ListModel.h \
    ../src/HashModel.h \
    ../src/SortModel.h \
    ../src/Bomber.h \
    ../src/Fighter.h
