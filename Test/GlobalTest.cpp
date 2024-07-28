//
// Created by John on 27/07/2024
//

#include "logix/Logix.hpp"

int main() {
  using namespace Logix;
  USR_DEBUG("%s", "Debug message");
  USR_INFO("%s", "Info message");
  USR_WARN("%s", "Warn message");
  USR_ERROR("%s", "Error message");
  USR_FATAL("%s", "Fatal message");

  size_t count = 0;
  while (count < 30) {
    USR_FATAL("Fatal message %d", count++);
  }

  return 0;
}