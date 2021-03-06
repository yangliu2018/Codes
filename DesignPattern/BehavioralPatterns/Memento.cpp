struct State;

class Memento {
public:
    // narrow public interface
    virtual ~Memento();
private:
    // wide private interface only to Originator
    friend class Originator;
    Memento();
    State GetState() { return m_state; }
    void SetState(const State& state) { m_state = state; }
    State m_state;
};

class Originator {
public:
    void SetMemento(Memento* memento) { m_state = memento->GetState(); }
    Memento* CreateMemento() {
        Memento* memento = new Memento();
        memento->SetState(m_state);
        return memento;
    }
private:
    State m_state;
};

class Caretaker {
public:
    void SetMemento(Memento* memento) { m_memento = memento; }
    Memento* GetMemento() { return m_memento; }
private:
    Memento* m_memento;
};

void Client() {
    Originator* orig = new Originator();
    Caretaker* care = new Caretaker();
    care->SetMemento(orig->CreateMemento());
    //...
    orig->SetMemento(care->GetMemento());
}

int main() {
    Client();
    return 0;
}