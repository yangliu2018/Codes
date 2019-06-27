#pragma once

#include "Future.h"

template <class R>
class Promise {
public:
    void set_value(R&& value) {
        std::unique_lock<std::mutex> lock(m_future.m_mutex);
        m_future.m_result = std::forward<R>(value);
        m_future.m_status = FutureStatus::ready;
        lock.unlock();
        m_future.m_cv.notify_all();
    }

    Future<R>& get_future() {
        return m_future;
    }

private:
    Future<R> m_future;
};