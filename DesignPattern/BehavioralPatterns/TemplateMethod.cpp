#include <iostream>
#define PRINT_FUNCTION() std::cout << __FUNCTION__ << std::endl
#define PRINT_LINE() std::cout << std::endl;

class AbstractClass
{
public:
    void TemplateMethod()
    {
        PRINT_FUNCTION();
        PrimitiveOperation1();
        PrimitiveOperation2();
    }
protected:
    virtual void PrimitiveOperation1() { PRINT_FUNCTION(); }
    virtual void PrimitiveOperation2() { PRINT_FUNCTION(); }
};

class ConcreteClassA : public AbstractClass
{
    virtual void PrimitiveOperation1() override { PRINT_FUNCTION(); }
    virtual void PrimitiveOperation2() override { PRINT_FUNCTION(); }
};

class ConcreteClassB : public AbstractClass
{
    virtual void PrimitiveOperation2() override { 
        PRINT_FUNCTION();
        AbstractClass::PrimitiveOperation2();
    }
};

class ConcreteClassC : public AbstractClass
{
};

void Client()
{
    ConcreteClassA().TemplateMethod();
    PRINT_LINE();
    ConcreteClassB().TemplateMethod();
    PRINT_LINE();
    ConcreteClassC().TemplateMethod();
}

int main()
{
    Client();
    return 0;
}