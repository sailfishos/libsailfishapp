
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


#ifndef LIBSAILFISHAPP_SAILFISHAPP_PRIV_H
#define LIBSAILFISHAPP_SAILFISHAPP_PRIV_H

#include "sailfishapp.h"

#include <QString>


class QGuiApplication;
class QQuickView;

namespace SailfishAppPriv
{
    // Backend-specific (booster, non-booster) functions
    QGuiApplication *application(int &argc, char **argv);
    QQuickView *view();

    // Non-backend-specific functions
    QString appName();
    QString dataDir();
    QGuiApplication *configureApp(QGuiApplication *app);
    QQuickView *configureView(QQuickView *view);

    // Only used by launcher - please don't use in 3rd party apps
    SAILFISHAPP_EXPORT void _PrivateAPI_DoNotUse_setAppName(QString appName);

    SAILFISHAPP_EXPORT void _PrivateAPI_DoNotUse_onViewCreated(QQuickView *view) __attribute__((weak));
}

#endif /* LIBSAILFISHAPP_SAILFISHAPP_PRIV_H */
