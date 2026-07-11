#include <bits/stdc++.h>

using namespace std;

class User {
    public:
        int a, b;

        User(int a, int b) {
            this->a = a;
            this->b = b; 
        }

        // overloaded + operator 
        User operator+(const User& u) {
            int a = (this->a + u.a);
            int b = (this->b + u.b);
            return User(a,b);
        }
};

int main() {

    User u1(10, 20);
    User u2(5, 15);

    User u3 = u1 + u2;

    cout << u3.a << " " << u3.b << endl;
    return 0;
}