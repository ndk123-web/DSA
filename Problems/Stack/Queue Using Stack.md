
---

# 📘 **Implement Queue Using Stacks — Two Approaches (Clean MD)**

Queue must behave **FIFO**, but stack is **LIFO**, so we simulate queue logic using stacks.

This file includes:

* **Approach 1:** Simple but slow
* **Approach 3:** True optimized two-stack solution

---

# # 🥉 **Approach 1 — Single Stack + Temporary Reverse**

### **Time:**

- push → O(1)
- pop → O(n)
- peek → O(n)

### **Idea:**

For pop/peek, reverse the stack into a temporary stack to access the front element.

---

### **Code (with short comments)**

```cpp
class MyQueue {
private:
    stack<int> st;  // main stack

public:
    MyQueue() {}

    void push(int x) {
        st.push(x);                     // normal push
    }

    int pop() {
        stack<int> temp;

        // reverse st -> temp
        while (!st.empty()) {
            temp.push(st.top());
            st.pop();
        }

        int val = temp.top();           // front element
        temp.pop();

        // restore order temp -> st
        while (!temp.empty()) {
            st.push(temp.top());
            temp.pop();
        }

        return val;
    }

    int peek() {
        stack<int> temp;

        // reverse st -> temp
        while (!st.empty()) {
            temp.push(st.top());
            st.pop();
        }

        int val = temp.top();           // front element

        // restore order back into st
        while (!temp.empty()) {
            st.push(temp.top());
            temp.pop();
        }

        return val;
    }

    bool empty() {
        return st.empty();
    }
};
```

---

# # 🥇 **Approach 3 — Optimized Two-Stack Queue (Best Approach)**

### **Time:**

- push → O(1)
- pop → amortized O(1)
- peek → amortized O(1)

### **Idea:**

Use **two stacks**:

- `inStack` → for pushing
- `outStack` → for popping/peeking
- Move elements from `inStack → outStack` **only when needed**, not every time.

This reduces pop/peek to **amortized O(1)**.

---

### **Code (with short comments)**

```cpp
class MyQueue {
private:
    stack<int> inStack;   // receives new elements
    stack<int> outStack;  // gives queue front

    // move elements only when outStack is empty
    void shiftStacks() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
    }

public:
    MyQueue() {}

    void push(int x) {
        inStack.push(x);                  // always push here (O(1))
    }

    int pop() {
        shiftStacks();                    // ensure correct order
        int val = outStack.top();         // front of queue
        outStack.pop();
        return val;
    }

    int peek() {
        shiftStacks();                    // ensure correct order
        return outStack.top();            // front element
    }

    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};
```

---

# # 🏁 **Final Notes**

| Approach       | push     | pop                | peek               | Comment            |
| -------------- | -------- | ------------------ | ------------------ | ------------------ |
| **Approach 1** | O(1)     | O(n)               | O(n)               | Simple but slow    |
| **Approach 3** | **O(1)** | **O(1) amortized** | **O(1) amortized** | Best & recommended |

---
