#pragma once

#include <string>
using namespace std;

namespace AccountNamespace
{

    class Account
    {
    protected:
        string accountHolderName;
        double amount;

    public:
        Account(string holder, double initialAmount);
        ~Account();

        void deposit(double amount);
        virtual void withdraw(double amount);
        double getAmount();
    };
}