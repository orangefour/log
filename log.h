#pragma once
#include <QObject>
#include <QByteArray>
#include <QString>
#include <ostream>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wshadow"
#endif

#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

class Log {
public:
  template <typename... Args>
  static void error(const Args&... args) {
    logger()->error(args...);
  }

  template <typename... Args>
  static void info(const Args&... args) {
    logger()->info(args...);
  }

  template <typename... Args>
  static void debug(const Args&... args) {
    logger()->debug(args...);
  }

  static void flush();

private:
  static std::shared_ptr<spdlog::logger> logger();
};

class QQmlEngine;
class QJSEngine;

class QLog : public QObject {
  Q_OBJECT
public:
  QLog(QObject* parent = nullptr);

public slots:
  void error(const QString& str);
  void info(const QString& str);
  void debug(const QString& str);
  void flush();
};

std::ostream& operator<<(std::ostream& stream, const QString& str);

template <>
struct fmt::formatter<QByteArray> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx) -> decltype(ctx.begin()) {
    for (auto it = ctx.begin(); it != ctx.end(); ++it) {
      if (*it == '}') {
        return it;
      }
    }
    throw format_error("invalid format");
  }
  template <typename FormatContext>
  auto format(const QByteArray& ba, FormatContext& ctx) -> decltype(ctx.out()) {
    QString qs = ba.toHex();
    return format_to(ctx.out(), "{}({})", qs, ba.size());
  }
};
