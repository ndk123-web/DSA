---

# 📘 **Implement Stack Using Queues — Complete Guide**

You must implement a **Stack (LIFO)** using **Queue(s) (FIFO)**.

Stack operations required:

| Operation | Meaning         |
| --------- | --------------- |
| `push(x)` | Insert at top   |
| `pop()`   | Remove from top |
| `top()`   | Return top      |
| `empty()` | Check if empty  |

---

# # 🎯 **Core Idea**

A queue normally gives:

```
push → back
pop → front
```

But a **stack** needs:

```
push → top
pop → top
```

So we need to manipulate the queue(s) so that the **most recent element becomes the front**.

There are two ways:

### ✔ Approach 1 — One queue + rearranging

### ✔ Approach 2 — Two queues (optimized, standard)

---

# # 🥉 **Approach 1 — Single Queue + Temporary Queue**

### **Time Complexity**

- `push` → O(1)
- `pop` → O(n)` (we remove all items except last)
- `top` → O(1)`

### **Idea**

- `push(x)` → normal push to queue
- `pop()` →

  - Take last inserted element (queue.back())
  - Move all other elements to a temp queue
  - Replace original queue with temp

---

### **Code (with short comments)**

```cpp
class MyStack {
private:
    queue<int> q;

public:
    MyStack() {}

    void push(int x) {
        q.push(x);                      // normal queue push
    }

    int pop() {
        queue<int> temp;
        int val = q.back();             // last inserted = stack's top

        // move all except last into temp
        while (!q.empty()) {
            if (q.front() != val) {
                temp.push(q.front());
            }
            q.pop();
        }

        q = temp;                       // restore remaining elements
        return val;
    }

    int top() {
        return q.back();                // last element behaves like top
    }

    bool empty() {
        return q.empty();
    }
};
```

---

# # 🥇 **Approach 2 — Two Queues (Optimized & Recommended)**

### ⭐ **push = O(n)**

### ⭐ **pop = O(1)**

### ⭐ **top = O(1)**

### **Idea**

To simulate stack behavior, after every push:

1. Insert element into `q2`
2. Move all elements from `q1 → q2`
3. Swap queues
4. Now `q1.front()` is always the **top of stack**

This ensures:

- pop = pop front from q1
- top = q1.front()
- empty = q1.empty()

---

### **Code (with short comments)**

```cpp
class MyStack {
private:
    queue<int> q1, q2;

public:
    MyStack() {}

    void push(int x) {
        q2.push(x);                    // new element added to q2 first

        // move all previous elements behind it
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }

        swap(q1, q2);                  // q1 now has newest element in front
    }

    int pop() {
        int val = q1.front();          // this is the top of stack
        q1.pop();
        return val;
    }

    int top() {
        return q1.front();             // front always = top
    }

    bool empty() {
        return q1.empty();
    }
};
```

---

# # 🏁 **Approach Comparison**

| Approach                 | push | pop  | top  | Space | Notes                |
| ------------------------ | ---- | ---- | ---- | ----- | -------------------- |
| **1 Queue + Temp Queue** | O(1) | O(n) | O(1) | O(n)  | Simple but pop slow  |
| **2 Queue Optimized**    | O(n) | O(1) | O(1) | O(n)  | Standard & efficient |

---

# # 🎯 Final Takeaway

To implement a stack using queues:

- **Approach 1** works but is inefficient for frequent pops.
- **Approach 2** is the classic optimal version:
  - After each push, the newest element comes to the front.
  - pop & top become O(1) and very efficient.

---
