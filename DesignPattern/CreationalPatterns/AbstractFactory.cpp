class AbstractProductA {};
class ConcreteProductA1: public AbstractProductA {};
class ConcreteProductA2: public AbstractProductA {};

class AbstractProductB {};
class ConcreteProductB1: public AbstractProductB {};
class ConcreteProductB2: public AbstractProductB {};

class AbstractFactory
{
public:
    virtual AbstractProductA* CreateProductA() = 0;
    virtual AbstractProductB* CreateProductB() = 0;
};

class ConcreteFactory1: public AbstractFactory
{
public:
    virtual AbstractProductA* CreateProductA() {return new ConcreteProductA1();}
    virtual AbstractProductB* CreateProductB() {return new ConcreteProductB1();}
};

class ConcreteFactory2: public AbstractFactory
{
public:
    virtual AbstractProductA* CreateProductA() {return new ConcreteProductA2();}
    virtual AbstractProductB* CreateProductB() {return new ConcreteProductB2();}
};

void Client(AbstractFactory* factory)
{
    AbstractProductA* productA = factory->CreateProductA();
    AbstractProductB* productB = factory->CreateProductB();
}