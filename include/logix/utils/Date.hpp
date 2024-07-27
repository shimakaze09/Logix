//
// Created by John on 27/07/2024
//

#ifndef LOGIX_DATE_HPP
#define LOGIX_DATE_HPP

#include <ctime>
#include <iostream>

namespace Logix {
class Date {
public:
  // Get time
  static time_t Now() { return time(nullptr); }

  // Get time structure
  static struct tm GetTimeSet() {
    struct tm t;
    time_t timeStamp = Date::Now();
#ifdef _WIN32
    localtime_s(&t, &timeStamp);
#else
    localtime_r(&timeStamp, &t);
#endif
    return t;
  }
};
} // namespace Logix

#endif // LOGIX_DATE_HPP