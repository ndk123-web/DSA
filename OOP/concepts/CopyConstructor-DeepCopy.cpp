#include <bits/stdc++.h>

using namespace std;

class User {
    public: 
        int* roll;

        User(int roll) {
            this->roll = new int(roll);    
        }

        // copy constructor (when u2 = u1 (compiler calls this))
        User(const User& u) {
            this->roll = new int(*u.roll);
        }
};

int main() {

    User u1(10);

    User u2 = u1;

    cout << *u1.roll << " " << *u2.roll << endl;

    return 0;
}