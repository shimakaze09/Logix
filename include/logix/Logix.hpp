//
// Created by John on 27/07/2024
//

#ifndef LOGIX_HPP
#define LOGIX_HPP

#include "logger/Logger.hpp"
#include "logix/manager/LogManager.hpp"

namespace Logix {
inline const Logger::ptr &GetLogger(const std::string &name) {
  return LogManager::GetInstance().GetLogger(name);
}

inline const Logger::ptr &DefaultLogger() {
  return LogManager::GetInstance().DefaultLogger();
}
} // namespace Logix

#endif // LOGIX_HPP
