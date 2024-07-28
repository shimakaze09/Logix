//
// Created by John on 28/07/2024.
//

#ifndef LOGIX_ASYNCLOGGER_HPP
#define LOGIX_ASYNCLOGGER_HPP

#include "Logger.hpp"
#include "logix/tools/AsyncLopper.hpp"
#include <cstddef>

namespace Logix {
class AsyncLogger : public Logger {
public:
  AsyncLogger(const std::string &logger, LogLevel::Level level,
              Formatter::ptr formatter, std::vector<LogSink::ptr> sinks,
              ASYNCTYPE type)
      : Logger(logger, level, formatter, sinks),
        m_lopper(std::bind(&AsyncLogger::RealSink, this, std::placeholders::_1),
                 type) {}

protected:
  void Log(const char *data, size_t len) override { m_lopper.Push(data, len); }

  void RealSink(Buffer &buf) {
    for (auto &sink : m_sinks) {
      if (sink.get() != nullptr) {
        sink->Log(buf.Start(), buf.ReadableSize());
      }
    }
  }

protected:
  // Async lopper
  AsyncLopper m_lopper;
};
} // namespace Logix

#endif // LOGIX_ASYNCLOGGER_HPP
