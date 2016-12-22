#pragma once
#include <QObject>
#include <QString>

class Folders : public QObject {
  Q_OBJECT

public:
  Folders(QObject* parent = nullptr);

public slots:
  static QString appData();
  static QString temp();
  static QString downloads();

private:
  static QString finish(QString path);
};
