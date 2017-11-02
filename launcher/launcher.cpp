
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

#include <QDebug>
#include <QGuiApplication>
#include <QProcessEnvironment>
#include <QQuickView>
#include <QScopedPointer>

int main(int argc, char *argv[])
{
    // SailfishAppPriv::_PrivateAPI_DoNotUse_setAppName() must be called before
    // SailfishApp::application(), so not using QCoreApplication::arguments()
    // and strictly requiring that <appname> is the very first argument,
    // preceding any options recognized by Qt when used.
    if (argc < 2 || argv[1][0] == '\0' || argv[1][0] == '-') {
        qWarning() << "Usage: " << argv[0] << " <appname> [<qt-option>...]";
        return 1;
    }
    SailfishAppPriv::_PrivateAPI_DoNotUse_setAppName(argv[1]);

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));

    if (QProcessEnvironment::systemEnvironment().contains(
            QStringLiteral("SAILFISHAPP_ENABLE_QML_DEBUGGING"))) {
        (void)QQmlDebuggingEnabler(false);
    }

    QScopedPointer<QQuickView> view(SailfishApp::createView());

    view->setSource(SailfishApp::pathToMainQml());
    view->showFullScreen();

    return app->exec();
}
