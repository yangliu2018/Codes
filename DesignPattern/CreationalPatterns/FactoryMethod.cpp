class AbstractProduct {};
class ConcreteProductA: public AbstractProduct {};
class ConcreteProductB: public AbstractProduct {};

class Creator
{
public:
    virtual AbstractProduct* FactoryMethod() = 0;
};

class ConcreteCreatorA: public Creator
{
public:
    virtual AbstractProduct* FactoryMethod() {return new ConcreteProductA();}
};

class ConcreteCreatorB: public Creator
{
public:
    virtual AbstractProduct* FactoryMethod() {return new ConcreteProductB();}
};


void Client(Creator* creator)
{
    AbstractProduct* product = creator->FactoryMethod();
}