//
// Created by John on 27/07/2024
//

#ifndef LOGIX_MESSAGE_HPP
#define LOGIX_MESSAGE_HPP

#include "Level.hpp"
#include "logix/utils/Date.hpp"
#include "logix/utils/File.hpp"
#include <ctime>
#include <string>
#include <thread>

namespace Logix {
struct LogMsg {
  time_t m_ctime;          // Time stamp
  LogLevel::Level m_level; // Log level
  std::string m_logger;    // Logger name
  std::thread::id m_tid;   // Thread ID
  std::string m_file;      // Source file name
  size_t m_line;           // Source file line number
  std::string m_payload;   // Payload

  LogMsg() {}

  LogMsg(LogLevel::Level level, const std::string &logger,
         const std::string file, size_t line, const std::string payload)
      : m_ctime(Date::Now()) // Get the log time when creating logMsg
        ,
        m_level(level), m_logger(logger),
        m_tid(std::this_thread::get_id()) // Get the thread ID when creating
                                          // logMsg
        ,
        m_file(file), m_line(line), m_payload(payload) {}
};
} // namespace Logix

#endif // LOGIX_MESSAGE_HPP
