//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_NLINEFORMATITEM_HPP
#define LOGIX_FMT_NLINEFORMATITEM_HPP

#include "FormatItem.hpp"

namespace Logix {
class NLineFormatItem : public FormatItem {
public:
  void Format(std::ostream &out, const LogMsg &msg) override {
    // Output a newline character to the stream
    out << '\n';
  }
};
} // namespace Logix

#endif // LOGIX_FMT_NLINEFORMATITEM_HPP
