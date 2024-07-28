//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FORMATTER_HPP
#define LOGIX_FORMATTER_HPP

#include "Message.hpp"
#include "logix/fmt/FileFormatItem.hpp"
#include "logix/fmt/FormatItem.hpp"
#include "logix/fmt/LevelFormatItem.hpp"
#include "logix/fmt/LineFormatItem.hpp"
#include "logix/fmt/LoggerFormatItem.hpp"
#include "logix/fmt/MsgFormatItem.hpp"
#include "logix/fmt/NLineFormatItem.hpp"
#include "logix/fmt/OtherFormatItem.hpp"
#include "logix/fmt/TabFormatItem.hpp"
#include "logix/fmt/ThreadFormatItem.hpp"
#include "logix/fmt/TimeFormatItem.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Logix {
class Formatter {
public:
  using ptr = std::shared_ptr<Formatter>;
  Formatter(const std::string &pattern =
                "[%d{%H:%M:%S}] [%p] [%c] [%t] [%f:%l]%T%m%n")
      : m_pattern(pattern) {
    // The parsing must be successful during construction
    // otherwise the log will not be output in any way
    assert(ParsePattern());
  }

  // Output the log to the specified stream
  void Format(std::ostream &out, const LogMsg &msg) {
    // Output the log according to the format
    for (auto &it : m_items) {
      it->Format(out, msg);
    }
  }

  // Return the log as string
  std::string Format(const LogMsg &msg) {
    std::stringstream ss;
    Format(ss, msg);
    return ss.str();
  }

private:
  // Parse the formatted string and fill the items array
  bool ParsePattern() {
    // Valid formatting character set
    std::unordered_set<char> fmtSet = {'d', 'p', 'c', 't', 'f',
                                       'l', 'm', 'T', 'n'};

    // The order in which formatting characters are stored
    // The first parameter of the pair is the formatting character, and the
    // second parameter is the corresponding parameter when creating the
    // formatting sub-item.
    std::vector<std::pair<std::string, std::string>> fmtOrder;

    std::string key, val;

    // String processing position
    size_t pos = 0;

    // When pos is out of bounds, it means pattern parsing is complete
    while (pos < m_pattern.size()) {
      // When processing raw strings, format characters all start with %.
      if (m_pattern[pos] != '%') {
        // The original string only has val, no key
        val.push_back(m_pattern[pos++]);
        continue;
      }

      // Process and escape %% (the current position must be equal to %)
      if (pos + 1 < m_pattern.size() && m_pattern[pos + 1] == '%') {
        val.push_back('%');
        pos += 2;
        continue;
      }

      // Put the organized original string into fmtOrder
      if (!val.empty()) {
        fmtOrder.push_back(std::make_pair("", val));
        val.clear();
      }

      // Handling formatting characters
      if (pos + 1 > m_pattern.size()) {
        std::cerr << "No formatting characters after %!" << std::endl;
        return false;
      } else {
        auto it = fmtSet.find(m_pattern[pos + 1]);
        if (it != fmtSet.end()) {
          key.push_back(m_pattern[pos + 1]);
          pos += 2;
        } else {
          std::cerr << "Incorrect formatting characters!" << std::endl;
          return false;
        }
      }

      // Process the formatted substring of %d
      if (pos < m_pattern.size() && m_pattern[pos] == '{') {
        size_t endPos = m_pattern.find_first_of('}', pos + 1);
        if (endPos == std::string::npos) {
          std::cerr << "Problem with formatting substring!" << std::endl;
          return false;
        } else {
          val += m_pattern.substr(pos + 1, endPos - pos - 1);
          pos = endPos + 1;
        }
      }
      fmtOrder.push_back(std::make_pair(key, val));
      key.clear();
      val.clear();
    }
    // Initialize the formatted sub-item array using the parsed data
    for (auto &it : fmtOrder) {
      m_items.push_back(CreateItem(it.first, it.second));
    }

    return true;
  }

  // Create different formatting subclasses according to different formatting
  // characters, which are subfunctions of ParsePattern
  FormatItem::ptr CreateItem(const std::string &key, const std::string &val) {
    // Construct a date format sub-item
    if (key == "d")
      return std::make_shared<TimeFormatItem>(val);

    // Construct a log level format sub-item
    if (key == "p")
      return std::make_shared<LevelFormatItem>();

    // Construct logger name format sub-item
    if (key == "c")
      return std::make_shared<LoggerFormatItem>();

    // Construct thread id format sub-item
    if (key == "t")
      return std::make_shared<ThreadFormatItem>();

    // Construct file name format sub-item
    if (key == "f")
      return std::make_shared<FileFormatItem>();

    // Construct line number formatting sub-item
    if (key == "l")
      return std::make_shared<LineFormatItem>();

    // Construct log message format sub-item
    if (key == "m")
      return std::make_shared<MsgFormatItem>();

    // Construct indent formatting subitem
    if (key == "T")
      return std::make_shared<TabFormatItem>();

    // Construct newline formatting subitem
    if (key == "n")
      return std::make_shared<NLineFormatItem>();

    // If there is no matching formatting character
    // construct other formatting sub-items
    return std::make_shared<OtherFormatItem>(val);
  }

private:
  // The formatted string
  std::string m_pattern;

  // The array of formatting items
  std::vector<FormatItem::ptr> m_items;
};
} // namespace Logix

#endif // LOGIX_FORMATTER_HPP
