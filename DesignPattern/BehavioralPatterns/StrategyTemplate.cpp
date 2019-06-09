#include <iostream>
#define PRINT_MESSAGE(msg)  std::cout << (msg) << std::endl
#define PRINT_FUNCTION()    PRINT_MESSAGE(__FUNCTION__)
#define PRINT_LINE()        PRINT_MESSAGE("")

template <class Strategy>
class Context {
public:
    void Operate() { 
        PRINT_FUNCTION();
        m_strategy.Algorithm(); 
    }
private:
    Strategy m_strategy;
};

class MyStrategy {
public:
    void Algorithm() {
        PRINT_FUNCTION();
    }
};

void Client() {
    Context<MyStrategy> context;
    context.Operate();
}

int main() {
    Client();
    return 0;
}