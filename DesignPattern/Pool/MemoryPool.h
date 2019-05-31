#pragma once
#include <list>

constexpr auto BUFFER_SIZE = 100;

class MemoryPool {
public:
    static MemoryPool* Instance() {
        static MemoryPool pool;
        return &pool;
    }

    void* GetMemory() {
        void* ret = nullptr;
        if (m_buffers.empty()) ret = std::malloc(BUFFER_SIZE);
        else {
            ret = m_buffers.front();
            m_buffers.pop_front();
        }
        return ret;
    }

    void ReturnMemory(void* buffer) {
        m_buffers.push_back(buffer);
    }

private:
    MemoryPool() = default;
    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;
    ~MemoryPool() {
        for (void* buffer : m_buffers) {
            std::free(buffer);
        }
        m_buffers.clear();
    }
    std::list<void*> m_buffers;
};


#include <iostream>
void Client()
{
    MemoryPool* pool = MemoryPool::Instance();
    void* buffer1 = pool->GetMemory();
    void* buffer2 = pool->GetMemory();
    std::cout << "buffer1: " << buffer1 << std::endl;
    std::cout << "buffer2: " << buffer2 << std::endl;
    pool->ReturnMemory(buffer2);
    buffer2 = nullptr;
    void* buffer3 = pool->GetMemory();
    std::cout << "buffer3: " << buffer3 << std::endl;
    pool->ReturnMemory(buffer1);
    buffer1 = nullptr;
    pool->ReturnMemory(buffer3);
    buffer3 = nullptr;
}