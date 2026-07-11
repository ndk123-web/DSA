#include <iostream>
using namespace std;


// also called as Function Overloading 
// can be use using Generics, operator overloading 
class Print {
public:
    void show(int x) {
        cout << "Integer: " << x << endl;
    }

    void show(double y) {
        cout << "Double: " << y << endl;
    }
};

int main() {
    Print obj;
    obj.show(10);
    obj.show(5.5);
}