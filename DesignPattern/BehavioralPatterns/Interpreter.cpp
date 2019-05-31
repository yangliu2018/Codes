class Context;

class AbstractExpression
{
public:
    virtual void Interpret(Context* context) = 0;
    virtual ~AbstractExpression() {}
};

class TerminalExpression : public AbstractExpression
{
public:
    virtual void Interpret(Context* context);
};

class NonterminalExpression : public AbstractExpression
{
public:
    NonterminalExpression(AbstractExpression* expression): m_expression(expression) {}
    virtual void Interpret(Context* context) { m_expression->Interpret(context); }
private:
    AbstractExpression* m_expression;
};

void Client()
{
    Context* context = new Context();
    AbstractExpression* expression1 = new TerminalExpression();
    AbstractExpression* expression2 = new NonterminalExpression(expression1);
    expression1->Interpret(context);
    expression2->Interpret(context);
    delete context;
    delete expression1;
    delete expression2;
}