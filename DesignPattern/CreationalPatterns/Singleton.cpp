class Singleton
{
public:
    static Singleton* Instance() 
    {
        if (m_uniqueInstance == nullptr)
        {
            m_uniqueInstance = new Singleton();
        }
        return m_uniqueInstance; 
    }
    void SingletonOperation();
protected:
    Singleton();
private:
    static Singleton* m_uniqueInstance;
};

Singleton* Singleton::m_uniqueInstance = nullptr;