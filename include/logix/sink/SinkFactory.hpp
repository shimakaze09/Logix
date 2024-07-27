//
// Created by John on 27/07/2024
//

#ifndef LOGIX_SINKFACTORY_HPP
#define LOGIX_SINKFACTORY_HPP

#include "LogSink.hpp"
#include <memory>

namespace Logix {
class SinkFactory {
public:
  template <class SinkType, class... Args>
  static LogSink::ptr Create(Args &&...args) {
    return std::make_shared<SinkType>(std::forward<Args>(args)...);
  }
};
} // namespace Logix

#endif // LOGIX_SINKFACTORY_HPP