TEMPLATE = aux

docs.path = $$PREFIX/share/doc/libsailfishapp/
docs.files = index.html static/background.jpg static/develop.png
docs.depends = mdown

INSTALLS += docs

mdown.files = mdown
mdown.commands = (cat static/header.html; markdown documentation.mdown; cat static/footer.html) > index.html
mdown.depends = documentation.mdown

QMAKE_EXTRA_TARGETS = mdown
