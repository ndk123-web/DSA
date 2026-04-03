#include <iostream>

using namespace std;

class Node
{
    // GETTER AND SETTER
private:
    int balance;

public:
    // must initialize outside class
    static int nodeCount;

    Node() : balance(0)
    {
        nodeCount++;
    }

    // SETTER
    void deposit(int amount)
    {
        if (amount > 0)
        {
            balance += amount;
            return;
        }
    }

    // GETTER
    int getBalance() const
    {
        return balance;
    }
};

// Composition Concept
class UPI
{
public:
    // Composition with explicit default initialization style
    Node node{};

    void addMoney(int amount)
    {
        node.deposit(amount);
    }

    int balance() const
    {
        return node.getBalance();
    }
};

int Node::nodeCount = 0;

int main()
{
    cout << "Total: " << Node::nodeCount << endl;
    Node n1;
    cout << "Total: " << Node::nodeCount << endl;
    Node n2;
    cout << "Total: " << Node::nodeCount << endl;
    Node n3;
    cout << "Total: " << Node::nodeCount << endl;

    // Example: Node node{} inside UPI works without error
    UPI u;
    u.addMoney(500);
    cout << "UPI Balance: " << u.balance() << endl;
    cout << "Total after UPI object: " << Node::nodeCount << endl;

    return 0;
}