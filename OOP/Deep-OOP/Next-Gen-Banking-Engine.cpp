#include "utils/account.h"
#include <iostream>
#include "utils/savings.h"
#include "utils/crypto.h"

using namespace std;
using namespace AccountNamespace;

// entry point
int main()
{

    // try Saving Account
    int interestRate = 8;
    double initialAmount = 20000;
    string holderName = "NDK";

    // Saving Example
    Account *acc = new Saving(interestRate, holderName, initialAmount);
    acc->withdraw(1000);
    double savingAmount = acc->getAmount();
    cout << "Saving Amount: " << savingAmount << endl;

    // Crypto Example
    int initialGas = 10;
    Account *acc2 = new Crypto(initialGas, initialAmount, holderName);
    acc2->withdraw(5000);
    double cryptoAmount = acc2->getAmount();
    cout << "Crypto Amount: " << cryptoAmount << endl;

    return 0;
}