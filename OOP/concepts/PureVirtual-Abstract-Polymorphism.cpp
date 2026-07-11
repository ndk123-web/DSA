#include <bits/stdc++.h>

using namespace std;

class Animal {
    public:

    // abstract now (pure virtual fn)
    // cant create object
    // derived classes must implement speak function
    virtual void speak()  = 0;
};

class Dog: public Animal {
    public:

        void speak() {
            cout << "Bark";
        }
};

int main() {

    // here polymorphism is runitme,
    // at runtime it checks address type = Dog and called Dog::speak() , jabki pointer type is Animal
    Animal* animal = new Dog();
    animal->speak();

    return 0;
}