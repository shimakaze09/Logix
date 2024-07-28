//
// Created by John on 27/07/2024
//

#include "logix/tools/Formatter.hpp"

int main() {
  Logix::LogMsg msg;
  msg.m_ctime = Logix::Date::Now();
  msg.m_level = Logix::LogLevel::Level::WARN;
  msg.m_file = "test.cpp";
  msg.m_line = 38;
  msg.m_logger = "Logger";
  msg.m_payload = "Test log message";
  Logix::Formatter formatter("%d{%H:%M:%S}[%p][%c][%f:%l]%T%m%n");
  std::cout << formatter.Format(msg) << std::endl;
  return 0;
}
