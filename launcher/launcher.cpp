
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
#include <QQuickView>
#include <QScopedPointer>

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));

    if (app->arguments().count() != 2) {
        qWarning() << "Usage: " << qPrintable(app->arguments().first()) << " <appname>";
        return 1;
    }

    // Application name is first parameter (private API for launcher)
    SailfishAppPriv::_PrivateAPI_DoNotUse_setAppName(app->arguments().at(1));

    QScopedPointer<QQuickView> view(SailfishApp::createView());

    view->setSource(SailfishApp::pathToMainQml());
    view->show();

    return app->exec();
}
