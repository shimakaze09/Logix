//
// Created by John on 28/07/2024
//

#ifndef LOGIX_GLOBALLOGGERBUILDER_HPP
#define LOGIX_GLOBALLOGGERBUILDER_HPP

#include "logix/builder/LoggerBuilder.hpp"
#include "logix/logger/AsyncLogger.hpp"
#include "logix/logger/Logger.hpp"
#include "logix/logger/SyncLogger.hpp"
#include "logix/manager/LogManager.hpp"
#include "logix/sink/SinkFactory.hpp"
#include "logix/sink/StdOutSink.hpp"


#include <cassert>
#include <memory>

namespace Logix {
class GlobalLoggerBuilder : public LoggerBuilder {
public:
  Logger::ptr Build() override {
    assert(!m_loggerName.empty());
    if (m_formatter.get() == nullptr) {
      m_formatter = std::make_shared<Formatter>();
    }

    if (m_sinks.empty()) {
      m_sinks.push_back(SinkFactory::Create<StdOutSink>());
    }

    Logger::ptr logger;
    if (m_loggerType == LoggerType::AsyncLogger) {
      logger = std::make_shared<AsyncLogger>(m_loggerName, m_level, m_formatter,
                                             m_sinks, m_asyncType);
    } else {
      logger = std::make_shared<SyncLogger>(m_loggerName, m_level, m_formatter,
                                            m_sinks);
    }

    LogManager::GetInstance().AddLogger(logger);
    return logger;
  }
};
} // namespace Logix

#endif // LOGIX_GLOBALLOGGERBUILDER_HPP