class Context {

};

class AbstractExpression {
public:
    virtual void Interpret(Context* context) = 0;
};

class TerminalExpression : public AbstractExpression {
public:
    void Interpret(Context* context) override {

    }
};

class NonterminalExpression : public AbstractExpression {
public:
    void Interpret(Context* context) override {

    }
};

void Client() {
    Context* context = new Context();
    // construct abstract grammer tree
    // interpret
}

