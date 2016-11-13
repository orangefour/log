#include "folders.h"
#include <QDir>
#include <QStandardPaths>
#include <QtGlobal>
#include <iostream>

Folders::Folders(QObject* parent)
  : QObject(parent) {
}

QObject* Folders::singletontypeProvider(QQmlEngine* /*engine*/,
                                        QJSEngine* /*scriptEngine*/) {
  Folders* o = new Folders();
  return o;
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

QString Folders::temp() {
  return QStandardPaths::writableLocation(QStandardPaths::TempLocation) +
         QDir::separator();
}

QString Folders::downloads() {
  return QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) +
         QDir::separator();
}

QString Folders::finish(QString path) {
  path += QDir::separator();
  if (!QDir().mkpath(path)) {
    std::cerr << "Can not create folder: " << qPrintable(path) << std::endl;
  }
  return path;
}
