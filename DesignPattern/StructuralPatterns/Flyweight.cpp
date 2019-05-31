#include <unordered_map>

class Flyweight {
public:
    virtual void Operation() = 0;
};

class ConcreteFlyweight : public Flyweight {
public:
    virtual void Operation();
private:
    static int m_state;
};

class UnsharedConcreteFlyweight : public Flyweight {
public:
    virtual void Operation();
private:
    int m_state;
};

class FlyweightFactory
{
public:
    Flyweight* GetFlyweight(int key) {
        if (m_pFlyweights.find(key) == m_pFlyweights.end()) {
            m_pFlyweights[key] = new ConcreteFlyweight();
        }
        return m_pFlyweights[key];
    }
private:
    std::unordered_map<int, Flyweight*> m_pFlyweights;
};

void Client()
{
    int key = 0;
    FlyweightFactory factory;
    Flyweight* flyweight1 = factory.GetFlyweight(key);
    Flyweight* flyweight2 = factory.GetFlyweight(key);
}