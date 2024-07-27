//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_THREADFORMATITEM_HPP
#define LOGIX_FMT_THREADFORMATITEM_HPP

#include "FormatItem.hpp"

namespace Logix {
class ThreadFormatItem : public FormatItem {
public:
  void Format(std::ostream &out, const LogMsg &msg) override {
    // Output the thread ID to the stream
    out << msg.m_tid;
  }
};
} // namespace Logix

#endif // LOGIX_FMT_THREADFORMATITEM_HPP
