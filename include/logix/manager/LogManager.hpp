//
// Created by John on 28/07/2024
//

#ifndef LOGIX_LOGMANAGER_HPP
#define LOGIX_LOGMANAGER_HPP

#include "logix/builder/LocalLoggerBuilder.hpp"
#include "logix/builder/LoggerBuilder.hpp"
#include "logix/logger/Logger.hpp"

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace Logix {
class LogManager {
public:
  static LogManager &GetInstance() {
    static LogManager instance;
    return instance;
  }

  void AddLogger(const Logger::ptr &logger) {
    if (HasLogger(logger->GetLogger()))
      return;

    std::unique_lock<std::mutex> ulk(m_mtxLoggers);
    m_loggers[logger->GetLogger()] = logger;
  }

  bool HasLogger(const std::string &loggerName) {
    std::unique_lock<std::mutex> ulk(m_mtxLoggers);
    return m_loggers.find(loggerName) != m_loggers.end();
  }

  const Logger::ptr &DefaultLogger() { return m_defaultLogger; }

  const Logger::ptr &GetLogger(const std::string &loggerName) {
    if (!HasLogger(loggerName))
      return Logger::ptr();
    return m_loggers[loggerName];
  }

private:
  LogManager() {
    std::unique_ptr<LoggerBuilder> builder(new LocalLoggerBuilder());
    builder->BuildName("default");
    m_defaultLogger = builder->Build();
    AddLogger(m_defaultLogger);
  }

  LogManager(const LogManager &) = delete;

private:
  std::mutex m_mtxLoggers;
  // Default logger
  Logger::ptr m_defaultLogger;
  // Logger map
  std::unordered_map<std::string, Logger::ptr> m_loggers;
};
} // namespace Logix

#endif // LOGIX_LOGMANAGER_HPP