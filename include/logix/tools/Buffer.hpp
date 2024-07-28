//
// Created by John on 28/07/2024
//

#ifndef LOGIX_BUFFER_HPP
#define LOGIX_BUFFER_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

namespace Logix {
// Default buffer size for the buffer
const size_t DEFAULT_BUFFER_SIZE = 1 * 1024 * 1024;

// Threshold for the buffer
const size_t THRESHOLD = 2 * 1024 * 1024;

// Increment size for the buffer
const size_t INCREMENT_SIZE = 1 * 1024 * 1024;

class Buffer {
public:
  Buffer(size_t bufferSize = DEFAULT_BUFFER_SIZE)
      : m_buffer(bufferSize), m_readIndex(0), m_writeIndex(0) {}

  // Push data to the buffer
  void Push(const char *data, size_t len) {
    if (len > WritableSize())
      Resize(len);
    std::copy(data, data + len, &m_buffer[m_writeIndex]);
    MoveWriteIndex(len);
  }

  // Move the read index
  void MoveReadIndex(size_t len) {
    if (len > ReadableSize()) {
      m_readIndex = ReadableSize();
    } else {
      m_readIndex += len;
    }
  }

  // Return the writable size of the buffer
  size_t WritableSize() const { return m_buffer.size() - m_writeIndex; }

  // Return the readable size of the buffer
  size_t ReadableSize() const { return m_writeIndex - m_readIndex; }

  // Return the start address of the buffer
  const char *Start() const { return &m_buffer[m_readIndex]; }

  // Reset the buffer
  void Reset() {
    m_writeIndex = 0;
    m_readIndex = 0;
  }

  // Swap the buffer
  void Swap(Buffer &buf) {
    std::swap(m_writeIndex, buf.m_writeIndex);
    std::swap(m_readIndex, buf.m_readIndex);
    m_buffer.swap(buf.m_buffer);
  }

  bool Empty() const { return m_readIndex == m_writeIndex; }

private:
  // Move the write index
  void MoveWriteIndex(size_t len) {
    assert(m_writeIndex + len <= m_buffer.size());
    m_writeIndex += len;
  }

  // Resize the buffer
  void Resize(size_t len) {
    size_t newSize;

    if (m_buffer.size() < THRESHOLD) {
      newSize = m_buffer.size() * 2 + len;
    } else {
      newSize = m_buffer.size() + INCREMENT_SIZE + len;
    }

    m_buffer.resize(newSize);
  }

private:
  std::vector<char> m_buffer;
  size_t m_readIndex;
  size_t m_writeIndex;
};
} // namespace Logix

#endif // LOGIX_BUFFER_HPP