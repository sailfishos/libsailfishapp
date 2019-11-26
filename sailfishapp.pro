TEMPLATE = subdirs
SUBDIRS = src data launcher tests

OTHER_FILES += README \
    rpm/libsailfishapp.spec

include(doc/doc.pri)
