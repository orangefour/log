#include "folders.h"
#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>
#include <QtGlobal>
#include <iostream>

Folders::Folders(QObject* parent)
  : QObject(parent) {
}

QString Folders::appDir() {
  return finish(QCoreApplication::applicationDirPath());
}

QString Folders::appData() {
  QString path =
#ifdef Q_OS_ANDROID
      QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).last();
#else
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#endif
  return finish(path);
}

QString Folders::documents() {
#ifdef Q_OS_IOS
  return finish(
      QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
#else
  return appData();
#endif
}

QString Folders::temp() {
  return finish(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
}

QString Folders::downloads() {
  return finish(
      QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
}

QString Folders::finish(QString path) {
  path += "/";
  if (!QDir().mkpath(path)) {
    std::cerr << "Can not create folder: " << qPrintable(path) << std::endl;
  }
  return path;
}
