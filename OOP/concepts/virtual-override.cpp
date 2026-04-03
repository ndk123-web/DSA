#include <bits/stdc++.h>

using namespace std;

class Payment
{
public:
    double amount, cash;
    Payment(double amount, double cash) : amount(amount), cash(cash)
    {
    }

    // Payment() {

    // }

    // default process , child in future can override it
    virtual void process()
    {
        if (amount - cash >= 0)
        {
            cout << "Its OK" << endl;
        }
        else
        {
            cout << "Its Not OK" << endl;
        }
    }
};

class User : public Payment
{
public:
    User(double amount, double cash) : Payment(amount, cash)
    {

        // doesn't  do anything just pass to the Parent Class the parameters
    }
};

class Crypto : public Payment
{
public:

    // parent do have both amount and cash with it so dont need to declare it 
    // double amount, cash;

    Crypto(double amount, double cash) : Payment(amount, cash)
    {
    }

    void process() override
    {
        if (amount - cash >= 0)
        {
            cout << "Yo its Crypto" << endl;
        }
        else
        {
            cout << "Yo Its Crypto cant withdraw" << endl;
        }
    }
};

namespace ndk {
    int a = 10;
}

int main()
{
    double amount, cash;
    amount = 1000;
    cash = 500;

    // Payment *p1;
    // User u1(amount, cash);

    // p1 = &u1;

    // p1->process();

    Crypto c1(amount, cash);
    c1.process();   

    return 0;
}