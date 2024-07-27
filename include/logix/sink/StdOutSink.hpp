//
// Created by John on 27/07/2024
//

#ifndef LOGIX_STDOUTSINK_HPP
#define LOGIX_STDOUTSINK_HPP

#include "LogSink.hpp"
#include <iostream>

namespace Logix {
class StdOutSink : public LogSink {
public:
  void Log(const char *data, size_t len) override {
    // Write the log to the standard output
    std::cout.write(data, len);
  }
};
} // namespace Logix

#endif // LOGIX_STDOUTSINK_HPP
