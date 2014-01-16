QT += quick qml

INCLUDEPATH += ../../include ../../src

SOURCES += storage_locations.cpp

LIBS += -L../../src -lsailfishapp

# Always use booster
CONFIG += link_pkgconfig
PKGCONFIG += qdeclarative5-boostable
