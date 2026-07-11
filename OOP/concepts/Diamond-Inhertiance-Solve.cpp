#include <bits/stdc++.h>

using namespace std;

class A {
    
};

// virtual means here A is shared
class B: virtual public A {

};

// virtual means here A is shared
class C: virtual public A {

};

// here D has C and D normal means D has only 1 A
class D: public C, public B {

};

int main() {

    D* obj = new D();

    return 0;
}