#pragma once
#include <QObject>
#include <QString>

class Folders : public QObject {
  Q_OBJECT

public:
  Folders(QObject* parent = nullptr);

public slots:
  static QString appDir();
  static QString appData();
  static QString documents();
  static QString temp();
  static QString downloads();
  static QString finish(QString path);
};
