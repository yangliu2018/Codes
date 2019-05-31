#pragma once 

#include <iostream>
#define PRINT_FUNCTION std::cout << __FUNCTION__ << std::endl;

class SubsystemA {
public:
    void Operate() { PRINT_FUNCTION; }
};

class SubsystemB {
public:
    void Operate() { PRINT_FUNCTION; }
};

class SubsystemC {
public:
    void Operate() { PRINT_FUNCTION; }
};

class Facade {
public:
    void Operate() {
        PRINT_FUNCTION;
        m_subsystemA.Operate();
        m_subsystemB.Operate();
        m_subsystemC.Operate();
    }
private:
    SubsystemA m_subsystemA;
    SubsystemB m_subsystemB;
    SubsystemC m_subsystemC;
};

void Client() {
    Facade facade;
    facade.Operate();
}

int main() {
    Client();
    return 0;
}