#include <bits/stdc++.h>

using namespace std;

int main() {

    // static cast - converts int to double
    int a = 10;
    double b = static_cast<double>(a);

    cout << fixed << b << endl;

    // need 2 precision
    cout << fixed << setprecision(2) << b << endl;

    return 0;
}