//
// Created by John on 28/07/2024
//

#ifndef LOGIX_LOGGERBUILDER_HPP
#define LOGIX_LOGGERBUILDER_HPP

#include "logix/logger/AsyncLogger.hpp"
#include "logix/logger/Logger.hpp"
#include "logix/sink/LogSink.hpp"
#include "logix/sink/SinkFactory.hpp"
#include "logix/tools/Formatter.hpp"
#include "logix/tools/Level.hpp"

#include <memory>
#include <utility>
#include <vector>

namespace Logix {
enum class LoggerType { SyncLogger, AsyncLogger };

class LoggerBuilder {
public:
  LoggerBuilder()
      : m_loggerType(LoggerType::AsyncLogger), m_level(LogLevel::Level::DEBUG),
        m_asyncType(ASYNCTYPE::ASYNC_SAFE) {}

  void BuildEnableUnsafe() { m_asyncType = ASYNCTYPE::ASYNC_UNSAFE; }

  void BuildType(LoggerType loggerType = LoggerType::AsyncLogger) {
    m_loggerType = loggerType;
  }

  void BuildName(const std::string &loggerName) { m_loggerName = loggerName; }

  void BuildLevel(LogLevel::Level level) { m_level = level; }

  void BuildFormatter(
      const std::string &pattern = "[%d{%H:%M:%S}][%p][%c][%t][%f:%l]%T%m%n") {
    m_formatter = std::make_shared<Formatter>(pattern);
  }

  template <class SinkType, class... Args> void BuildLogSink(Args &&...args) {
    LogSink::ptr sink =
        SinkFactory::Create<SinkType>(std::forward<Args>(args)...);
    m_sinks.push_back(sink);
  }

  virtual Logger::ptr Build() = 0;

protected:
  LoggerType m_loggerType;
  LogLevel::Level m_level;
  ASYNCTYPE m_asyncType;
  std::string m_loggerName;
  Formatter::ptr m_formatter;
  std::vector<LogSink::ptr> m_sinks;
};
} // namespace Logix

#endif // LOGIX_LOGGERBUILDER_HPP