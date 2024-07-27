//
// Created by John on 27/07/2024
//

#ifndef LOGIX_LOGSINK_HPP
#define LOGIX_LOGSINK_HPP

#include <memory>

namespace Logix {
class LogSink {
public:
  using ptr = std::shared_ptr<LogSink>;
  // Log output interface, data is the actual address of the log, len is the
  // length of the log
  virtual void Log(const char *data, size_t len) = 0;
  virtual ~LogSink() = default;
};
} // namespace Logix

#endif // LOGIX_LOGSINK_HPP