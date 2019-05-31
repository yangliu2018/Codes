class Implementor
{
public:
    virtual void OperationImp() = 0;
};

class ConcreteImplementorA : public Implementor
{
public:
    virtual void OperationImp();
};

class ConcreteImplementorB : public Implementor
{
public:
    virtual void OperationImp();
};

class Abstraction
{
public:
    Abstraction(Implementor* imp) : m_imp(imp) {}
    virtual void Operation() { m_imp->OperationImp(); };
private:
    Implementor* m_imp;
};

class RefinedAbstraction : Abstraction
{
public:
    RefinedAbstraction(Implementor* imp) : Abstraction(img) {}
    virtual void Operation() {
        Abstraction::Operation();
        AdditionalOperation();
    }
private:
    void AdditionalOperation() {}
};

void Client(Implementor* imp)
{
    Abstraction* abs = new Abstraction(imp);
    abs->Operation();
}
