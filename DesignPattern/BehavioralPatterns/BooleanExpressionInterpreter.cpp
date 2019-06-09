#include <string>
#include <unordered_map>

class VariableExp;
// Assign: assign value to a variable
// Lookup: get the value of a variable
class Context {
public:
    bool Lookup(const std::string& name) const;
    void Assign(VariableExp* exp, bool value);
private:
    std::unordered_map<std::string, bool> m_variables;
};

// Evaluate, Replace, Copy are three interpreters
// Evaluate: evaluate value of expression; contex is the values of variables
// Replace: replace a variable with an expression; context is the name of replaced variable and the target expression
// Copy: copy expression itself; context is empty
class BooleanExp {
public:
    virtual ~BooleanExp() {};
    virtual bool Evaluate(Context&) = 0;
    virtual BooleanExp* Replace(const std::string& name, BooleanExp& exp) = 0;
    virtual BooleanExp* Copy() const = 0;
};

class ConstantExp : public BooleanExp {
public:
    ConstantExp(bool value) : m_value(value) {}
    virtual bool Evaluate(Context& context) override { return m_value; }
    virtual BooleanExp* Replace(const std::string& name, BooleanExp& exp) override {
        return new ConstantExp(m_value);
    }
    virtual BooleanExp* Copy() const override { return new ConstantExp(m_value); }
private:
    bool m_value;
};

class VariableExp : public BooleanExp {
public:
    VariableExp(const std::string name) : m_name(name) {}
    virtual bool Evaluate(Context& context) override { return context.Lookup(m_name); }
    virtual BooleanExp* Replace(const std::string& name, BooleanExp& exp) override {
        if (m_name == name) return exp.Copy();
        else return Copy();
    }
    virtual BooleanExp* Copy() const override { return new VariableExp(m_name); }
    const std::string& GetVariableName() const { return m_name; }
private:
    std::string m_name;
};

class AndExp : public BooleanExp {
public:
    AndExp(BooleanExp* operand1, BooleanExp* operand2) : m_operand1(operand1), m_operand2(operand2) {}
    virtual bool Evaluate(Context& context) override {
        return m_operand1->Evaluate(context) && m_operand2->Evaluate(context);
    }
    virtual BooleanExp* Replace(const std::string& name, BooleanExp& exp) override {
        return new AndExp(
            m_operand1->Replace(name, exp), m_operand2->Replace(name, exp)
        );
    }
    virtual BooleanExp* Copy() const override {
        return new AndExp(m_operand1->Copy(), m_operand2->Copy());
    }
private:
    BooleanExp* m_operand1;
    BooleanExp* m_operand2;
};

class OrExp : public BooleanExp {
public:
    OrExp(BooleanExp* operand1, BooleanExp* operand2) : m_operand1(operand1), m_operand2(operand2) {}
    virtual bool Evaluate(Context& context) override {
        return m_operand1->Evaluate(context) || m_operand2->Evaluate(context);
    }
    virtual BooleanExp* Replace(const std::string& name, BooleanExp& exp) override {
        return new OrExp(
            m_operand1->Replace(name, exp), m_operand2->Replace(name, exp)
        );
    }
    virtual BooleanExp* Copy() const override {
        return new OrExp(m_operand1->Copy(), m_operand2->Copy());
    }
private:
    BooleanExp* m_operand1;
    BooleanExp* m_operand2;
};


class NotExp : public BooleanExp {
public:
    NotExp(BooleanExp* op) : m_operand(op) {}
    virtual bool Evaluate(Context& context) override {
        return !m_operand->Evaluate(context);
    }
    virtual BooleanExp* Replace(const std::string& name, BooleanExp& exp) override {
        return new NotExp(m_operand->Replace(name, exp));
    }
    virtual BooleanExp* Copy() const override {
        return new NotExp(m_operand);
    }
private:
    BooleanExp* m_operand;
};

bool Context::Lookup(const std::string& name) const {
    return m_variables.at(name);
}
void Context::Assign(VariableExp* exp, bool value) {
    m_variables[exp->GetVariableName()] = value;
}


#include <iostream>

void Client() {
    // boolean expression: (true and x) or (y and (not x))
    Context context;
    VariableExp* x = new VariableExp("X");
    VariableExp* y = new VariableExp("Y");
    BooleanExp* expression = new OrExp(
        new AndExp(new ConstantExp(true), x),
        new AndExp(y, new NotExp(x))
    );

    // x = false, y = true
    context.Assign(x, false);
    context.Assign(y, true);
    bool result = expression->Evaluate(context);
    std::cout << "result: " << result << std::endl;

    // z = true, replace y with !z
    VariableExp* z = new VariableExp("Z");
    NotExp not_z(z);
    BooleanExp* replacement = expression->Replace("Y", not_z);
    context.Assign(z, true);
    result = replacement->Evaluate(context);
    std::cout << "result: " << result << std::endl;
}

int main()
{
    Client();
    return 0;
}