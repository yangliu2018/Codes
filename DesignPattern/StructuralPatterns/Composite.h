#pragma once
#include <vector>

class Component {
public:
    virtual void Operation() = 0;
    virtual void Add(Component* item) {};
    virtual void Remove(Component* item) {};
    virtual Component* GetChild(size_t idx) { return nullptr; };
};

class Composite : public Component
{
public:
    virtual void Operation() {
        for (Component* child : m_children) {
            child->Operation();
        }
    }
    virtual void Add(Component* item) {
        m_children.push_back(item);
    }
    virtual void Remove(Component* item) {
        auto iter = std::find(m_children.begin(), m_children.end(), item);
        if (iter != m_children.end()) m_children.erase(iter);
    }
    virtual Component* GetChild(size_t idx) {
        Component* ret = nullptr;
        if (idx < m_children.size()) ret = m_children[idx];
        return ret;
    }
private:
    std::vector<Component*> m_children;
};

#include <iostream>

class LeafA : public Component {
public:
    virtual void Operation() { std::cout << "LeafA::Operation()" << std::endl; }
};

class LeafB : public Component {
public:
    virtual void Operation() { std::cout << "LeafB::Operation()" << std::endl; }
};

void Client()
{
    Component* componentA = new LeafA();
    Component* componentB = new LeafB();
    Component* componentC = new Composite();
    componentC->Add(componentA);
    componentC->Add(componentB);
    componentA->Operation();
    componentB->Operation();
    componentC->Operation();
    delete componentA;
    delete componentB;
    delete componentC;
}