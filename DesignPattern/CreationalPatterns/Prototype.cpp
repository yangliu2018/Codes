class Prototype
{
public:
    virtual Prototype* Clone() = 0;
};

class ConcretePrototype1 : public Prototype
{
public:
    virtual ConcretePrototype1* Clone() { return new ConcretePrototype1(*this); }
};

class ConcretePrototype2 : public Prototype
{
public:
    virtual ConcretePrototype2* Clone() { return new ConcretePrototype2(*this); }
};

void Client(Prototype* prototype)
{
    Prototype* p = prototype->Clone();
}