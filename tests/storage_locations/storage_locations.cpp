
/**
 *
 * Copyright (C) 2014 Jolla Ltd.
 * Contact: Thomas Perl <thomas.perl@jolla.com>
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

#include <QGuiApplication>
#include <QStandardPaths>
#include <QSettings>
#include <QQmlEngine>
#include <QDebug>
#include <QDir>


int main(int argc, char *argv[])
{
    QGuiApplication *app = SailfishApp::application(argc, argv);

    qDebug() << "== QCoreApplication ==";
    qDebug() << "Organization:" << QCoreApplication::organizationName();
    qDebug() << "Application:" << QCoreApplication::applicationName();

    qDebug() << "== QStandardPaths ==";
    qDebug() << "Writable data:" << QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    qDebug() << "Writable cache:" << QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

    // QStandardPaths::ConfigLocation only tells us the generic config
    // location; in order to get the application-specific location, we
    // append the QCoreApplication::applicationName() to it (we could
    // also use QCoreApplication::organizationName(), as both are set
    // by libsailfishapp so that Qt always uses the right paths)
    qDebug() << "== Target paths ==";
    qDebug() << "Config goes into:" << QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation))
        .filePath(QCoreApplication::applicationName());

    qDebug() << "== QSettings ==";
    qDebug() << "File name:" << QSettings().fileName();

    qDebug() << "== QQmlEngine ==";
    qDebug() << "Offline storage path:" << QQmlEngine().offlineStoragePath();

    delete app;

    return 0;
}
