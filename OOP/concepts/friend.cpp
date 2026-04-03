#include <iostream>

using namespace std;

class Bank
{
private:
    int balanace = 5000;

    // mean fn can access the private variables
    friend void fn(Bank &b);

    // not entire class can access private variables
    friend class friendClass;

public:
    int getBalancer()
    {
        return balanace;
    }
};

void fn(Bank &b)
{
    b.balanace += 1000;
    cout << b.getBalancer() << endl;
};

class friendClass
{
public:
    void cfn(Bank &b)
    {
        b.balanace += 1000;
        cout << b.getBalancer() << endl;
    }
};

int main()
{

    Bank bank;
    fn(bank);
    friendClass fn;
    fn.cfn(bank);
    return 0;
}