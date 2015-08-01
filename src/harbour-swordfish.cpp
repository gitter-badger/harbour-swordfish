/*
  Copyright (C) 2015 Thomas Tanghus <thomas@tanghus.net>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QStandardPaths>
#include "settings.h"
#include "filedownloader.h"

int main(int argc, char *argv[]) {
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    app->setApplicationVersion(QString(APP_VERSION));
    Settings *settings = new Settings("harbour-swordfish", "net.tanghus.swordfish.sailfish");
    FileDownloader *downloader = new FileDownloader();

    QQuickView* view = SailfishApp::createView();
    qDebug() << "Import path" << SailfishApp::pathTo("qml/components/").toLocalFile();
    view->engine()->addImportPath(SailfishApp::pathTo("lib/").toLocalFile());
    view->engine()->addImportPath(SailfishApp::pathTo("qml/components/").toLocalFile());
    view->engine()->addImportPath(SailfishApp::pathTo("qml/pages/").toLocalFile());

    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    qDebug() << "Cache dir:" << cacheDir;

    QString apiKey = QString(API_KEY);

    QTranslator *translator = new QTranslator;

    QString locale = QLocale::system().name();

    qDebug() << "Translations:" << SailfishApp::pathTo("translations").toLocalFile() + "/" + locale + ".qm";

    if(!translator->load(SailfishApp::pathTo("translations").toLocalFile() + "/" + locale + ".qm")) {
        qDebug() << "Couldn't load translation";
    }
    app->installTranslator(translator);

    view->rootContext()->setContextProperty("downloader", downloader);
    view->rootContext()->setContextProperty("settings", settings);
    view->rootContext()->setContextProperty("apiKey", apiKey);
    view->setSource(SailfishApp::pathTo("qml/harbour-swordfish.qml"));
    view->showFullScreen();
    return app->exec();
}

