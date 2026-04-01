#pragma once

#include "account.h"
using namespace AccountNamespace;

class Saving : public Account
{
protected:
    int interestRate;
    double MIN_BALANCE_RULE = 1000;

public:
    Saving(int interestRate, string holder, double initialAmount);
    ~Saving();
    void withdraw(double cash) override;
};