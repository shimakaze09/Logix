//
// Created by John on 27/07/2024
//

#ifndef LOGIX_ROLLBYSIZESINK_HPP
#define LOGIX_ROLLBYSIZESINK_HPP

#include "LogSink.hpp"
#include "logix/utils/Date.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

namespace Logix {
class RollBySizeSink : public LogSink {
public:
  RollBySizeSink(const std::string &baseName, size_t maxSize)
      : m_baseName(baseName), m_maxSize(maxSize), m_currentSize(0),
        m_nameCounter(0) {
    std::string fileName = GetFileName();
    m_ofs.open(fileName, std::ios::out);
    if (!m_ofs.is_open()) {
      std::cerr << "Failed to open file: " << fileName << std::endl;
      abort();
    }
  }

  // Log
  void Log(const char *data, size_t len) override {
    if (m_currentSize + len > m_maxSize) {
      m_ofs.close();

      std::string fileName = GetFileName();
      m_ofs.open(fileName, std::ios::binary | std::ios::app);
      if (m_ofs.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        abort();
      }

      m_currentSize = 0;
    }

    m_ofs.write(data, len);
    m_currentSize += len;
  }

private:
  // Get the file name
  std::string GetFileName() {
    std::stringstream ss;
    struct tm t = Date::GetTimeSet();
    ss << m_baseName;
    ss << "_";
    ss << t.tm_year + 1900;
    ss << t.tm_mon + 1;
    ss << t.tm_mday;
    ss << "_";
    ss << t.tm_hour;
    ss << t.tm_min;
    ss << t.tm_sec;
    ss << "_";
    ss << std::to_string(m_nameCounter++);
    ss << ".log";
    return ss.str();
  }

private:
  std::string m_baseName;
  size_t m_maxSize;
  size_t m_currentSize;
  std::ofstream m_ofs;
  size_t m_nameCounter;
};
} // namespace Logix

#endif // LOGIX_ROLLBYSIZESINK_HPP
