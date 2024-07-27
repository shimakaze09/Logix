//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_TABFORMATITEM_HPP
#define LOGIX_FMT_TABFORMATITEM_HPP

#include "FormatItem.hpp"

namespace Logix {
class TabFormatItem : public FormatItem {
public:
  void Format(std::ostream &out, const LogMsg &msg) override {
    // Output a tab character to the stream
    out << '\t';
  }
};
} // namespace Logix

#endif // LOGIX_FMT_TABFORMATITEM_HPP
