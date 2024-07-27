//
// Created by John on 27/07/2024
//

#ifndef LOGIX_LEVEL_HPP
#define LOGIX_LEVEL_HPP

#include <string>

namespace Logix {
class LogLevel {
public:
  enum class Level { UNKNOWN = 0, DEBUG, INFO, WARN, ERR, FATAL, OFF };

  static std::string ToString(LogLevel::Level level) {
    switch (level) {
    case LogLevel::Level::DEBUG:
      return "DEBUG";
    case LogLevel::Level::INFO:
      return "INFO";
    case LogLevel::Level::WARN:
      return "WARN";
    case LogLevel::Level::ERR:
      return "ERROR";
    case LogLevel::Level::FATAL:
      return "FATAL";
    case LogLevel::Level::OFF:
      return "OFF";
    default:
      break;
    }
    return "UNKNOWN";
  }
};
} // namespace Logix

#endif // LOGIX_LEVEL_HPP
