//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_OTHERFORMATITEM_HPP
#define LOGIX_FMT_OTHERFORMATITEM_HPP

#include "FormatItem.hpp"

namespace Logix {
class OtherFormatItem : public FormatItem {
public:
  OtherFormatItem(const std::string &str) : m_str(str) {}
  void Format(std::ostream &out, const LogMsg &msg) override {
    // Output the string to the stream
    out << m_str;
  }

private:
  std::string m_str;
};
} // namespace Logix

#endif // LOGIX_FMT_OTHERFORMATITEM_HPP
