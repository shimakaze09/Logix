//
// Created by John on 29/07/2024
//

#include "TestMacro.hpp"
#include "logix/Logix.hpp"
#include "logix/builder/GlobalLoggerBuilder.hpp"
#include "logix/builder/LoggerBuilder.hpp"
#include "logix/logger/Logger.hpp"
#include "logix/sink/FileSink.hpp"
#include "logix/tools/Level.hpp"

#include <chrono>
#include <cstddef>
#include <string>
#include <thread>
#include <vector>

/// @brief Performance test interface
/// @param logName The name of the logger
/// @param threadNum The number of threads
/// @param logNum The number of logs
/// @param logSize The size of each log
void Bench(const std::string &logName, size_t threadNum, size_t logNum,
           size_t logSize) {
  // Get the logger
  Logix::Logger::ptr logger = Logix::GetLogger(logName);
  if (logger.get() == nullptr) {
    return;
  }

  // Create log messages
  std::string msg(logSize - 1, 'A');
  size_t thrPerNum = logNum / threadNum;
  std::cout << "Total logs: " << logNum << std::endl;
  std::cout << "Size of each log: " << logSize << std::endl;
  std::cout << "Number of threads: " << threadNum << std::endl;
  std::cout << "Logs per thread: " << thrPerNum << std::endl;
  std::cout << "-----------------------------------" << std::endl;

  // Create threads
  std::vector<std::thread> threadPool;
  std::vector<double> cost(threadNum);
  for (size_t i = 0; i < threadNum; ++i) {
    threadPool.emplace_back([&, i]() {
      auto begin = std::chrono::high_resolution_clock::now();

      for (int j = 0; j < thrPerNum; ++j) {
        logger->LOG_FATAL("%s\n", msg.c_str());
      }

      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> timeSpan = end - begin;

      cost[i] = timeSpan.count();
      std::cout << "Thread " << i << " cost " << cost[i] << " seconds"
                << std::endl;
    });
  }

  // Recycle threads
  for (int i = 0; i < threadNum; ++i) {
    threadPool[i].join();
  }

  double maxTime = cost[0];
  for (size_t i = 1; i < threadNum; ++i) {
    maxTime = cost[i] > maxTime ? cost[i] : maxTime;
  }

  size_t numPerSec = logNum / maxTime;
  size_t sizePerSec = (logNum * logSize) / (maxTime * 1024);

  // Output the result
  std::cout << "-----------------------------------" << std::endl;
  std::cout << "Max time: " << maxTime << " seconds" << std::endl;
  std::cout << "Logs per second: " << numPerSec << std::endl;
  std::cout << "Size per second: " << sizePerSec << " KB" << std::endl;
}

/// @brief Sync logger performance test
/// @param threadNum The number of threads
void SyncBench(size_t threadNum = 1) {
  Logix::GlobalLoggerBuilder builder;
  builder.BuildName("SyncLogger");
  builder.BuildType(Logix::LoggerType::SyncLogger);
  builder.BuildLevel(Logix::LogLevel::Level::DEBUG);
  builder.BuildFormatter("%m");

  builder.BuildLogSink<Logix::FileSink>("./logfile/sync.log");
  builder.Build();
  Bench("SyncLogger", threadNum, 100, 100);
}

/// @brief Async logger performance test
/// @param threadNum The number of threads
void AsyncBench(size_t threadNum = 1) {
  Logix::GlobalLoggerBuilder builder;
  builder.BuildName("AsyncLogger");
  builder.BuildType(Logix::LoggerType::AsyncLogger);
  builder.BuildLevel(Logix::LogLevel::Level::DEBUG);
  builder.BuildFormatter("%m");

  builder.BuildLogSink<Logix::FileSink>("./logfile/async.log");
  builder.Build();
  Bench("AsyncLogger", threadNum, 100, 100);
}

int main() {
  SyncBench(1);
//   AsyncBench(1);
//   SyncBench(4);
//   AsyncBench(4);
  return 0;
}
