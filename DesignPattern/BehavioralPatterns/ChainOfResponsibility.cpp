#include <iostream>

#define PRINT_FUNCTION() std::cout << __FUNCTION__ << std::endl
#define PRINT_MESSAGE(msg) std::cout << (msg) << std::endl

class Handler {
public:
    Handler(Handler* successor = nullptr) : m_successor(successor) {}
    virtual void HandleRequest() {
        PRINT_FUNCTION();
        if (m_successor == nullptr) PRINT_MESSAGE("no handler for the request");
        else {
            PRINT_MESSAGE("transfer request to next handler");
            m_successor->HandleRequest();
        }
    }
private:
    Handler* m_successor;
};

class ConcreteHandler1 : public Handler {
public:
    ConcreteHandler1(Handler* successor = nullptr) : Handler(successor) {}
    void HandleRequest() override {
        PRINT_FUNCTION();
    }
};

class ConcreteHandler2 : public Handler {
public:
    ConcreteHandler2(Handler* successor = nullptr) : Handler(successor) {}
    void HandleRequest() override {
        PRINT_FUNCTION();
    }
};

class ConcreteHandler3 : public Handler {
public:
    ConcreteHandler3(Handler* successor = nullptr) : Handler(successor) {}
};

void Client() {
    Handler* handler1 = new ConcreteHandler1();
    Handler* handler2 = new ConcreteHandler2(handler1);
    Handler* handler3 = new ConcreteHandler3(handler2);
    handler3->HandleRequest();
    delete handler1;
    delete handler2;
    delete handler3;
}

int main()
{
    Client();
    return 0;
}