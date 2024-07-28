//
// Created by John on 28/07/2024
//

#include "logix/builder/GlobalLoggerBuilder.hpp"
#include "logix/builder/LoggerBuilder.hpp"
#include "logix/logger/Logger.hpp"
#include "logix/manager/LogManager.hpp"
#include "logix/sink/FileSink.hpp"
#include "logix/sink/StdOutSink.hpp"
#include "logix/tools/Level.hpp"


#include <cstddef>
#include <memory>

void LogTest() {
  using namespace Logix;
  Logger::ptr logger = LogManager::GetInstance().GetLogger("asyncLogger");
  logger->Debug(__FILE__, __LINE__, "%s", "Debug message");
  logger->Info(__FILE__, __LINE__, "%s", "Info message");
  logger->Warn(__FILE__, __LINE__, "%s", "Warn message");
  logger->Error(__FILE__, __LINE__, "%s", "Error message");
  logger->Fatal(__FILE__, __LINE__, "%s", "Fatal message");

  size_t count = 0;
  while (count < 300) {
    logger->Fatal(__FILE__, __LINE__, "Fatal message %d", count++);
  }
}

int main() {
  using namespace Logix;

  // Create global logger builder
  std::unique_ptr<Logix::LoggerBuilder> builder(
      new Logix::GlobalLoggerBuilder());

  // Create components
  builder->BuildName("asyncLogger");
  builder->BuildLevel(Logix::LogLevel::Level::WARN);
  builder->BuildFormatter("[%c]%m%n");
  builder->BuildType(Logix::LoggerType::AsyncLogger);
  builder->BuildEnableUnsafe();
  builder->BuildLogSink<FileSink>("./logfile/async.log");
  builder->BuildLogSink<StdOutSink>();

  // Build logger
  builder->Build();
  LogTest();
  return 0;
}
