//
// Created by John on 28/07/2024
//

#ifndef LOGIX_LOCALLOGGERBUILDER_HPP
#define LOGIX_LOCALLOGGERBUILDER_HPP

#include "logix/builder/LoggerBuilder.hpp"
#include "logix/logger/Logger.hpp"
#include "logix/logger/SyncLogger.hpp"
#include "logix/sink/SinkFactory.hpp"
#include "logix/sink/StdOutSink.hpp"
#include "logix/tools/Formatter.hpp"

#include <cassert>
#include <memory>

namespace Logix {
class LocalLoggerBuilder : public LoggerBuilder {
public:
  Logger::ptr Build() override {
    assert(!m_loggerName.empty());

    if (m_formatter.get() == nullptr) {
      m_formatter = std::make_shared<Formatter>();
    }

    if (m_sinks.empty()) {
      m_sinks.push_back(SinkFactory::Create<StdOutSink>());
    }

    if (m_loggerType == LoggerType::AsyncLogger) {
      return std::make_shared<AsyncLogger>(m_loggerName, m_level, m_formatter,
                                           m_sinks, m_asyncType);
    }
    
    return std::make_shared<SyncLogger>(m_loggerName, m_level, m_formatter,
                                        m_sinks);
  }
};
} // namespace Logix

#endif // LOGIX_LOCALLOGGERBUILDER_HPP