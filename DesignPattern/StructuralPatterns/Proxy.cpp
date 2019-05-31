class Subject
{
public:
    virtual void Request() = 0;
};

class RealSubject
{
public:
    void Request();
};

class Proxy: public Subject
{
public:
    Proxy(RealSubject& realSubject): m_realSubject(&realSubject) {}
    virtual void Request() { m_realSubject->Request();}
private:
    RealSubject* m_realSubject;
};

void Client()
{
    RealSubject* realSubject = new RealSubject;
    Subject* subject = new Proxy(*realSubject);
    subject->Request();
}