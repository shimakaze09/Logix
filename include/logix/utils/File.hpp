//
// Created by John on 27/07/2024
//

#ifndef LOGIX_FILE_HPP
#define LOGIX_FILE_HPP

#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace Logix {
class File {
public:
  static bool IsExist(const std::string &path) {
#ifdef _WIN32
    DWORD fileAttr = GetFileAttributes(path.c_str());
    if (fileAttr == INVALID_FILE_ATTRIBUTES) {
      return false;
    }
    return true;
#else
    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
      return true;
    }
    return false;
#endif
  }

  // Get the directory path where the file is located
  static std::string GetPath(const std::string &path) {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
      return ".";
    } else {
      return path.substr(0, pos + 1);
    }
  }

  // Create directory
  static void CreateDirectory(const std::string &path) {
    if (path.size() == 0)
      return;
    size_t cur = 0, pos = 0;
    std::string parentDir;

    while (cur < path.size()) {
      pos = path.find_first_of("/\\", cur);
      // Intercept the parent path
      parentDir = path.substr(0, pos);
      // The parent path is valid && the directory does not exist
      if ((parentDir.size() != 0) && (!IsExist(parentDir))) {
#ifdef _WIN32
        ::CreateDirectoryA(parentDir.c_str(), NULL);
#else
        mkdir(parentDir.c_str(), 0755);
#endif
      }

      // If pos is equal to the end position, the directory is created
      if (pos == std::string::npos)
        break;
      cur = pos + 1;
    }
  }
};
} // namespace Logix

#endif // LOGIX_FILE_HPP
