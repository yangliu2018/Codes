#include <iostream>
#define PRINT_MESSAGE(msg)  std::cout << (msg) << std::endl
#define PRINT_FUNCTION()    PRINT_MESSAGE(__FUNCTION__)
#define PRINT_LINE()        PRINT_MESSAGE("")

class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual void AlgorithmInterface() = 0;
};

class Context
{
public:
    Context(Strategy* strategy) : m_strategy(strategy) {}
    void ContextInterface() {
        PRINT_FUNCTION();
        m_strategy->AlgorithmInterface(); 
    }
private:
    Strategy* m_strategy;
};

class ConcreteStrategyA : public Strategy
{
public:
    virtual void AlgorithmInterface() override {
        PRINT_FUNCTION();
    }
};

class ConcreteStrategyB : public Strategy
{
public:
    virtual void AlgorithmInterface() override {
        PRINT_FUNCTION();
    }
};

void Client()
{
    Context(&ConcreteStrategyA()).ContextInterface();
    PRINT_LINE();
    Context(&ConcreteStrategyB()).ContextInterface();
}

int main()
{
    Client();
    return 0;
}