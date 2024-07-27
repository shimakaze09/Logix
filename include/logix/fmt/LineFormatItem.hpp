//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_LINEFORMATITEM_HPP
#define LOGIX_FMT_LINEFORMATITEM_HPP

#include "FormatItem.hpp"

namespace Logix {
class LineFormatItem : public FormatItem {
public:
  void Format(std::ostream &out, const LogMsg &msg) override {
    // Output the line number to the stream
    out << msg.m_line;
  }
};
} // namespace Logix

#endif // LOGIX_FMT_LINEFORMATITEM_HPP
