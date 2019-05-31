class Strategy
{
public:
    virtual ~Strategy() {}
    virtual void AlgorithmInterface() = 0;
};

class Context
{
public:
    void ContextInterfact() { m_strategy->AlgorithmInterface(); }
private:
    Strategy* m_strategy;
};

class ConcreteStrategyA
{
public:
    virtual void AlgorithmInterface();
};

class ConcreteStrategyB
{
public:
    virtual void AlgorithmInterface();
};