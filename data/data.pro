TEMPLATE = aux

feature.path = $$[QMAKE_MKSPECS]/features/
feature.files = $$files(*.prf)

INSTALLS += feature
