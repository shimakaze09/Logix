//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_TIMEFORMATITEM_HPP
#define LOGIX_FMT_TIMEFORMATITEM_HPP

#include "FormatItem.hpp"
#include <ctime>

namespace Logix {
class TimeFormatItem : public FormatItem {
public:
  TimeFormatItem(const std::string &fmt = "%H:%M:%S")
      : m_timeFmt(fmt.size() == 0 ? "%H:%M:%S" : fmt) {}

  // Override the Format method
  void Format(std::ostream &out, const LogMsg &msg) override {
    struct tm t;
    char buf[32] = {0};
// Use C library functions to format timestamps
#ifdef _WIN32
    localtime_s(&t, &msg.m_ctime);
#else
    localtime_r(&msg.m_ctime, &t);
#endif
    strftime(buf, sizeof(buf), m_timeFmt.c_str(), &t);
    // Output the formatted timestamp to the stream
    out << buf;
  }

private:
  std::string m_timeFmt;
};
} // namespace Logix

#endif // LOGIX_FMT_TIMEFORMATITEM_HPP
