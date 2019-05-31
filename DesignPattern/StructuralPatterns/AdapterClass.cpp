class Target
{
public:
    virtual void Request() = 0;
};

class Adaptee
{
public:
    void SpecificRequest() {};
};

class Adapter : public Target, public Adaptee
{
    virtual void Request()
    {
        SpecificRequest();
    }
};

void Client()
{
    Target* target = new Adapter();
    target->Request();
}