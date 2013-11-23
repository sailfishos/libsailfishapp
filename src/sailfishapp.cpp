
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
#include <QScreen>
#include <QSize>
#include <QQuickView>
#include <QString>
#include <QDir>
#include <QQmlEngine>


namespace SailfishApp {

QGuiApplication *application(int &argc, char **argv)
{
    static QGuiApplication *app = NULL;

    if (app == NULL) {
        app = SailfishAppPriv::application(argc, argv);
    } else {
        qWarning("SailfishApp::application() called multiple times");
    }

    return app;
}

QQuickView *createView()
{
    QQuickWindow::setDefaultAlphaBuffer(true);

    QQuickView *view = SailfishAppPriv::view();

    // Add import path to allow private QML import modules in /usr/share/<name>/
    view->engine()->addImportPath(SailfishAppPriv::dataDir());

    // XXX: The next 4 lines fix a bug in QtWayland not showing the window
    // and should eventually be removed (see JB#8917)
    QGuiApplication *application = static_cast<QGuiApplication *>(QGuiApplication::instance());
    QSize screenSize = application->primaryScreen()->size();
    view->resize(screenSize.width(), screenSize.height());

    return view;
}

QUrl pathTo(const QString &filename)
{
    return QUrl::fromLocalFile(QDir::cleanPath(QString("%1/%2")
        .arg(SailfishAppPriv::dataDir())
        .arg(filename)));
}

int main(int &argc, char **argv)
{
    int result = 0;

    QGuiApplication *app = SailfishApp::application(argc, argv);
    QQuickView *view = SailfishApp::createView();

    QString qml = QString("qml/%1.qml").arg(SailfishAppPriv::appName());
    view->setSource(SailfishApp::pathTo(qml));
    view->show();

    result = app->exec();

    delete view;
    delete app;

    return result;
}

}; /* namespace SailfishApp */
