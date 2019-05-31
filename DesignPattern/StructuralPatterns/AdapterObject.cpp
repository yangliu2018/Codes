class Target
{
public:
    virtual void Request() = 0;
};

class Adaptee
{
public:
    void SepcificRequest();
};

class Adapter : public Target
{
public:
    Adapter(Adaptee* adaptee) : m_adaptee(adaptee) {};
    virtual void Request() { m_adaptee->SepcificRequest(); };
private:
    Adaptee* m_adaptee;
};

void Client()
{
    Adaptee* adaptee = new Adaptee();
    Target* target = new Adapter(adaptee);
    target->Request();
}