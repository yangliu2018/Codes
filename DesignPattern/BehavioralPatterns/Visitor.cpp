class Element;
class ConcreteElementA : public Element;
class ConcreteElementB : public Element;

class Visitor
{
public:
    virtual void VisitConcreteElementA(ConcreteElementA* elementA) = 0;
    virtual void VisitConcreteElementB(ConcreteElementB* elementB) = 0;
};

class Element()
{
public:
    virtual void Accept(Visitor* visitor) = 0;
};

class ObjectStructure
{
private:
    Element* m_elementX;
    Element* m_elementY;
    //...
};

class ConcreteVisit1 : public Visitor
{
public:
    virtual void VisitConcreteElementA(ConcreteElementA* elementA);
    virtual void VisitConcreteElementB(ConcreteElementB* elementB);
};

class ConcreteVisit2 : public Visitor
{
public:
    virtual void VisitConcreteElementA(ConcreteElementA* elementA);
    virtual void VisitConcreteElementB(ConcreteElementB* elementB);
};

class ConcreteElementA()
{
public:
    virtual void Accept(Visitor* v) { v->VisitConcreteElemeteA(this); }
    void OperationA();
};

class ConcreteElementB()
{
public:
    virtual void Accept(Visitor* v) { v->VisitConcreteElemeteB(this); }
    void OperationB();
};