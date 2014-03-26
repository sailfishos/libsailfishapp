
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


#include "sailfishapp_priv.h"

#include <QCoreApplication>
#include <QGuiApplication>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QLocale>
#include <QTranslator>
#include <QQuickView>
#include <MDesktopEntry>


static QString applicationPath()
{
    QString argv0 = QCoreApplication::arguments()[0];

    if (argv0.startsWith("/")) {
        // First, try argv[0] if it's an absolute path (needed for booster)
        return argv0;
    } else {
        // If that doesn't give an absolute path, use /proc-based detection
        return QCoreApplication::applicationFilePath();
    }
}

static QString customAppName;

namespace SailfishAppPriv {

void _PrivateAPI_DoNotUse_setAppName(QString appName)
{
    // Set custom app name - used by the launcher
    customAppName = appName;
}

QString appName()
{
    if (!customAppName.isNull()) {
        return customAppName;
    }

    QFileInfo exe = QFileInfo(applicationPath());
    return exe.fileName();
}

QString dataDir()
{
    QFileInfo exe = QFileInfo(applicationPath());

    // "/usr/bin/<appname>" --> "/usr/share/<appname>/"
    return QDir::cleanPath(QString("%1/%2")
        .arg(exe.absoluteDir().filePath("../share"))
        .arg(appName()));
}

QGuiApplication *
configureApp(QGuiApplication *app)
{
    // We need to set the appName, so the following features will use
    // the right application name for the data directory:
    //
    //  - QStandardPaths (::DataLocation, ::CacheLocation)
    //  - QSettings (with default organization/application name)
    //  - Qt Quick Local Storage (QQmlEngine::offlineStoragePath())

    app->setOrganizationName(appName());
    app->setOrganizationDomain(appName());
    app->setApplicationName(appName());

    // Automatic i18n support. Translations are supposed to be named
    // "<appname>-<lang>.qm" in "/usr/share/<appname>/translations/"

    QString translations = QDir(dataDir()).filePath("translations");
    if (QDir(translations).exists()) {
        QTranslator *translator = new QTranslator();

        // Fallback translation (optional; only for id-based translations)
        //translator->load(QDir(translations).filePath(appName() + "_eng_en"));

        // Locale-based translation
        translator->load(QLocale::system(), appName(), "-", translations);

        app->installTranslator(translator);
    }

    return app;
}

QQuickView *
configureView(QQuickView *view)
{
    if (!view) {
        qWarning("View is NULL while trying to configure view");
        return NULL;
    }

    MDesktopEntry entry("/usr/share/applications/" + appName() + ".desktop");
    if (entry.isValid()) {
        view->setTitle(entry.name());
    }
    return view;
}

}; /* namespace SailfishAppPriv */
