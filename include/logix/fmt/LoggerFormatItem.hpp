//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_LOGGERFORMATITEM_HPP
#define LOGIX_FMT_LOGGERFORMATITEM_HPP

#include "FormatItem.hpp"

namespace Logix {
class LoggerFormatItem : public FormatItem {
public:
  void Format(std::ostream &out, const LogMsg &msg) override {
    // Extract the specified field and insert it into the stream
    out << msg.m_logger;
  }
};
} // namespace Logix

#endif // LOGIX_FMT_LOGGERFORMATITEM_HPP