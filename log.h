#pragma once
#include <QByteArray>
#include <QObject>
#include <QString>
#include <ostream>

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

struct unused {
  template <typename... Args>
  unused(Args const&...) {
  }
};

class Log {
public:
  template <typename... Args>
  static void error(const Args&... args) {
    console()->error(args...);
    file()->error(args...);
    file()->flush();
  }

  template <typename... Args>
  static void info(const Args&... args) {
    console()->info(args...);
    file()->info(args...);
    file()->flush();
  }

  template <typename... Args>
  static void debug(const Args&... args) {
#ifndef NDEBUG
    console()->debug(args...);
    file()->debug(args...);
    file()->flush();
#else
    unused{args...};
#endif
  }

private:
  static std::shared_ptr<spdlog::logger> console();
  static std::shared_ptr<spdlog::logger> file();
};

std::ostream& operator<<(std::ostream& stream, const QString& str);
std::ostream& operator<<(std::ostream& stream, const QByteArray& ba);

class QQmlEngine;
class QJSEngine;

class QLog : public QObject {
  Q_OBJECT
public:
  QLog(QObject* parent = nullptr);

public slots:
  void error(const QString& str);
  void info(const QString& str);
};

namespace fmt {
namespace internal {
FMT_DISABLE_CONVERSION_TO_INT(QByteArray);
}
} // namespace fmt
