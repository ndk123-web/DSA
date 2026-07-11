#include <bits/stdc++.h>

using namespace std;


class Animal {
    public:

    // derived classes should implement speak function, but here its optional
    virtual void speak() {
        cout << "Animal";   
    }
};

class Dog: public Animal {
    public:

        // optional to write speak fn , since animal has speak() 
        void speak() {
            cout << "Bark";
        }
};

int main() {

    // at runtime it calls Dog->speak() , not Anima::speak() 
    // this is Runtiime Polymorphsim
    Animal* animal = new Dog();
    animal->speak();

    return 0;
}