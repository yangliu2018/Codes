class Handler
{
public:
    virtual void HandleRequest() = 0;
};

class ConcreteHandler1
{
public:
    virtual void HandleRequest();
};

class ConcreteHandler2
{
public:
    virtual void HandleRequest();
};

void Client(Handler* handler)
{
    handler->HandleRequest();
}