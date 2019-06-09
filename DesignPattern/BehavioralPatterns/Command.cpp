#include <iostream>
#include <vector>
#define PRINT_FUNCTION() std::cout << __FUNCTION__ << std::endl

class Command
{
public:
    virtual void Execute() = 0;
};

class Invoker
{
public:
    Invoker(Command* command): m_command(command) {}
    virtual void Call() { 
        PRINT_FUNCTION();
        m_command->Execute(); 
    }
private:
    Command* m_command;
};

class Receiver
{
public:
    virtual void Action() {
        PRINT_FUNCTION();
    }
};

class ConcreteCommand : public Command
{
public:
    ConcreteCommand(Receiver* receiver): m_receiver(receiver) {}
    virtual void Execute() { 
        PRINT_FUNCTION();
        m_receiver->Action(); 
    }
private:
    Receiver* m_receiver;
};

class MacroCommand : public Command {
public:
    void Execute() override {
        for (Command* cmd : m_subcommands) {
            cmd->Execute();
        }
    }
private:
    std::vector<Command*> m_subcommands;
};

void Client()
{
    Receiver* receiver = new Receiver();
    Command* command = new ConcreteCommand(receiver);
    Invoker* invoker = new Invoker(command);
    invoker->Call();
}

int main() {
    Client();
    return 0;
}