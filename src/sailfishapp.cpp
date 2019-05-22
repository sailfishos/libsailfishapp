
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

/*!
  \namespace SailfishApp
  \inheaderfile sailfishapp.h
  \ingroup libsailfishapp-index
  \inmodule libsailfishapp
  \brief The SailfishApp namespace allows the easy creation of Sailfish applications.

  When creating a QT application for use on Sailfish OS, the functions in the \c
  SailfishApp namespace provide a simple and minimal way to manage your
  application lifecycle, provide a QML interface, a QT event loop, and manage
  resources.

  To use libsailfishapp in your project:

  \list 1
      \li Add \c {BuildRequires: pkgconfig(sailfishapp)} to your .spec file
      \li Set \c {TARGET = harbour-yourappname} in your .pro file
      \li Add \c {CONFIG += sailfishapp} to your .pro file
      \li Include \c {sailfishapp.h} in your .cpp file
      \li Use the \c {SailfishApp::} methods in your \c main()
  \endlist

  Example of usage:

  \code
  #include <QtQuick>
  #include <QDebug>
  #include <sailfishapp.h>

  int main(int argc, char *argv[])
  {
      QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
      QScopedPointer<QQuickView> view(SailfishApp::createView());

      view->setSource(SailfishApp::pathTo(QString("qml/main.qml")));
      view->show();

      return app->exec();
  }
  \endcode
*/

namespace SailfishApp
{

/*!
  \fn QGuiApplication * SailfishApp::application(int &argc, char **argv)

  \brief Create a new QGuiApplication instance configured for use on Sailfish OS

  Creates and configures a QGuiApplication ready to be used as part of a
  Sailfish application.

  After having removed any arguments passed to \c main that your application is
  specifically interested in, the remaining arguments should be passed on to
  this call.

  The \c QGuiApplication instance returned is owned by your application, so
  should be deleted when no longer needed.

  The \a argc and \a argv parameters are the command-line parameters to pass in
  for interpretation. The \a argv parameter is an array of pointers to
  zero-terminated strings to be interpreted, while \a argc is the length of
  this arrary (the number of parameters to interpret).

  Returns a new \c QGuiApplication instance to use for your application.
*/
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

/*!
  \fn QQuickView *SailfishApp::createView()

  \brief Create a QQuickView instance for use by your application.

  Creates a new \c QQuickView instance that your application can use to display
  its user interface. The QQuickView can be used, for example, to set up the
  root QML page to be displayed by your application.

  The \c QQuickView instance returned is owned by your application, so should
  be deleted when no longer needed.

  Returns a new \c QQuickView instance to use for your user interface.
*/
QQuickView *createView()
{
    QQuickWindow::setDefaultAlphaBuffer(true);

    QQuickView *view = SailfishAppPriv::view();

    // Add import path to allow private QML import modules in /usr/share/<name>/
    view->engine()->addImportPath(SailfishAppPriv::dataDir());
    view->setResizeMode(QQuickView::SizeRootObjectToView);

    return view;
}

/*!
  \fn QUrl SailfishApp::pathTo(const QString &filename)

  \brief Convert a relative resource path into a fully qualified path specific to the application

  Used to find the fully qualified path of a file contained within the
  application's data directory. The \c filename parameter should specificify
  the file relative to the base of the data directory. The returned URL will
  be a fully qualified path pointing to the file.

  The data directory is usually found at \c /usr/share/$$TARGET (where \c
  $$TARGET is the application name), so for an app called \c harbour-myapp and
  an input filename of \c "qml\myApp.qml" the resulting file would be found at
  \c /usr/share/harbour-myapp/qml/myApp.qml

  The \a filename parameter represents the path relative to the application's data directory.

  Returns A fully qualified path pointing to the file.
 */
QUrl pathTo(const QString &filename)
{
    return QUrl::fromLocalFile(
                QDir::cleanPath(SailfishAppPriv::dataDir() + '/' + filename));
}

/*!
  \fn QUrl SailfishApp::pathToMainQml()

  \brief Returns the path to the QML file used as the root of the application UI

  This function is used to get a path on the local filesystem of the qml file
  that is opened when your application starts, and that will form the root of
  all other QML files displayed by your application. The file should contain an
  \c ApplicationWindow that links to the initial page used for the application,
  and the cover page to be used on the app screen, similar to the following.

  \qml
  import QtQuick 2.0
  import Sailfish.Silica 1.0

  ApplicationWindow
  {
      initialPage: Component { MainPage { } }
	  // ... Points to the first page to be displayed
      cover: Qt.resolvedUrl("cover/CoverPage.qml")
	  // ... Points to the file to be used for the app screen cover
      allowedOrientations: defaultAllowedOrientations
  }
  \endqml

  The path returned will usually be of the form \c
  /usr/share/$$TARGET/qml/$$TARGET.qml (where \c $$TARGET is the application
  name), so for an app called \c harbour-myapp the path returned would be \c
  /usr/share/harbour-myapp/qml/harbour-myapp.qml

  Returns A fully qualified path pointing to the file.
 */
QUrl pathToMainQml()
{
    return QUrl::fromLocalFile(
                QDir::cleanPath(SailfishAppPriv::dataDir() + "/qml/" +
                                SailfishAppPriv::appName() + ".qml"));
}

/*!
  \fn int SailfishApp::main(int &argc, char **argv)

  \brief A convenience function for getting a Sailfish app up-and-running with minimal fuss

  If your application is primarily QML-based, with limited need for
  interactions with C++, then you can use this call to get your application
  up-and-running as swiftly and painlessly as possible. Ensure you have a QML
  file called \c qml/$$TARGET.qml inside your application's data install
  directory (so usually this would be a file \c
  /usr/share/$$TARGET/qml/$$TARGET.qml ) and then simply call \c main to start
  your application's Qt event loop.

  Using this approach you can get a minimal application running using the
  following code.

  \code
  #include <sailfishapp.h>

  int main(int argc, char *argv[])
  {
      return SailfishApp::main(argc, argv);
  }
  \endcode

  After having removed any arguments passed to \c main that your application is
  specifically interested in, the remaining arguments should be passed on to
  this call.

  The return value of the call can be used as the return value for the
  application. On normal exit a zero value will be returned, any other value
  represents an abnormal exit.

  The \a argc and \a argv parameters are the command-line parameters to pass in
  for interpretation. The \a argv parameter is an array of pointers to
  zero-terminated strings to be interpreted, while \a argc is the length of
  this arrary (the number of parameters to interpret).

  Returns the result of the application execution. Zero for normal exit,
  non-zero for anything else.
*/
int main(int &argc, char **argv)
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    view->setSource(SailfishApp::pathToMainQml());
    view->showFullScreen();

    return app->exec();
}

} /* namespace SailfishApp */
