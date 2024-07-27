//
// Created by John on 28/07/2024
//

#include "logix/Level.hpp"
#include "logix/logger/SyncLogger.hpp"
#include "logix/sink/FileSink.hpp"
#include "logix/sink/LogSink.hpp"
#include "logix/sink/SinkFactory.hpp"
#include "logix/sink/StdOutSink.hpp"

#include <memory>
#include <vector>

int main() {
  using namespace Logix;
  Logix::Formatter::ptr formatter = std::make_shared<Formatter>();

  LogSink::ptr logOut = SinkFactory::Create<StdOutSink>();
  LogSink::ptr logFile = SinkFactory::Create<FileSink>("./logfile/log.txt");

  std::vector<LogSink::ptr> sinks = {logOut, logFile};
  std::string logger = "TestLogger";
  SyncLogger slogger(logger, LogLevel::Level::DEBUG, formatter, sinks);

  slogger.Error(__FILE__, __LINE__, "This is an error message");
  return 0;
}
