class Iterator
{
public:
    virtual ~Iterator() {}
    virtual First();
    virtual Next();
    virtual IsDone();
    virtual CurrentItern();
};

class Aggregate
{
public:
    virtual ~Aggregate() {}
    virtual Iterator* CreateIterator() = 0;
};

class ConcreteIterator : public Iterator
{
public:
    ConcreteIterator(Aggregate* aggregate);
};


class ConcreteAggregate : public Aggregate
{
public:
    virtual ConcreteIterator* CreateIterator() { return new ConcreteIterator(this); }
};

void Client()
{
    Aggregate* aggr = new ConcreteAggregate();
    Iterator* iter = aggr->CreateIterator();
    delete iter;
    delete aggr;
}