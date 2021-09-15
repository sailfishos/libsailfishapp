TEMPLATE = aux

CONFIG += sailfish-qdoc-template

SAILFISH_QDOC.project = libsailfishapp
SAILFISH_QDOC.config = libsailfishapp.qdocconf
SAILFISH_QDOC.style = offline
SAILFISH_QDOC.path = /usr/share/doc/libsailfishapp/

OTHER_FILES += \
    $$PWD/libsailfishapp.qdocconf \
    $$PWD/src/*.qdoc
