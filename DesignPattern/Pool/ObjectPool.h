#pragma once
#include <list>

class Resource {
public:
    Resource(int value = 0) : m_value(value) {}
    void SetValue(int value) { m_value = value; }
    void Reset() { m_value = 0; }
private:
    int m_value;
};

class ObjectPool {
public:
    static ObjectPool* Instance() {
        static ObjectPool pool;
        return &pool;
    }

    Resource* GetResource() {
        Resource* ret = nullptr;
        if (m_objs.empty()) ret = new Resource();
        else {
            ret = m_objs.front();
            m_objs.pop_front();
        }
        return ret;
    }

    void ReturnResource(Resource* object) {
        object->Reset();
        m_objs.push_back(object);
    }

private:
    std::list<Resource*> m_objs;
    ObjectPool() = default;
    ~ObjectPool() {
        for (Resource* obj : m_objs) {
            delete obj;
        }
        m_objs.clear();
    }
};


void Client() {
    ObjectPool* pool = ObjectPool::Instance();
    Resource* r1 = pool->GetResource();
    Resource* r2 = pool->GetResource();
    Resource* r3 = pool->GetResource();
    pool->ReturnResource(r1);
    r1 = nullptr;
    pool->ReturnResource(r2);
    r2 = nullptr;
    Resource* r4 = pool->GetResource();
}