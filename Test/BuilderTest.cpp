//
// Created by John on 28/07/2024
//

#include "logix/builder/LocalLoggerBuilder.hpp"
#include "logix/builder/LoggerBuilder.hpp"
#include "logix/logger/Logger.hpp"

int main() {
  using namespace Logix;
  Logix::LocalLoggerBuilder localBuilder;
  localBuilder.BuildName("LocalLogger");
  localBuilder.BuildType(LoggerType::SyncLogger);
  Logger::ptr logger = localBuilder.Build();

  logger->Error(__FILE__, __LINE__, "This is the test for builder pattern");
  return 0;
}