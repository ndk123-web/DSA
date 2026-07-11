#include <bits/stdc++.h>

using namespace std;

class User {
    public:
        int id;
        string name;
    
    User(string name) {
        cout << "Hello" << " " << name << endl;
    }
};

int main() {

    User user1("Ndk");
    User user2("yash");

    return 0;
}