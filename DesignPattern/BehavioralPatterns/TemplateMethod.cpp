class AbstractClass
{
public:
    void TemplateMethod()
    {
        //...
        PrimitiveOperation1();
        //...
        PrimitiveOperation2();
        //...
    }
private:
    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;
};

class ConcreteClass
{
    virtual void PrimitiveOperation1();
    virtual void PrimitiveOperation2();
};