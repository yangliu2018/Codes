class State
{
public:
    virtual ~State() {}
    virtual void Handle() = 0;
};

class Context
{
public:
    void Request() { m_state->Handle(); }
private:
    State* m_state;
};

class ConcreteStateA : public State
{
public:
    virtual void Handle();
};

class ConcreteStateB : public State
{
public:
    virtual void Handle();
};