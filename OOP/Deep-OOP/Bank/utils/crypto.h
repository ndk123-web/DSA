#pragma once

#include <string>
#include "account.h"

class Crypto : public AccountNamespace::Account
{
protected:
    int gas;

public:
    Crypto(int initialGas, double amount, std::string holder);
    ~Crypto();
    void withdraw(double cash) override;
};