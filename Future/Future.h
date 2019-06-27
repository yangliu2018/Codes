#pragma once
#include <mutex>
#include <condition_variable>

enum class FutureStatus {
    ready,
    timeout,
    deferred
};

template <class T>
class Future {
public:
    friend class Promise;
    friend class PackagedTask;

    Future(const Future&) = delete;
    Future& operator= (const Future&) = delete;

    Future() : m_status(FutureStatus::deferred) {}

    T get() {
        wait();
        return m_result;
    }

    void wait() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [&m_status]() { return m_status == FutureStatus::ready; });
    }

private:
    FutureStatus m_status;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    T m_result;
};