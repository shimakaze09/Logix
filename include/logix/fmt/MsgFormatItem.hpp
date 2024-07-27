//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_MSGFORMATITEM_HPP
#define LOGIX_FMT_MSGFORMATITEM_HPP

#include "FormatItem.hpp"

namespace Logix {
class MsgFormatItem : public FormatItem {
public:
  void Format(std::ostream &out, const LogMsg &msg) override {
    // Output the payload to the stream
    out << msg.m_payload;
  }
};
} // namespace Logix

#endif // LOGIX_FMT_MSGFORMATITEM_HPP