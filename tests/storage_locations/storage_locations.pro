QT += quick qml

INCLUDEPATH += ../../include ../../src

SOURCES += storage_locations.cpp

LIBS += -L../../src -lsailfishapp

# Always use booster
CONFIG += link_pkgconfig
packagesExist(qdeclarative$${QT_MAJOR_VERSION}-boostable) {
    PKGCONFIG += qdeclarative$${QT_MAJOR_VERSION}-boostable
}
