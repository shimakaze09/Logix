//
// Created by John on 28/07/2024
//

#ifndef LOGIX_ASYNCLOPPER_HPP
#define LOGIX_ASYNCLOPPER_HPP

#include "Buffer.hpp"

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>

namespace Logix {
enum class ASYNCTYPE {
  // Async safe type
  ASYNC_SAFE,
  // Async unsafe type
  ASYNC_UNSAFE
};

class AsyncLopper {
public:
  using cb_t = std::function<void(Buffer &)>;
  using ptr = std::shared_ptr<AsyncLopper>;
  AsyncLopper(cb_t callback, ASYNCTYPE type = ASYNCTYPE::ASYNC_SAFE)
      : m_type(type), m_stop(false), m_callback(callback),
        m_td(&AsyncLopper::ThreadEntry, this) {}

  // Push data to the producer buffer
  void Push(const char *data, size_t len) {
    {
      std::unique_lock<std::mutex> ulk(m_mtx_pro_buf);

      if (m_type == ASYNCTYPE::ASYNC_SAFE) {
        m_pro_cv.wait(ulk, [&]() { return m_pro_buf.WritableSize() >= len; });
      }

      m_pro_buf.Push(data, len);
    }

    m_pro_cv.notify_one();
  }

  // Stop the async logger
  void Stop() {
    m_stop = true;
    // Notify the async thread
    m_con_cv.notify_all();
    // recycle the thread
    m_td.join();
  }

  ~AsyncLopper() {
    // Stop the async logger
    Stop();
  }

private:
  // Thread entry function
  void ThreadEntry() {
    while (true) {
      {
        std::unique_lock<std::mutex> ulk(m_mtx_pro_buf);
        m_con_cv.wait(ulk,
                      [&]() { return m_stop || m_pro_buf.ReadableSize() > 0; });

        if (m_stop && m_pro_buf.Empty())
          break;

        m_pro_buf.Swap(m_con_buf);
      }

      if (m_type == ASYNCTYPE::ASYNC_SAFE) {
        m_pro_cv.notify_all();
      }

      m_callback(m_con_buf);
      m_con_buf.Reset();
    }
  }

private:
  // Async logger safety type
  ASYNCTYPE m_type;
  std::atomic<bool> m_stop;
  // Producer buffer mutex
  std::mutex m_mtx_pro_buf;
  // Producer buffer
  Buffer m_pro_buf;
  // Consumer buffer
  Buffer m_con_buf;
  // Producer condition variable
  std::condition_variable m_pro_cv;
  // Consumer condition variable
  std::condition_variable m_con_cv;
  // Async thread object
  std::thread m_td;
  // Callback function
  cb_t m_callback;
};
} // namespace Logix

#endif // LOGIX_ASYNCLOPPER_HPP