//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FILESINK_HPP
#define LOGIX_FILESINK_HPP

#include "../utils/File.hpp"
#include "LogSink.hpp"

#include <fstream>
#include <iostream>
#include <stdlib.h>

namespace Logix {
class FileSink : public LogSink {
public:
  FileSink(const std::string &path) : m_path(path) {
    // Check if the path is valid, if not create the file
    if (!File::IsExist(File::GetPath(m_path))) {
      File::CreateDirectory(File::GetPath(m_path));
    }

    // Create and open the file
    m_ofs.open(m_path, std::ios::out | std::ios::app);
    if (!m_ofs.is_open()) {
      std::cerr << "Failed to open file: " << m_path << std::endl;
      abort();
    }
  }

  void Log(const char *data, size_t len) override {
    // Write the log to the file
    m_ofs.write(data, len);
  }

private:
  std::string m_path;
  std::ofstream m_ofs;
};
} // namespace Logix

#endif // LOGIX_FILESINK_HPP