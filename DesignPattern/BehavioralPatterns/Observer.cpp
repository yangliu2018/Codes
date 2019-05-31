#include <list>

class Observer
{
public:
    virtual ~Observer() {}
    virtual void Update() = 0;
};

class Subject
{
public:
    virtual ~Subject() {}
    void Attach(Observer* observer) { m_observers.push_back(observer); }
    void Detach(Observer* observer) { m_observers.remove(observer); }
    void Notify()
    {
        for (const auto& observer : m_observers)
        {
            observer->Update();
        }
    }
private:
    std::list<Observer*> m_observers;
};

struct State;

class ConcreteSubject : public Subject
{
public:
    const State& GetState() const { return m_subjectState; }
private:
    State m_subjectState;
};

class ConcreteObserver : public Observer
{
public:
    ConcreteObserver(ConcreteSubject* subject): m_subject(subject) {}
    virtual void Update() { m_observerState = m_subject->GetState(); }
private:
    ConcreteSubject* m_subject;
    State m_observerState;
};

class Client()
{
    ConcreteSubject* subj = new ConcreteObserver();
    ConcreteObserver* obse = new ConcreteObserver(subj);
    subj->Attach(obse);
    subj->Notify();
    subj->Detach(obse);
    delete obse;
    delete subj;
}