#include "log.h"
#include "folders.h"
#include <QDir>
#include <QStandardPaths>
#include <iomanip>

#include <QtGlobal>
#ifdef Q_OS_ANDROID
#include <QDebug>
#include <spdlog/sinks/sink.h>
class QDebugSink : public spdlog::sinks::sink {
  void log(const spdlog::details::log_msg& msg) override {
    qDebug() << QString::fromStdString(msg.formatted.str());
  }
  void flush() {
  }
};
#endif

QLog* g_qlog = nullptr;

std::shared_ptr<spdlog::logger> Log::console() {
  static std::shared_ptr<spdlog::logger> logger;
  if (!logger) {
#ifdef Q_OS_ANDROID
    auto sink = std::make_shared<QDebugSink>();
    logger = std::make_shared<spdlog::logger>("console", sink);
#else
    logger = spdlog::stdout_color_mt("console");
#endif
    logger->set_level(spdlog::level::trace);
  }
  return logger;
}

std::shared_ptr<spdlog::logger> Log::file() {
  static QString path = Folders::appData();
  static auto logger =
      spdlog::rotating_logger_mt("file", qPrintable(path + "log.txt"), 1024 * 1024 * 1, 1);
  return logger;
}

void Log::showIndicator() {
  Log::info("{}: {}", __PRETTY_FUNCTION__, (void*)g_qlog);
  if (g_qlog) {
    g_qlog->showIndicator(true);
  }
}

std::ostream& operator<<(std::ostream& stream, const QString& str) {
  stream << str.toStdString();
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const QByteArray& ba) {
  for (uint16_t b : ba) {
    b &= 0xFF;
    stream << std::hex << std::setw(2) << std::setfill('0') << b;
  }
  stream << "(" << ba.size() << ")";
  return stream;
}

QLog::QLog(QObject* parent)
  : QObject(parent) {
}

void QLog::error(const QString& error) {
  Log::error(error.toStdString());
}

void QLog::info(const QString& info) {
  Log::info(info.toStdString());
}
