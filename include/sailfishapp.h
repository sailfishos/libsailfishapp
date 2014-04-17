/**
 *
 * Copyright (C) 2013 - 2014 Jolla Ltd.
 * Contact: Thomas Perl <thomas.perl@jollamobile.com>
 * All rights reserved.
 *
 * This file is part of libsailfishapp
 *
 * You may use this file under the terms of the GNU Lesser General
 * Public License version 2.1 as published by the Free Software Foundation
 * and appearing in the file license.lgpl included in the packaging
 * of this file.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * and appearing in the file license.lgpl included in the packaging
 * of this file.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 **/

#ifndef LIBSAILFISHAPP_SAILFISHAPP_H
#define LIBSAILFISHAPP_SAILFISHAPP_H

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QtGlobal>
#include <QUrl>

class QGuiApplication;
class QQuickView;
class QString;

#if defined(LIBSAILFISHAPP_LIBRARY)
#  define SAILFISHAPP_EXPORT Q_DECL_EXPORT
#else
#  define SAILFISHAPP_EXPORT Q_DECL_IMPORT
#endif

namespace SailfishApp {
    // Simple interface: Get boosted application and view
    SAILFISHAPP_EXPORT QGuiApplication *application(int &argc, char **argv);
    SAILFISHAPP_EXPORT QQuickView *createView();

    // Get fully-qualified path to a file in the data directory
    SAILFISHAPP_EXPORT QUrl pathTo(const QString &filename);

    // Very simple interface: Uses "qml/<appname>.qml" as QML entry point
    SAILFISHAPP_EXPORT int main(int &argc, char **argv);
};

/* Forward-declare that main() is exportable (needed for booster) */
Q_DECL_EXPORT int main(int argc, char *argv[]);

#endif /* LIBSAILFISHAPP_SAILFISHAPP_H */
