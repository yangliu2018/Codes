#pragma once

#include "Future.h"

template <class R, class ...Args>
class PackagedTask<R(Args...)> {
public:
    template <class F>
    explicit PackagedTask(F&& f)
        :m_function(std::forward<F>(f)){}

    void operator() (Args... args) {
        R result = f(args);
        std::unique_lock<std::mutex> lock(m_future.m_mutex);
        m_future.m_result = result;
        m_future.m_status = FutureStatus::ready;
        lock.unlock();
        m_future.m_cv.notify_all();
    }

    Future& get_future() {
        return m_future;
    }

private:
    R(Args...) m_function;
    Future<R> m_future;
};