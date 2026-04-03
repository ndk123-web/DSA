# C++ OOP: Inline Function and Virtual Destructor

This note explains two important C++ concepts shown in `inline-and-virt-destructor.cpp`:

1. Inline function
2. Virtual destructor

It also explains constructor and destructor order when using base and derived class pointers.

---

## 1. Inline Function

**What:**
An `inline` function is a function that suggests the compiler may replace the function call with the actual function code.

**Why:**
It can reduce function call overhead for small, frequently used functions.

**Important Note:**
`inline` is only a suggestion. The compiler may ignore it. Modern compilers decide this automatically in many cases.

### Example
```cpp
inline int add(int a, int b) {
    return a + b;
}
```

### Logic
Normally, a function call has overhead because the program jumps to another location and returns back.
For a very small function like `add`, the compiler may directly expand the code at the call site.

### Input
```cpp
cout << add(2, 3) << endl;
```

### Output
```cpp
5
```

---

## 2. Virtual Destructor

**What:**
A destructor declared with `virtual` in the base class.

**Why:**
It ensures that when a derived object is deleted through a base class pointer, the derived class destructor is called first, then the base class destructor.

**High-Priority Interview Point:**
If a class is meant to be used polymorphically, its destructor should usually be virtual.

### Example
```cpp
class Base {
public:
    virtual ~Base() {
        cout << "Base destructor" << endl;
    }
};
```

### Logic
If you write:
```cpp
Base* base = new Derived();
delete base;
```
then the program must know the real object type at runtime.
Because the destructor is virtual, C++ calls:
1. `Derived` destructor
2. `Base` destructor

If the destructor is not virtual, deleting through a base pointer can cause undefined behavior and may skip the derived destructor.

---

## 3. Constructor and Destructor Order

### Construction Order
When a `Derived` object is created:
1. Base constructor runs first.
2. Derived constructor runs second.

### Destruction Order
When a `Derived` object is destroyed:
1. Derived destructor runs first.
2. Base destructor runs second.

This order is always opposite.

---

## 4. Your Program Flow

### Case 1
```cpp
Base* base = new Derived();
delete base;
```

What happens:
1. `Base` constructor
2. `Derived` constructor
3. `Derived` destructor
4. `Base` destructor

### Case 2
```cpp
Derived* d = new Derived();
delete d;
```

What happens:
1. `Base` constructor
2. `Derived` constructor
3. `Derived` destructor
4. `Base` destructor

### Final Output Order
The full output will be:
```cpp
Base constructor
Derived constructor
Derived destructor
Base destructor
Base constructor
Derived constructor
Derived destructor
Base destructor
```

---

## 5. Why Virtual Destructor Matters

**Without `virtual`:**
Deleting a derived object through a base pointer may not call the derived destructor properly.

**With `virtual`:**
C++ correctly performs runtime dispatch for destruction.

This is important when the derived class owns resources like:
- dynamic memory
- file handles
- sockets
- database connections

If the derived destructor does not run, those resources may leak.

---

## 6. Small Code Review of Your Example

Your example is correct for demonstrating the concept, but one comment should be understood carefully:

- It is not that the compiler "never calls the child destructor".
- The real issue is when the base destructor is not virtual and you delete through a base pointer.
- In that case, behavior is unsafe and the derived cleanup may be skipped.

So the concept to remember is:

**Use `virtual` in the base destructor when the class will be used polymorphically.**

---

## 7. One-Line Interview Answer

A virtual destructor ensures proper cleanup of derived objects when they are deleted through a base class pointer.

---

## 8. Full Example

```cpp
#include <iostream>
using namespace std;

inline int add(int a, int b) {
    return a + b;
}

class Base {
public:
    Base() {
        cout << "Base constructor" << endl;
    }

    virtual ~Base() {
        cout << "Base destructor" << endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        cout << "Derived constructor" << endl;
    }

    ~Derived() {
        cout << "Derived destructor" << endl;
    }
};

int main() {
    Base* base = new Derived();
    delete base;

    Derived* d = new Derived();
    delete d;

    cout << add(2, 3) << endl;
    return 0;
}
```

---

## 9. Expected Output

```cpp
Base constructor
Derived constructor
Derived destructor
Base destructor
Base constructor
Derived constructor
Derived destructor
Base destructor
5
```
