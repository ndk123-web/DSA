#include "account.h"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace AccountNamespace
{
    Account::Account(string holder, double initialAmount)
    {
        if (holder.empty())
        {
            throw invalid_argument("Holder cannot be empty");
        }

        if (initialAmount <= 1000)
        {
            throw invalid_argument("Initial Amount must above 1000");
        }

        accountHolderName = holder;
        amount = initialAmount;
    }

    Account::~Account()
    {
        cout << "Destroyed Account object";
    }

    void Account::deposit(double amount)
    {
        this->amount += amount;
    }

    double Account::getAmount()
    {
        return amount;
    }

    void Account::withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Withdrawl Fail" << endl;
            return;
        }

        if (this->amount >= amount)
        {
            this->amount -= amount;
            cout << "Withdrawl Success" << endl;
        }
        else
        {
            cout << "Withdrawl Fail" << endl;
        }
    }
}