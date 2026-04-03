#include <iostream>

// NORMAL CONSTRUCTOR
using namespace std;

// instead of putting this function in stack it directly uses as a code 
inline int add(int a, int b) {
    return a + b;
}

class Base
{

public:
    Base()
    {
        std::cout << "Base constructor" << endl;
    }

    // sometimes Base childs memory leaks because compiler never call desctructor of child 
    // when type is Base (parent)
    // so to solve that we must add virtual before the Desctructor to solve the issue 
    virtual ~Base()
    {
        std::cout << "Base destructor" << endl;
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        std::cout << "Derived constructor" << endl;
    }

    ~Derived()
    {

        std::cout << "Derived destructor" << endl;
    }
};

int main()
{   
    // 1. 
    Base* base = new Derived();
    
    // now compiler check the type and accordignly call that type desctructor
    // but not the derived one 
    delete base;

    // 2. 
    Derived* d = new Derived();

    // here type is derived so sequenctially derived then parent base destuctor will be called  
    delete d;
    return 0;
}