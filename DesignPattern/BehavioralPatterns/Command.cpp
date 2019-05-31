class Command
{
public:
    virtual void Execute() = 0;
};

class Invoker
{
public:
    Invoker(const Command& command): m_command(&command) {}
    virtual Call() { m_command->Execute(); }
private:
    Command* m_command;
};

class Receiver
{
public:
    virtual void Action();
};

class ConcreteCommand : public Command
{
public:
    ConcreteCommand(const Receiver& receiver): m_receiver(&receiver) {}
    virtual void Execute() { m_receiver->Action(); }
private:
    Receiver* m_receiver;
};

void Client()
{
    Receiver* receiver = new Receiver();
    Command* command = new ConcreteCommand(*receiver);
    Invoker* invoker = new Invoker(&command);
    invoker->Call();
}