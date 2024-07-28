//
// Created by John on 27/07/2024
//

#include "logix/sink/FileSink.hpp"
#include "logix/sink/LogSink.hpp"
#include "logix/sink/RollBySizeSink.hpp"
#include "logix/sink/SinkFactory.hpp"
#include "logix/sink/StdOutSink.hpp"
#include "logix/tools/Formatter.hpp"
#include "logix/tools/Message.hpp"
#include "logix/utils/Date.hpp"

int main() {
  using namespace Logix;
  LogMsg msg;
  msg.m_ctime = Logix::Date::Now();
  msg.m_level = LogLevel::Level::WARN;
  msg.m_file = "test.cpp";
  msg.m_line = 38;
  msg.m_logger = "Logger";
  msg.m_payload = "Test log message";
  Logix::Formatter formatter("%d{%H:%M:%S}[%p][%c][%f:%l]%T%m%n");

  // Generate log
  std::string s = formatter.Format(msg);
  LogSink::ptr logOut = SinkFactory::Create<StdOutSink>();
  LogSink::ptr logFile = SinkFactory::Create<FileSink>("./TestLog/test.log");
  LogSink::ptr logRollFile =
      SinkFactory::Create<RollBySizeSink>("test", 1024 * 1024 * 10);

  // Use the log sinks to output the log message
  logOut->Log(s.c_str(), s.size());
  logFile->Log(s.c_str(), s.size());
  logRollFile->Log(s.c_str(), s.size());
  return 0;
}
