#include <list>
#include <iostream>

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void Update() = 0;
};

class Subject
{
public:
    virtual ~Subject() = default;
    void Attach(Observer* observer) { m_observers.push_back(observer); }
    void Detach(Observer* observer) { m_observers.remove(observer); }
    void Notify()
    {
        for (auto& observer : m_observers)
        {
            observer->Update();
        }
    }
private:
    std::list<Observer*> m_observers;
};

struct State
{
    State(int x = 0) : state(x) {}
    int state;
};

class ConcreteSubject : public Subject
{
public:
    const State& GetState() const { return m_subjectState; }
    void SetState(const State& state) {
        std::cout << __FUNCTION__ << std::endl;
        m_subjectState = state;
        Notify();
    }
private:
    State m_subjectState;
};

class ConcreteObserver : public Observer
{
public:
    ConcreteObserver(ConcreteSubject* subject): m_subject(subject), m_observerState(m_subject->GetState()){}
    virtual void Update() override {
        std::cout << this << " " << __FUNCTION__ << std::endl;
        m_observerState = m_subject->GetState(); 
    }
private:
    ConcreteSubject* m_subject;
    State m_observerState;
};

void Client()
{
    ConcreteSubject* subject = new ConcreteSubject();
    Observer* observer1 = new ConcreteObserver(subject);
    Observer* observer2 = new ConcreteObserver(subject);
    subject->Attach(observer1);
    subject->Attach(observer2);

    subject->SetState(State(1));
    std::cout << std::endl;
    
    subject->Detach(observer1);
    subject->SetState(State(2));
    
    delete subject;
    delete observer1;
    delete observer2;
}

int main()
{
    Client();
    return 0;
}