#include "Decorator.h"

void Client()
{
    Component* component1 = new ConcreteComponent();
    Component* component2 = new ConcreteDecoratorA(component1);
    Component* component3 = new ConcreteDecoratorB(component2);
    component1->Operation();
    PRINT_LINE("");
    component2->Operation();
    PRINT_LINE("");
    component3->Operation();
    delete component1;
    delete component2;
    delete component3;
}

int main()
{
    Client();
    return 0;
}
