#include <iostream>
#define PRINT_FUNCTION() std::cout << __FUNCTION__ << std::endl;

class Colleague;
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void Request(Colleague*) = 0;
    virtual void AddColleague(Colleague*) = 0;
};

class Colleague {
public:
    Colleague(Mediator* mediator) : m_mediator(mediator) {
        m_mediator->AddColleague(this);
    }
    virtual ~Colleague() = default;
    void Request() {
        std::cout << typeid(*this).name() << ": ";
        PRINT_FUNCTION();
        m_mediator->Request(this);
    }
    virtual void HandleRequest() = 0;
private:
    Mediator* m_mediator;
};

class ConcreteMediator : public Mediator {
public:
    ConcreteMediator(Colleague* colleague1 = nullptr, Colleague* colleague2 = nullptr)
        : m_colleague1(colleague1), m_colleague2(colleague2) {}
    virtual void Request(Colleague* colleague) override {
        PRINT_FUNCTION();
        if (colleague == m_colleague1 && m_colleague2 != nullptr) {
            m_colleague2->HandleRequest();
        }
        else if (colleague == m_colleague2 && m_colleague1 != nullptr) {
            m_colleague1->HandleRequest();
        }
        else {
            std::cout << "fail to transfer request." << std::endl;
        }
    }
    virtual void AddColleague(Colleague* colleague) override {
        if (m_colleague1 == nullptr) m_colleague1 = colleague;
        else if (m_colleague2 == nullptr) m_colleague2 = colleague;
        else std::cout << "mediator is full." << std::endl;
    }
private:
    Colleague* m_colleague1;
    Colleague* m_colleague2;
};

class ConcreteColleague1 : public Colleague {
public:
    ConcreteColleague1(Mediator* mediator) : Colleague(mediator) {}
    virtual void HandleRequest() override {
        PRINT_FUNCTION();
    }
};

class ConcreteColleague2 : public Colleague {
public:
    ConcreteColleague2(Mediator* mediator) : Colleague(mediator) {}
    virtual void HandleRequest() override {
        PRINT_FUNCTION();
    }
};
void Client() {
    Mediator* mediator = new ConcreteMediator();
    Colleague* colleague1 = new ConcreteColleague1(mediator);
    Colleague* colleague2 = new ConcreteColleague2(mediator);
    colleague1->Request();
    std::cout << std::endl;
    colleague2->Request();
}

int main() {
    Client();
    return 0;
}