class Product;

class Builder
{
public:
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual Product* GetResult() = 0;
};

class ConcreteBulider : public Builder
{
public:
    virtual void BuildPartA();
    virtual void BuildPartB();
    virtual Product* GetResult();
};

class Director
{
public:
    Director(Builder* builder) : m_builder(builder) {}
    Product* Construct()
    {
        m_builder->BuildPartA();
        m_builder->BuildPartB();
        return m_builder->GetResult();
    }
private:
    Builder* m_builder;
};

void Client()
{
    Builder* builder = new ConcreteBulider();
    Director* director = new Director(builder);
    Product* product = director->Construct();
}