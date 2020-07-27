#include "log.h"
#include "folders.h"
#include <QDir>
#include <QStandardPaths>
#include <QtGlobal>
#include <iomanip>

#include <spdlog/async.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/android_sink.h>

std::ostream& operator<<(std::ostream& stream, const QString& str) {
  stream << str.toStdString();
  return stream;
}

void Log::flush() {
  logger()->flush();
}

std::shared_ptr<spdlog::logger> Log::logger() {
  static std::shared_ptr<spdlog::logger> logger;
  if (!logger) {
    std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks;

    auto sink = std::make_shared<spdlog::sinks::
#ifdef __ANDROID__
    android_sink_mt>("metr.at"
#else
    stdout_color_sink_mt>(
#endif
    );
    sinks.push_back(sink);

    QString path = Folders::documents() + "log.txt";
    auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink<
        std::mutex, spdlog::sinks::daily_filename_calculator>>(
        qPrintable(path), 0, 0);
    sinks.push_back(daily_sink);

    spdlog::init_thread_pool(8192, 1);
    logger = std::make_shared<spdlog::async_logger>("metrlogger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    logger->set_pattern("[%L %H:%M:%S.%e] %v");
    logger->set_level(spdlog::level::
#ifdef NDEBUG
    info
#else
    trace
#endif
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
