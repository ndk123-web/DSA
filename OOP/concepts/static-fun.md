# C++ OOP: Static, Getter-Setter, Composition, and Inheritance

This note explains four core OOP topics in clean interview style, based on your `Node` and `UPI` style code.

---

## 1. Static Variables and Static Functions

**What:**
`static` data member belongs to the class, not to each object.

**Why:**
Use it for shared information like total object count.

**High-Priority Interview Point:**
- Static variable: single copy for whole class.
- Static function: can access only static members directly (no `this` pointer).

### Example
```cpp
class Node {
private:
	int balance;

public:
	static int nodeCount;

	Node() : balance(0) {
		nodeCount++;
	}

	static int getNodeCount() {
		return nodeCount;
	}
};

int Node::nodeCount = 0;
```

### Logic
- Every time object is created, constructor runs.
- Constructor increments shared `nodeCount`.
- `getNodeCount()` works without object: `Node::getNodeCount()`.

### Input
Create 3 objects of `Node`.

### Output
`nodeCount = 3`.

---

## 2. Getter and Setter

**What:**
Getter reads private data, setter updates private data safely.

**Why:**
Encapsulation: data is protected and controlled.

**High-Priority Interview Point:**
- Keep data members private.
- Validate values inside setter.

### Example
```cpp
class Node {
private:
	int balance;

public:
	Node() : balance(0) {} 

	void deposit(int amount) {
		if (amount > 0) {
			balance += amount;
		}
	}

	int getBalance() const {
		return balance;
	}
};
```

### Logic
- Direct access to `balance` is blocked.
- `deposit()` prevents invalid negative/zero updates.
- `getBalance()` gives read-only access.

### Input
`deposit(500)`, `deposit(-10)`.

### Output
Balance becomes `500` (second input ignored).

---

## 3. Composition

**What:**
Composition means one class contains object(s) of another class.

**Why:**
Represents "has-a" relation.

**High-Priority Interview Point:**
- `UPI has-a Node` is composition.
- Prefer direct member object when possible (safer than raw pointer).
- You can write `Node node{};` for explicit value/default initialization style.

### Example (better memory-safe composition)
```cpp
class UPI {
private:
	Node node{};

public:
	void addMoney(int amount) {
		node.deposit(amount);
	}

	int balance() const {
		return node.getBalance();
	}
};
```

### Logic
- `UPI` internally uses `Node` features.
- User of `UPI` does not manage `Node` directly.

### Input
`UPI u; u.addMoney(1000);`

### Output
`u.balance()` returns `1000`.

---

## 4. Inheritance

**What:**
Inheritance lets one class reuse another class behavior.

**Why:**
Represents "is-a" relation and reduces repeated code.

**High-Priority Interview Point:**
- Public inheritance: public members stay public.
- Constructor order: Base first, then Derived.

### Example
```cpp
class Account {
protected:
	int balance;

public:
	Account() : balance(0) {}

	void deposit(int amount) {
		if (amount > 0) balance += amount;
	}

	int getBalance() const {
		return balance;
	}
};

class SavingsAccount : public Account {
public:
	void addInterest(int amount) {
		if (amount > 0) balance += amount;
	}
};
```

### Logic
- `SavingsAccount` inherits `deposit()` and `getBalance()`.
- It adds extra behavior `addInterest()`.

### Input
`SavingsAccount s; s.deposit(1000); s.addInterest(100);`

### Output
`s.getBalance()` returns `1100`.

---

## Quick Difference: Composition vs Inheritance

- Composition: has-a relationship (`UPI has-a Node`).
- Inheritance: is-a relationship (`SavingsAccount is-an Account`).
- Rule of thumb: prefer composition unless true is-a relation exists.

---

## One Combined Demo

```cpp
#include <iostream>
using namespace std;

class Node {
private:
	int balance;

public:
	static int nodeCount;

	Node() : balance(0) {
		nodeCount++;
	}

	void deposit(int amount) {
		if (amount > 0) balance += amount;
	}

	int getBalance() const {
		return balance;
	}

	static int getNodeCount() {
		return nodeCount;
	}
};

int Node::nodeCount = 0;

class UPI {
private:
	Node node{}; // Composition with explicit default initialization

public:
	void addMoney(int amount) {
		node.deposit(amount);
	}

	int balance() const {
		return node.getBalance();
	}
};

class PremiumUPI : public UPI { // Inheritance
public:
	void rewardMessage() {
		cout << "Reward eligible user" << endl;
	}
};

int main() {
	Node n1, n2;
	cout << "Total Nodes: " << Node::getNodeCount() << endl;

	PremiumUPI p;
	p.addMoney(700);
	cout << "Balance: " << p.balance() << endl;
	p.rewardMessage();

	return 0;
}
```
