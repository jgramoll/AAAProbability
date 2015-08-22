TEMPLATE = app

QT += qml quick concurrent

INCLUDEPATH += src

RESOURCES += qml.qrc

SOURCES += main.cpp \
    src/AAAProbability.cpp \
    src/UnitArmy.cpp \
    src/Infantry.cpp \
    src/Tank.cpp \
    src/ListModelBase.cpp \
    src/Result.cpp \
    src/HashModelBase.cpp \
    src/SortModel.cpp \
    src/Bomber.cpp \
    src/Fighter.cpp

HEADERS += \
    src/AAAProbability.h \
    src/UnitArmy.h \
    src/IUnit.h \
    src/Infantry.h \
    src/Tank.h \
    src/ListModelBase.h \
    src/Result.h \
    src/HashModelBase.h \
    src/ListModel.h \
    src/HashModel.h \
    src/SortModel.h \
    src/Bomber.h \
    src/Fighter.h

# Default rules for deployment.
include(deployment.pri)
