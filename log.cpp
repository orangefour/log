#include "log.h"
#include "folders.h"
#include <QDir>
#include <QStandardPaths>
#include <QtGlobal>
#include <iomanip>

#include <spdlog/sinks/file_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>
#include <spdlog/sinks/android_sink.h>
#include <spdlog/async_logger.h>

std::ostream& operator<<(std::ostream& stream, const QString& str) {
  stream << str.toStdString();
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const QByteArray& ba) {
  stream << QString(ba.toHex());
  return stream;
}

void Log::flush() {
  logger()->flush();
}

void Log::enableDebug(bool enable) {
  logger()->set_level(enable ? spdlog::level::trace : spdlog::level::info);
}

std::shared_ptr<spdlog::logger> Log::logger() {
  static std::shared_ptr<spdlog::logger> logger;
  if (!logger) {
    std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks;

    auto sink = std::make_shared<spdlog::sinks::
#ifdef __ANDROID__
    android_sink>("metr.at"
#else
    ansicolor_stdout_sink_mt>(
#endif
    );
    sinks.push_back(sink);

    QString path = Folders::documents() + "log.txt";
    auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink<std::mutex, spdlog::sinks::dateonly_daily_file_name_calculator>>(
        qPrintable(path), 0, 0);
    sinks.push_back(daily_sink);

    logger = std::make_shared<spdlog::async_logger>("metrlogger", sinks.begin(), sinks.end(), 1024);
    logger->set_pattern("[%L %H:%M:%S.%e] %v");
    logger->set_level(spdlog::level::
//#ifdef NDEBUG
    info
// #else
//     trace
// #endif
    );
  }
  return logger;
}

QLog::QLog(QObject* parent)
  : QObject(parent) {
}

void QLog::error(const QString& str) {
  Log::error(str.toStdString());
}

void QLog::info(const QString& str) {
  Log::info(str.toStdString());
}

void QLog::debug(const QString& str) {
  Log::debug(str.toStdString());
}

void QLog::flush() {
  Log::flush();
}

void QLog::enableDebug(bool enable) {
  Log::enableDebug(enable);
}
