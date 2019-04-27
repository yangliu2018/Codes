#pragma once
#include <mutex>
#include <condition_variable>


class Semaphore
{
public:
    explicit Semaphore(int count = 0): m_count(count) {}

    // V, Verhoog (increment)
    void Signal() {
        std::unique_lock<std::mutex> lock(m_mutex);
        ++m_count;
        m_cv.notify_one();
    }

    // P, Probeer (try)
    void Wait() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this](){ return m_count > 0; });
        --m_count;
    }

private:
    std::mutex m_mutex; // protect m_count
    std::condition_variable m_cv;
    int m_count;
};
