#include <iostream>
#include "account.h"
#include "crypto.h"

using namespace std;
using namespace AccountNamespace;

Crypto::Crypto(int initialGas, double amount, string holder)
    : Account(holder, amount), gas(initialGas)
{
}

Crypto::~Crypto()
{
    cout << "Crypto Destroyed" << endl;
}

/**
 * dont need to add override 
 */
void Crypto::withdraw(double cash)
{
    if (gas > 0)
    {
        amount = amount - cash;
        gas -= 1;
        cout << "Yo All Set Crypt" << endl;
    }
    else
    {
        cout << "Yo no gas!" << endl;
    }
}