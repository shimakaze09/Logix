//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_FILEFORMATITEM_HPP
#define LOGIX_FMT_FILEFORMATITEM_HPP

#include "FormatItem.hpp"

namespace Logix {
class FileFormatItem : public FormatItem {
public:
  void Format(std::ostream &out, const LogMsg &msg) override {
    // Extract the file name and insert it into the stream
    out << msg.m_file;
  }
};
} // namespace Logix

#endif // LOGIX_FMT_FILEFORMATITEM_HPP