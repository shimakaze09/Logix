//
// Created by John on 28/07/2024
//

#ifndef LOGIX_LOGGER_HPP
#define LOGIX_LOGGER_HPP

#include "logix/sink/LogSink.hpp"
#include "logix/tools/Formatter.hpp"
#include "logix/tools/Level.hpp"
#include "logix/tools/Message.hpp"

#include <cstdarg>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <stdio.h>
#include <vector>

namespace Logix {
class Logger {
public:
  using ptr = std::shared_ptr<Logger>;
  Logger(const std::string logger, LogLevel::Level level,
         Formatter::ptr formatter, std::vector<LogSink::ptr> sinks)
      : m_logger(logger), m_limitLevel(level), m_formatter(formatter),
        m_sinks(sinks) {}

  // Log at info level
  void Info(const std::string &file, size_t line, const char *fmt, ...) {
    // Check if the message can be logged
    if (LogLevel::Level::INFO < m_limitLevel) {
      return;
    }

    // Format the message
    va_list ap;
    va_start(ap, fmt);
    char *payload = nullptr;
#ifdef _WIN32
    va_list ap_copy;
    va_copy(ap_copy, ap);
    int size = _vscprintf(fmt, ap_copy) + 1;
    va_end(ap_copy);
    payload = (char *)malloc(size);
    if (payload == nullptr) {
      perror("malloc failed");
      va_end(ap);
      return;
    }
    vsnprintf(payload, size, fmt, ap);
#else
    if (vasprintf(&payload, fmt, ap) == -1) {
      perror("vasprintf failed");
      va_end(ap);
      return;
    }
#endif
    va_end(ap);

    // Log message structure
    LogMsg msg(LogLevel::Level::INFO, m_logger, file, line,
               std::string(payload));
    // Log message
    std::string logMessage = m_formatter->Format(msg);
    // Sink the message
    Log(logMessage.c_str(), logMessage.size());
    free(payload);
  }

  // Log at debug level
  void Debug(const std::string &file, size_t line, const char *fmt, ...) {
    // Check if the message can be logged
    if (LogLevel::Level::DEBUG < m_limitLevel) {
      return;
    }

    // Format the message
    va_list ap;
    va_start(ap, fmt);
    char *payload = nullptr;
#ifdef _WIN32
    va_list ap_copy;
    va_copy(ap_copy, ap);
    int size = _vscprintf(fmt, ap_copy) + 1;
    va_end(ap_copy);
    payload = (char *)malloc(size);
    if (payload == nullptr) {
      perror("malloc failed");
      va_end(ap);
      return;
    }
    vsnprintf(payload, size, fmt, ap);
#else
    if (vasprintf(&payload, fmt, ap) == -1) {
      perror("vasprintf failed");
      va_end(ap);
      return;
    }
#endif
    va_end(ap);

    // Log message structure
    LogMsg msg(LogLevel::Level::DEBUG, m_logger, file, line,
               std::string(payload));
    // Log message
    std::string logMessage = m_formatter->Format(msg);
    // Sink the message
    Log(logMessage.c_str(), logMessage.size());
    free(payload);
  }

  // Log at warn level
  void Warn(const std::string &file, size_t line, const char *fmt, ...) {
    // Check if the message can be logged
    if (LogLevel::Level::WARN < m_limitLevel) {
      return;
    }

    // Format the message
    va_list ap;
    va_start(ap, fmt);
    char *payload = nullptr;
#ifdef _WIN32
    va_list ap_copy;
    va_copy(ap_copy, ap);
    int size = _vscprintf(fmt, ap_copy) + 1;
    va_end(ap_copy);
    payload = (char *)malloc(size);
    if (payload == nullptr) {
      perror("malloc failed");
      va_end(ap);
      return;
    }
    vsnprintf(payload, size, fmt, ap);
#else
    if (vasprintf(&payload, fmt, ap) == -1) {
      perror("vasprintf failed");
      va_end(ap);
      return;
    }
#endif
    va_end(ap);

    // Log message structure
    LogMsg msg(LogLevel::Level::WARN, m_logger, file, line,
               std::string(payload));
    // Log message
    std::string logMessage = m_formatter->Format(msg);
    // Sink the message
    Log(logMessage.c_str(), logMessage.size());
    free(payload);
  }

  // Log at error level
  void Error(const std::string &file, size_t line, const char *fmt, ...) {
    // Check if the message can be logged
    if (LogLevel::Level::ERR < m_limitLevel) {
      return;
    }

    // Format the message
    va_list ap;
    va_start(ap, fmt);
    char *payload = nullptr;
#ifdef _WIN32
    va_list ap_copy;
    va_copy(ap_copy, ap);
    int size = _vscprintf(fmt, ap_copy) + 1;
    va_end(ap_copy);
    payload = (char *)malloc(size);
    if (payload == nullptr) {
      perror("malloc failed");
      va_end(ap);
      return;
    }
    vsnprintf(payload, size, fmt, ap);
#else
    if (vasprintf(&payload, fmt, ap) == -1) {
      perror("vasprintf failed");
      va_end(ap);
      return;
    }
#endif
    va_end(ap);

    // Log message structure
    LogMsg msg(LogLevel::Level::ERR, m_logger, file, line,
               std::string(payload));
    // Log message
    std::string logMessage = m_formatter->Format(msg);
    // Sink the message
    Log(logMessage.c_str(), logMessage.size());
    free(payload);
  }

  // Log at fatal level
  void Fatal(const std::string &file, size_t line, const char *fmt, ...) {
    // Check if the message can be logged
    if (LogLevel::Level::FATAL < m_limitLevel) {
      return;
    }

    // Format the message
    va_list ap;
    va_start(ap, fmt);
    char *payload = nullptr;
#ifdef _WIN32
    va_list ap_copy;
    va_copy(ap_copy, ap);
    int size = _vscprintf(fmt, ap_copy) + 1;
    va_end(ap_copy);
    payload = (char *)malloc(size);
    if (payload == nullptr) {
      perror("malloc failed");
      va_end(ap);
      return;
    }
    vsnprintf(payload, size, fmt, ap);
#else
    if (vasprintf(&payload, fmt, ap) == -1) {
      perror("vasprintf failed");
      va_end(ap);
      return;
    }
#endif
    va_end(ap);

    // Log message structure
    LogMsg msg(LogLevel::Level::FATAL, m_logger, file, line,
               std::string(payload));
    // Log message
    std::string logMessage = m_formatter->Format(msg);
    // Sink the message
    Log(logMessage.c_str(), logMessage.size());
    free(payload);
  }

  const inline std::string &GetLogger() const { return m_logger; }

protected:
  virtual void Log(const char *data, size_t len) = 0;

protected:
  std::mutex m_mtx;
  std::string m_logger;
  LogLevel::Level m_limitLevel;
  Formatter::ptr m_formatter;
  std::vector<LogSink::ptr> m_sinks;
};
} // namespace Logix

#endif // LOGIX_LOGGER_HPP