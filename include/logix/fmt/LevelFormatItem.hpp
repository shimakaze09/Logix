//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_LEVELFORMATITEM_HPP
#define LOGIX_FMT_LEVELFORMATITEM_HPP

#include "FormatItem.hpp"

namespace Logix {
class LevelFormatItem : public FormatItem {
public:
  void Format(std::ostream &out, const LogMsg &msg) override {
    // Output the log level to the stream
    out << LogLevel::ToString(msg.m_level);
  }
};
} // namespace Logix

#endif // LOGIX_FMT_LEVELFORMATITEM_HPP
