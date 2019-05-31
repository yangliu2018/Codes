class Mediator
{
public:
    virtual ~Mediator() {}
};

class Colleague
{
public:
    virtual ~Colleague() {}
private:
    Mediator* m_mediator;
};

class ConcreteMediator : public Mediator
{
private:
    Colleague* m_colleague1;
    Colleague* m_colleague2;
};

class ConcreteColleague1 : public Colleague;
class ConcreteColleague2 : public Colleague;