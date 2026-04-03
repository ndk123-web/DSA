# OOP in C++ - Final Master README

This is the final study README for the `OOP/` folder.

It is organized as a single master index with section links at the top, and each section explains the concept in a short, structured way.

---

## Quick Links

### 1. The 4 Main Pillars
- [Abstraction](#1-abstraction)
- [Encapsulation](#2-encapsulation)
- [Inheritance](#3-inheritance)
- [Polymorphism](#4-polymorphism)

### 2. Memory and Lifecycle
- [Constructors and Destructors](#5-constructors-and-destructors)
- [Copy Semantics](#6-copy-semantics)

### 3. Relationship Logic
- [Composition](#7-composition)
- [Aggregation](#8-aggregation)

### 4. Special Keywords
- [Static](#9-static)
- [Friend](#10-friend)
- [Inline](#11-inline)
- [Override](#12-override)
- [Auto](#13-auto)

### 5. File References
- [class-obj.md](class-obj.md)
- [friend.md](friend.md)
- [static-fun.md](static-fun.md)
- [inline-and-virt-destructor.md](inline-and-virt-destructor.md)
- [virtual-override.md](virtual-override.md)
- [Deep-OOP/README.md](Deep-OOP/README.md)

---

## 1. Abstraction

**Reference files:** [virtual-override.md](virtual-override.md), [virtual-override.cpp](virtual-override.cpp)

**What:**
Abstraction means hiding implementation details and showing only the useful interface.

**Why:**
It keeps the user focused on what an object does, not how it does it.

**How:**
- Use abstract classes
- Use pure virtual functions
- Create a contract that child classes must follow

**Important point:**
A pure virtual function makes a class abstract.

**Example:**
```cpp
class Payment {
public:
    virtual void process() = 0;
};
```

**Special line:**
Abstract class = contract, not object.

---

## 2. Encapsulation

**Reference files:** [static-fun.md](static-fun.md), [friend.md](friend.md)

**What:**
Encapsulation means keeping data and methods together while protecting data from direct outside access.

**Why:**
It improves data security and control.

**How:**
- Keep data `private`
- Expose safe access through getters and setters
- Use validation inside setter methods

**Example:**
```cpp
class Node {
private:
    int balance;

public:
    void deposit(int amount) {
        if (amount > 0) balance += amount;
    }

    int getBalance() const {
        return balance;
    }
};
```

**Special line:**
Encapsulation = data hiding + controlled access.

---

## 3. Inheritance

**Reference files:** [class-obj.md](class-obj.md), [static-fun.md](static-fun.md), [virtual-override.md](virtual-override.md), [Deep-OOP/README.md](Deep-OOP/README.md)

**What:**
Inheritance lets one class reuse another class’s behavior.

**Why:**
It reduces code duplication and models an `is-a` relationship.

**How:**
- Use `public`, `protected`, or `private` inheritance
- Base constructor runs first
- Derived constructor runs second

**Types of inheritance:**
- Single
- Multiple
- Multilevel
- Hierarchical

**Diamond problem:**
If two classes inherit from the same base and a child inherits from both, duplicate base memory can appear. Virtual inheritance solves that.

**Example:**
```cpp
class SavingsAccount : public Account {
};
```

**Special line:**
Inheritance = code reuse with a parent-child relationship.

---

## 4. Polymorphism

**Reference files:** [virtual-override.md](virtual-override.md), [inline-and-virt-destructor.md](inline-and-virt-destructor.md), [Deep-OOP/README.md](Deep-OOP/README.md)

**What:**
Polymorphism means one name, many forms.

**Why:**
It allows flexible behavior depending on the actual object type.

**How:**
- Compile-time polymorphism: function overloading, operator overloading
- Runtime polymorphism: virtual functions and overriding

**Example:**
```cpp
class Base {
public:
    virtual void process() {}
};
```

**Runtime logic:**
A base pointer points to a child object, and the child version of the function runs because of `virtual`.

**Special line:**
Polymorphism = same interface, different behavior.

---

## 5. Constructors and Destructors

**Reference files:** [class-obj.md](class-obj.md), [virtual-override.md](virtual-override.md), [inline-and-virt-destructor.md](inline-and-virt-destructor.md)

**What:**
Constructors initialize objects. Destructors clean them up.

**Why:**
They control object lifecycle and safe resource handling.

**How:**
- Use initialization lists for fast construction
- Parent constructor runs before child constructor
- Child destructor runs before parent destructor
- Use virtual destructor when deleting through a base pointer

**Example:**
```cpp
class Payment {
public:
    Payment(double amt) : amount(amt) {}
    virtual ~Payment() {}
};
```

**Special line:**
Constructor order is forward, destructor order is reverse.

---

## 6. Copy Semantics

**Reference files:** not yet separated into a dedicated note

**What:**
Copy semantics define how an object is copied.

**Why:**
Important when a class owns pointers or dynamic memory.

**How:**
- Shallow copy copies the pointer address
- Deep copy creates a new memory block

**Example:**
```cpp
class Example {
private:
    int* data;
};
```

**Special line:**
If a class owns memory, deep copy is usually safer.

---

## 7. Composition

**Reference files:** [static-fun.md](static-fun.md), [static-class-obj.cpp](static-class-obj.cpp)

**What:**
Composition means one class contains another class as a member object.

**Why:**
It is a strong `has-a` relationship.

**How:**
```cpp
class UPI {
private:
    Node node{};
};
```

**Example idea:**
`UPI` uses `Node` internally to manage balance.

**Special line:**
Prefer composition when a class should own its helper object.

---

## 8. Aggregation

**Reference files:** not yet separated into a dedicated note

**What:**
Aggregation is a weaker `has-a` relationship where one class uses another class but does not strongly own it.

**Why:**
It allows loose coupling.

**How:**
- Usually uses pointers or references
- Lifetime is not fully controlled by the owning class

**Example:**
```cpp
class Team {
private:
    Player* player;
};
```

**Special line:**
Aggregation = loose ownership.

---

## 9. Static

**Reference files:** [static-fun.md](static-fun.md), [static-class-obj.cpp](static-class-obj.cpp)

**What:**
Static members belong to the class, not to each object.

**Why:**
Use them for shared data like counters.

**How:**
- Declare inside class
- Define outside class
- Static function can access only static data directly

**Example:**
```cpp
class Node {
public:
    static int nodeCount;
    static int getNodeCount() { return nodeCount; }
};
```

**Special line:**
Static = one copy shared by all objects.

---

## 10. Friend

**Reference files:** [friend.md](friend.md), [friend.cpp](friend.cpp)

**What:**
A friend function or friend class can access private members.

**Why:**
It is useful when a helper function needs direct access.

**How:**
- `friend void fn(Bank& b);`
- `friend class friendClass;`

**Example:**
```cpp
class Bank {
private:
    int balance = 5000;
    friend void fn(Bank& b);
};
```

**Special line:**
Friend = controlled exception to access control.

---

## 11. Inline

**Reference files:** [inline-and-virt-destructor.md](inline-and-virt-destructor.md), [inline-and-virt-destructor.cpp](inline-and-virt-destructor.cpp)

**What:**
An inline function may be expanded at the call site.

**Why:**
It can reduce overhead for small functions.

**How:**
```cpp
inline int add(int a, int b) {
    return a + b;
}
```

**Special line:**
Inline = small function optimization hint.

---

## 12. Override

**Reference files:** [virtual-override.md](virtual-override.md), [virtual-override.cpp](virtual-override.cpp)

**What:**
`override` checks that a child function really overrides a base virtual function.

**Why:**
It prevents signature mismatch bugs.

**How:**
```cpp
void process() override {}
```

**Special line:**
Override = compile-time safety for runtime polymorphism.

---

## 13. Auto

**Reference files:** general C++ concept

**What:**
`auto` lets the compiler deduce the variable type.

**Why:**
It reduces repetition and improves readability in obvious cases.

**How:**
```cpp
auto x = 10;
auto y = 3.14;
```

**Special line:**
Use `auto` when the type is clear from the right-hand side.

---

## 14. Access Specifiers

**Reference files:** [class-obj.md](class-obj.md), [static-fun.md](static-fun.md), [virtual-override.md](virtual-override.md)

**What:**
Access specifiers control who can access class members.

**Why:**
They are the base of encapsulation.

**How:**
- `private`: only the class
- `protected`: class + derived class
- `public`: everyone

**Example:**
```cpp
class Bank {
private:
    int balance;

protected:
    int accountId;

public:
    void deposit(int amount);
};
```

**Special line:**
Default rule: keep data `private`, expose methods `public`.

---

## 15. Most Important OOP Concepts

**Reference files:** all major notes above

**Encapsulation:**
Data hiding with controlled access.

**Abstraction:**
Hide implementation details.

**Inheritance:**
Reuse code through parent-child relationships.

**Polymorphism:**
One interface, many behaviors.

**Composition:**
One class contains another class object.

**Aggregation:**
One class uses another class loosely.

**Special short interview line:**
Encapsulation protects data, abstraction hides complexity, inheritance reuses code, and polymorphism gives flexibility.

---

## 16. Deep OOP Project

**Reference files:** [Deep-OOP/README.md](Deep-OOP/README.md), [Deep-OOP/Next-Gen-Banking-Engine.cpp](Deep-OOP/Next-Gen-Banking-Engine.cpp)

**What:**
A multi-file banking engine project that combines inheritance, polymorphism, and project structure.

**Why:**
It shows how OOP concepts work in a real codebase.

**How:**
- `Account` is the base class
- `Saving` and `Crypto` are derived classes
- `withdraw()` is virtual for runtime dispatch

**Special line:**
This is the project-level example of the same OOP concepts used in the notes.

---

## Final Revision Order

If you want to revise in a simple way, read in this order:

1. [class-obj.md](class-obj.md)
2. [static-fun.md](static-fun.md)
3. [friend.md](friend.md)
4. [inline-and-virt-destructor.md](inline-and-virt-destructor.md)
5. [virtual-override.md](virtual-override.md)
6. [Deep-OOP/README.md](Deep-OOP/README.md)

---

## One-Line Summary

This folder is a complete OOP reference for C++ covering the 4 pillars, memory and lifecycle, relationships, special keywords, and a real project example.
