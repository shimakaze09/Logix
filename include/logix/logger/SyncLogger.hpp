//
// Created by John on 28/07/2024.
//

#ifndef LOGIX_SYNCLOGGER_HPP
#define LOGIX_SYNCLOGGER_HPP

#include "Logger.hpp"
#include <mutex>

namespace Logix {
class SyncLogger : public Logger {
public:
  SyncLogger(const std::string logger, LogLevel::Level level,
             Formatter::ptr formatter, std::vector<LogSink::ptr> sinks)
      : Logger(logger, level, formatter, sinks) {}

protected:
  // Sink the log
  void Log(const char *data, size_t len) override {
    std::unique_lock<std::mutex> ulk(m_mtx);
    for (auto &sink : m_sinks) {
      if (sink.get() != nullptr) {
        sink->Log(data, len);
      }
    }
  }
};
} // namespace Logix

#endif // LOGIX_SYNCLOGGER_HPP
