#pragma once
#include <iostream>

template<typename T>
constexpr auto PRINT_LINE(T x) { std::cout << x << std::endl; }

#define PRINT_FUNCTION  std::cout << __FUNCTION__ << std::endl 

class Component
{
public:
    virtual void Operation() = 0;
};

class ConcreteComponent : public Component
{
public:
    virtual void Operation() { PRINT_FUNCTION; };
};

class Decorator : public Component
{
public:
    Decorator(Component* component): m_component(component) {}
    virtual void Operation() {
        PRINT_FUNCTION;
        m_component->Operation(); 
    };
private:
    Component* m_component;
};

class ConcreteDecoratorA : public Decorator
{
public:
    ConcreteDecoratorA(Component* component): Decorator(component), m_addedState(0) {}
    virtual void Operation() {
        PRINT_FUNCTION;
        Decorator::Operation();
    }
private:
    int m_addedState;
};

class ConcreteDecoratorB : public Decorator
{
public:
    ConcreteDecoratorB(Component* component) : Decorator(component) {}
    virtual void Operatoion()
    {
        PRINT_FUNCTION;
        Decorator::Operation();
        AddedBehavior();
    }
    void AddedBehavior() { PRINT_FUNCTION; }
};
