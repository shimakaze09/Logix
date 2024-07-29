//
// Created by John on 29/07/2024
//

#include "logix/Logix.hpp"

namespace Logix {
#define LOG_DEBUG(fmt, ...) Debug(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) Info(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) Warn(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) Error(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) Fatal(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define USR_DEBUG(fmt, ...)                                                    \
  Logix::DefaultLogger()->LOG_DEBUG(fmt, ##__VA_ARGS__)
#define USR_INFO(fmt, ...) Logix::DefaultLogger()->LOG_INFO(fmt, ##__VA_ARGS__)
#define USR_WARN(fmt, ...) Logix::DefaultLogger()->LOG_WARN(fmt, ##__VA_ARGS__)
#define USR_ERROR(fmt, ...)                                                    \
  Logix::DefaultLogger()->LOG_ERROR(fmt, ##__VA_ARGS__)
#define USR_FATAL(fmt, ...)                                                    \
  Logix::DefaultLogger()->LOG_FATAL(fmt, ##__VA_ARGS__)
} // namespace Logix