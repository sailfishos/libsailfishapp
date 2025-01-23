TARGET = sailfish-qml

QT += quick qml

target.path = /usr/bin
INSTALLS += target

INCLUDEPATH += ../include ../src

SOURCES += launcher.cpp

LIBS += -L../src -lsailfishapp

# Always use booster
CONFIG += link_pkgconfig
packagesExist(qdeclarative$${QT_MAJOR_VERSION}-boostable) {
    PKGCONFIG += qdeclarative$${QT_MAJOR_VERSION}-boostable
}
