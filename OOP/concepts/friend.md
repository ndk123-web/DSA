# C++ OOP: Friend Function and Friend Class (Simple Notes)

This file explains the concepts used in friend.cpp in simple English.

---

## 1) Friend Function

What:
A friend function is a normal function that is allowed to access private and protected members of a class.

Why:
Sometimes we need a helper function to work closely with a class without making it a member function.

Syntax idea:
Inside class, declare:
friend void fn(Bank& b);

In your code:
- fn(Bank& b) can directly update b.balance.
- It is not called with object dot syntax like b.fn().

---

## 2) Friend Class

What:
A friend class gives all methods of that class access to private and protected members of another class.

Why:
Useful when one class must deeply cooperate with another class.

Syntax idea:
Inside class, declare:
friend class FriendClass;

In your code:
- friendClass::cfn(Bank& b) can directly update b.balance.

---

## 3) Flow of Your Program

- Bank starts with balance = 5000.
- fn(bank) adds 1000, so balance becomes 6000.
- friendClass object calls cfn(bank), adds another 1000.
- Final balance becomes 7000.

Expected printed output:
6000
7000

---

## 4) Important Interview Points

- Friendship is not inheritance.
- Friendship is not mutual by default.
  If class A is friend of B, B is not automatically friend of A.
- Friendship is not transitive.
  If A is friend of B and B is friend of C, A is not friend of C.
- Use friend carefully, because it breaks strict encapsulation.

---

## 5) Small Naming Improvements (Optional)

For cleaner code style, you can rename:
- balanace -> balance
- getBalancer() -> getBalance()
- friendClass -> FriendClass
