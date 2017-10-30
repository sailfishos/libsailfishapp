
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


#include "sailfishapp.h"
#include "sailfishapp_priv.h"

#include <QtGlobal>

#include <QGuiApplication>
#include <QScopedPointer>
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

    return view;
}

QUrl pathTo(const QString &filename)
{
    return QUrl::fromLocalFile(QDir::cleanPath(QString("%1/%2")
        .arg(SailfishAppPriv::dataDir())
        .arg(filename)));
}

QUrl pathToMainQml()
{
    QString mainQml = QString("qml/%1.qml").arg(SailfishAppPriv::appName());
    return pathTo(mainQml);
}

int main(int &argc, char **argv)
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    view->setSource(SailfishApp::pathToMainQml());
    view->showFullScreen();

    return app->exec();
}

}; /* namespace SailfishApp */
