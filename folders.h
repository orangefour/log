#pragma once
#include <QObject>
#include <QString>

class QQmlEngine;
class QJSEngine;

class Folders : public QObject {
  Q_OBJECT

public:
  Folders(QObject* parent = nullptr);
  static QObject* singletontypeProvider(QQmlEngine* engine,
                                        QJSEngine* scriptEngine);
public slots:
  static QString appData();
  static QString temp();
  static QString downloads();

private:
  static QString finish(QString path);
};
