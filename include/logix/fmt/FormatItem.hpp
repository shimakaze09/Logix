//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FMT_FORMATITEM_HPP
#define LOGIX_FMT_FORMATITEM_HPP

#include "../Message.hpp"
#include <memory>
#include <ostream>

namespace Logix {
class FormatItem {
public:
  using ptr = std::shared_ptr<FormatItem>;
  virtual void Format(std::ostream &out, const LogMsg &msg) = 0;
};
} // namespace Logix

#endif // LOGIX_FMT_FORMATITEM_HPP