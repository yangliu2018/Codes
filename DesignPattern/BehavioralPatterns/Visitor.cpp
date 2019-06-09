#include <iostream>
#include <vector>

#define PRINT_MESSAGE(msg)  std::cout << (msg) << std::endl
#define PRINT_FUNCTION()    PRINT_MESSAGE(__FUNCTION__)
#define PRINT_LINE()        PRINT_MESSAGE("")


class Element;
class ConcreteElementA;
class ConcreteElementB;

class Visitor
{
public:
    virtual void VisitConcreteElementA(ConcreteElementA* elementA) = 0;
    virtual void VisitConcreteElementB(ConcreteElementB* elementB) = 0;
};

class Element
{
public:
    virtual void Accept(Visitor* visitor) = 0;
};

class ConcreteVisitor1 : public Visitor
{
public:
    virtual void VisitConcreteElementA(ConcreteElementA* elementA) override {
        PRINT_FUNCTION();
    }
    virtual void VisitConcreteElementB(ConcreteElementB* elementB) override {
        PRINT_FUNCTION();
    }
};

class ConcreteVisitor2 : public Visitor
{
public:
    virtual void VisitConcreteElementA(ConcreteElementA* elementA) override {
        PRINT_FUNCTION();
    }
    virtual void VisitConcreteElementB(ConcreteElementB* elementB) override {
        PRINT_FUNCTION();
    }
};

class ConcreteElementA : public Element
{
public:
    virtual void Accept(Visitor* v) override {
        PRINT_FUNCTION();
        v->VisitConcreteElementA(this); 
    }
    void OperationA();
};

class ConcreteElementB : public Element
{
public:
    virtual void Accept(Visitor* v) override {
        PRINT_FUNCTION();
        v->VisitConcreteElementB(this);
    }
    void OperationB();
};

class ObjectStructure
{
public:
    void AddElement(Element* element) {
        m_elements.push_back(element);
    }
    void Accept(Visitor* visitor) {
        for (Element* element : m_elements) {
            element->Accept(visitor);
        }
    }
private:
    std::vector<Element*> m_elements;
};

void Client() {
    ObjectStructure container;
    container.AddElement(new ConcreteElementA());
    container.AddElement(new ConcreteElementB());
    container.AddElement(new ConcreteElementA());
    container.Accept(new ConcreteVisitor1());
    PRINT_LINE();
    container.Accept(new ConcreteVisitor2());
}

int main() {
    Client();
    return 0;
}