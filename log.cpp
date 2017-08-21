#include "log.h"
#include "folders.h"
#include <QDir>
#include <QStandardPaths>
#include <iomanip>
#include <QtGlobal>

struct spdlog_init {
  spdlog_init() {
    spdlog::set_pattern("[%L %H:%M:%S.%e] %v");
  }
} spdlog_init_inst;

std::shared_ptr<spdlog::sinks::sink> g_sink;
void Log::set_debug_sink(std::shared_ptr<spdlog::sinks::sink> sink) {
  g_sink = sink;
}

std::shared_ptr<spdlog::logger> Log::console() {
  static std::shared_ptr<spdlog::logger> logger;
  if (!logger) {
    if (g_sink) {
      logger = std::make_shared<spdlog::logger>("console", g_sink);
      // a bug with spdlog, need to set format again
      logger->set_pattern("[%L %H:%M:%S.%e] %v");
    } else {
      logger = spdlog::stdout_color_mt("console");
    }
    logger->set_level(spdlog::level::trace);
    logger->info("============= console logger created =============");
  }
  return logger;
}

std::shared_ptr<spdlog::logger> Log::file() {
  static QString path = Folders::appData();
  static std::shared_ptr<spdlog::logger> logger;
  if (!logger) {
    logger = spdlog::rotating_logger_mt("file", qPrintable(path + "log.txt"),
                                        1024 * 1024 * 1, 0);
    logger->info("================= logger created =================");
  }
  return logger;
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
