TEMPLATE = aux

CONFIG += mer-qdoc-template
MER_QDOC.project = libsailfishapp
MER_QDOC.config = libsailfishapp.qdocconf
MER_QDOC.style = offline
MER_QDOC.path = /usr/share/doc/libsailfishapp/

OTHER_FILES += \
    $$PWD/libsailfishapp.qdocconf \
    $$PWD/index.qdoc

