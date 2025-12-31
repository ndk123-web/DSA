# MyCircularQueue — Two Implementations Explained (Deque vs Linked List)

## Problem Summary

Design a **circular queue** with fixed size `k` that supports:

- `enQueue(value)`
- `deQueue()`
- `Front()`
- `Rear()`
- `isEmpty()`
- `isFull()`

Key constraints:

- Queue has a **fixed capacity**
- FIFO behavior
- Efficient operations

---

# ✅ Solution 1: Using `deque<int>` (STL-based)

```cpp
class MyCircularQueue {
private:
    int size;
    deque<int> dq;

public:
    MyCircularQueue(int k) {
        size = k;
    }

    bool enQueue(int value) {
        if (dq.size() == size) {
            return false;
        }
        dq.push_back(value);
        return true;
    }

    bool deQueue() {
        if (dq.size() == 0) {
            return false;
        }
        dq.pop_front();
        return true;
    }

    int Front() {
        if (dq.size() == 0) return -1;
        return dq.front();
    }

    int Rear() {
        if (dq.size() == 0) return -1;
        return dq.back();
    }

    bool isEmpty() {
        return dq.size() == 0;
    }

    bool isFull() {
        return dq.size() == size;
    }
};
```

---

## 🔍 How this works

- `deque` already supports:

  - `push_back`
  - `pop_front`
  - `front`
  - `back`

- You manually enforce **capacity** using `size`

This is **not a real circular queue internally**, but:

- From the problem’s perspective
- It behaves exactly like one

---

## ✅ Pros

- Very clean
- Zero pointer bugs
- Perfect for interviews if STL is allowed
- No memory management issues

---

## ❌ Cons

- Hides the real circular queue mechanics
- Not suitable if interviewer wants **low-level implementation**

---

## When to use this?

✔ LeetCode
✔ Rapid prototyping
✔ When STL is allowed

---

# ✅ Solution 2: Linked List–Based Queue (Manual Memory)

```cpp
struct Node {
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;  // VERY IMPORTANT
    }
};

class MyCircularQueue {
private:
    int size;
    Node* front = nullptr;
    Node* back = nullptr;
    int currcnt = 0;

public:
    MyCircularQueue(int k) { size = k; }

    bool enQueue(int value) {
        if (currcnt == size) {
            return false;
        }
        Node* newback = new Node(value);
        if (back == nullptr) {
            back = newback;
            front = newback;
        } else {
            back->next = newback;
            back = back->next;
        }
        currcnt++;
        return true;
    }

    bool deQueue() {
        if (currcnt == 0) {
            return false;
        }
        if (front->next == nullptr) {
            front = nullptr;
            back = nullptr;
        } else {
            Node* temp = front;
            front = front->next;
            delete temp;   // memory free
        }
        currcnt--;
        return true;
    }

    int Front() {
        if (currcnt == 0) return -1;
        return front->data;
    }

    int Rear() {
        if (currcnt == 0) return -1;
        return back->data;
    }

    bool isEmpty() { return currcnt == 0; }

    bool isFull() { return currcnt == size; }
};
```

---

## 🔍 How this works

- `front` → first element
- `back` → last element
- `currcnt` tracks current size
- `size` is max capacity

This is a **queue using linked list**, with capacity restriction.

⚠️ Note: It is **logically circular**, not physically circular.

---

# 🚨 Issues You Faced Earlier (and WHY)

## ❌ Issue 1: `Node->next` was uninitialized

Earlier constructor:

```cpp
Node(int data) { this->data = data; }
```

### What happened?

- `next` contained garbage (`0xbebebebebebebebe`)
- Accessing `front->next` caused **Undefined Behavior**

### Why sanitizer showed `0xbebebebe`?

This pattern means:

> “Uninitialized memory accessed”

### Fix (you did it correctly):

```cpp
this->next = nullptr;
```

---

## ❌ Issue 2: Misaligned pointer error

Error:

```
member access within misaligned address 0xbebebebebebebebe
```

Meaning:

- Pointer was never initialized
- C++ trusted you blindly
- Program accessed random memory

C++ does **NOT** auto-null pointers.

---

## ❌ Issue 3: Missing `delete` in `deQueue`

Earlier:

```cpp
front = front->next;
```

Problem:

- Memory leak
- Node was lost forever

Fix:

```cpp
Node* temp = front;
front = front->next;
delete temp;
```

---

# 🧠 Key Concepts You Learned (Important)

## 1️⃣ STL vs Manual Memory

| Aspect   | deque            | Linked List         |
| -------- | ---------------- | ------------------- |
| Safety   | Very high        | Your responsibility |
| Speed    | Optimized        | Same (O(1))         |
| Bugs     | Rare             | Easy to make        |
| Learning | Low-level hidden | Deep understanding  |

---

## 2️⃣ Why deque version never crashed

Because:

- STL initializes memory
- STL manages lifetime
- No raw pointers

---

## 3️⃣ Why linked list version crashed earlier

Because:

- Raw pointers
- No automatic initialization
- One missing line = UB

---

## 4️⃣ Circular Queue ≠ Must be circular list

Important insight:

> A circular queue is about **behavior**, not structure

Array, deque, linked list — all valid if behavior matches.

---

# ✅ Final Verdict

- **deque solution**
  ✔ Best for interviews
  ✔ Clean and safe

- **linked list solution**
  ✔ Best for learning
  ✔ Teaches memory discipline

You didn’t just “solve a problem” —
you learned **why C++ is dangerous when you’re careless**.
