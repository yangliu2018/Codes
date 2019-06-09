#include <iostream>
#define PRINT_FUNCTION std::cout << __FUNCTION__ << std::endl

class Subject {
public:
    virtual void Request() = 0;
};

class RealSubject : public Subject {
public:
    RealSubject() { PRINT_FUNCTION; }
    void Request() final { PRINT_FUNCTION; }
};

class Proxy : public Subject {
public:
    Proxy(RealSubject* realSubject = nullptr)
        : m_realSubject(realSubject) {
        PRINT_FUNCTION;
    }
    void Request() final {
        PRINT_FUNCTION;
        if (m_realSubject == nullptr) m_realSubject = new RealSubject();
        m_realSubject->Request();
    }
private:
    RealSubject* m_realSubject;
};

void Client() {
    Subject* subject = new Proxy();
    subject->Request();
}

int main() {
    Client();
    return 0;
}