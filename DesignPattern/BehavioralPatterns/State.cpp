#include <iostream>
#define PRINT_MESSAGE(msg)  std::cout << (msg) << std::endl
#define PRINT_FUNCTION()    PRINT_MESSAGE(__FUNCTION__)
#define PRINT_LINE()        PRINT_MESSAGE("")
class State {
public:
    virtual ~State() = default;
    virtual void Handle() = 0;
};

class Context {
public:
    Context(State* state = nullptr) : m_state(state) {}
    void SwitchState(State* state) { m_state = state; }
    void Request() {
        PRINT_FUNCTION();
        m_state->Handle(); 
    }
private:
    State* m_state;
};

class ConcreteStateA : public State {
public:
    virtual void Handle() override {
        PRINT_FUNCTION();
    }
};

class ConcreteStateB : public State {
public:
    virtual void Handle() override {
        PRINT_FUNCTION();
    }
};

void Client()
{
    Context* context = new Context();
    State* state1 = new ConcreteStateA();
    context->SwitchState(state1);
    context->Request();
    PRINT_LINE();
    State* state2 = new ConcreteStateB();
    context->SwitchState(state2);
    context->Request();
    delete context;
    delete state1;
    delete state2;
}

int main()
{
    Client();
    return 0;
}