
/**
 *
 * Copyright (C) 2013 Jolla Ltd.
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


#include "sailfishapp.h"
#include "sailfishapp_priv.h"

#include <QtGlobal>

#include <QGuiApplication>
#include <QQuickView>
#include <QString>
#include <QDir>


QGuiApplication *
SailfishApp::application(int &argc, char **argv)
{
    static QGuiApplication *app = NULL;

    if (app == NULL) {
        app = SailfishAppPriv::application(argc, argv);
    } else {
        qWarning("SailfishApp::application() called multiple times");
    }

    return app;
}

QQuickView *
SailfishApp::createView(const QString &filename)
{
    QQuickWindow::setDefaultAlphaBuffer(true);

    QQuickView *view = SailfishAppPriv::view();

    if (!filename.startsWith("/")) {
        // Filename is relative to the data directory

        // First, try argv[0] if it's an absolute path (needed for booster)
        QString argv0 = QCoreApplication::arguments()[0];

        // If that doesn't give an absolute path, use /proc-based detection
        if (!argv0.startsWith("/")) {
            argv0 = QCoreApplication::applicationFilePath();
        }

        QFileInfo exe = QFileInfo(argv0);

        // "/usr/bin/<appname>" --> "/usr/share/<appname>/<filename>"
        view->setSource(QUrl::fromLocalFile(QDir::cleanPath(QString("%1/%2/%3")
            .arg(exe.absoluteDir().filePath("../share"))
            .arg(exe.fileName())
            .arg(filename))));
    } else {
        view->setSource(QUrl::fromLocalFile(filename));
    }

    return view;
}

int
SailfishApp::main(int &argc, char **argv)
{
    int result = 0;

    QGuiApplication *app = SailfishApp::application(argc, argv);
    QQuickView *view = SailfishApp::createView("qml/main.qml");

    view->show();
    result = app->exec();

    delete view;
    delete app;

    return result;
}
