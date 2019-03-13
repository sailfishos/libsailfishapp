TEMPLATE = aux

CONFIG += mer-qdoc-template
MER_QDOC.project = libsailfishapp
MER_QDOC.config = config/libsailfishapp.qdocconf
MER_QDOC.style = offline
MER_QDOC.path = /usr/share/doc/libsailfishapp/

OTHER_FILES += \
    $$PWD/config/*.qdocconf \
    $$PWD/config/style/*.css \
    $$PWD/config/images/*.png \
    $$PWD/config/libsailfishapp.qdocconf \
    $$PWD/src/*.qdoc
