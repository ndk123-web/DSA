#include <iostream>
#include "savings.h"

using namespace std;
using namespace AccountNamespace;

Saving::Saving(int interestRate, string holder, double initialAmount)
    : Account(holder, initialAmount), interestRate(interestRate)
{
}

Saving::~Saving()
{
    cout << "Saving Destroyed" << endl;
}

void Saving::withdraw(double cash)
{
    if (amount - cash >= MIN_BALANCE_RULE)
    {
        amount -= cash;
        cout << "Withdrawl Success" << endl;
    }
    else
    {
        cout << "Withdrawl Fail" << endl;
    }
}