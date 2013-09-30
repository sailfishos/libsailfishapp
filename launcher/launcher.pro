TARGET = sailfish-qml

QT += quick qml

target.path = /usr/bin
INSTALLS += target

INCLUDEPATH += ../include ../src

SOURCES += launcher.cpp

LIBS += -L../src -lsailfishapp

# Always use booster
CONFIG += link_pkgconfig
PKGCONFIG += qdeclarative5-boostable
