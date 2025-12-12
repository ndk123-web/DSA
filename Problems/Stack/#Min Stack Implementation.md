
---

# 📘 **Min Stack — Brute to Optimal (All Approaches)**

The goal is to design a stack that supports:

| Operation  | Complexity Goal |
| ---------- | --------------- |
| `push(x)`  | O(1)            |
| `pop()`    | O(1)            |
| `top()`    | O(1)            |
| `getMin()` | O(1)            |

This file covers **all approaches**, from brute force to optimal.

---

# # 🥉 **Approach 1 — Brute Force (Scan the Entire Stack)**

### **Time:**

- push: O(1)
- pop: O(1)
- top: O(1)
- **getMin: O(n)** (worst)

### **Idea:**

Use a normal stack.
Whenever `getMin()` is called, iterate through a copy of the stack to find the smallest element.

---

### **Code (with short comments)**

```cpp
class MinStack {
private:
    stack<int> st;

public:
    MinStack() {}

    void push(int val) {
        st.push(val);                       // normal push
    }

    void pop() {
        st.pop();
    }

    int top() {
        return st.top();
    }

    // brute: scan all elements to find min
    int getMin() {
        stack<int> temp = st;
        int mn = INT_MAX;

        while (!temp.empty()) {
            mn = min(mn, temp.top());
            temp.pop();
        }

        return mn;
    }
};
```

### ✔ Pros

- Easiest method

### ❌ Cons

- `getMin()` is **O(n)** → inefficient

---

# # 🥈 **Approach 2 — Using multiset (Another valid method)**

### **Time:**

- push: O(log n)
- pop: O(log n)
- getMin: **O(1)**

### **Idea:**

- `st` stores real stack
- `multiset` always sorted → min always at `begin()`

---

### **Code**

```cpp
class MinStack {
private:
    stack<int> st;
    multiset<int> mset;

public:
    MinStack() {}

    void push(int val) {
        st.push(val);
        mset.insert(val);                   // log n insert
    }

    void pop() {
        mset.erase(mset.find(st.top()));    // erase one instance
        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return *mset.begin();               // smallest element
    }
};
```

### ✔ Pros

- Easy to write
- Correct
- Constant-time getMin()

### ❌ Cons

- Worse complexity than optimal (log n)
- Needs extra memory

---

# # 🥈 **Approach 3 — Stack of Pairs (value, minSoFar)**

### **Time:**

All operations → **O(1)**

### **Idea:**

Each stack entry stores:

```
(value, currentMinBeforeThisPush)
```

So top.second is always the minimum at that level.

---

### **Code**

```cpp
class MinStack {
private:
    stack<pair<int,int>> st;

public:
    void push(int val) {
        if (st.empty())
            st.push({val, val});                   // first element
        else
            st.push({val, min(val, st.top().second)});
    }

    void pop() {
        st.pop();
    }

    int top() {
        return st.top().first;
    }

    int getMin() {
        return st.top().second;                    // min so far
    }
};
```

### ✔ Pros

- Very easy
- O(1) operations
- No extra data structures

### ❌ Cons

- Uses pair → little extra memory

---

# # 🥇 **Approach 4 — Two Stack Method (Optimal & Clean)**

### **Time:**

All operations → **O(1)**

### **Idea:**

Use two stacks:

- `st` → stores real values
- `mn` → stores only mins

  - Push to `mn` only if new value ≤ current min
  - Pop from `mn` only when popped value == current min

---

### **Code**

```cpp
class MinStack {
private:
    stack<int> st;
    stack<int> mn;

public:
    MinStack() {}

    void push(int val) {
        st.push(val);
        if (mn.empty() || mn.top() >= val)
            mn.push(val);                     // update min stack
    }

    void pop() {
        if (st.top() == mn.top())
            mn.pop();                         // remove min if needed
        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return mn.top();                      // always top of mn
    }
};
```

### ✔ Pros

- True optimal
- Clean and intuitive
- Zero extra overhead

### ❌ Cons

- None — Best method

---

# # 🏁 **Comparison**

| Approach              | push     | pop      | top      | getMin   | Space | Notes                  |
| --------------------- | -------- | -------- | -------- | -------- | ----- | ---------------------- |
| **Brute Force**       | O(1)     | O(1)     | O(1)     | O(n)     | O(n)  | getMin slow            |
| **multiset**          | O(log n) | O(log n) | O(1)     | O(1)     | O(n)  | simple but not optimal |
| **pair stack**        | O(1)     | O(1)     | O(1)     | O(1)     | O(n)  | min stored with each   |
| **two-stack optimal** | **O(1)** | **O(1)** | **O(1)** | **O(1)** | O(n)  | best solution          |

---

# 🎯 **Final Recommendation**

Use **Approach 4 (two stacks)** in interviews.
Approach 3 (pair stack) is also fully acceptable.

Brute & multiset versions are good for learning, but not optimal.

---
