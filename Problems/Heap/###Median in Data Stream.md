# Find Median from Data Stream 

## Problem Summary

Design a data structure that supports:

1. `addNum(int num)` → add a number from a stream
2. `findMedian()` → return the median of all numbers so far

### What is Median?

- If count is **odd** → middle element
- If count is **even** → average of two middle elements

---

## 🔑 Core Challenge

The numbers arrive **one by one (stream)**.
We must be able to:

- Insert efficiently
- Get median efficiently **at any time**

---

# 🟢 Solution 1 — Two Heaps (Optimal & Interview Standard)

### Key Idea (THIS IS THE HEART)

Split the numbers into **two halves**:

- **Left part (max-heap)** → smaller half
- **Right part (min-heap)** → larger half

### Invariants (Always True)

1. `leftPart.size()` and `rightPart.size()` differ by **at most 1**
2. Every element in `leftPart` ≤ every element in `rightPart`

If we maintain these, median is trivial.

---

## Why Two Heaps?

| Heap             | Purpose                 |
| ---------------- | ----------------------- |
| Max-heap (left)  | Largest of smaller half |
| Min-heap (right) | Smallest of larger half |

Median is always at the **top(s)**.

---

## Code (Two Heaps) — with Short Comments

```cpp
class MedianFinder {
private:
    // Max-heap for left (smaller half)
    priority_queue<int> leftPart;

    // Min-heap for right (larger half)
    priority_queue<int, vector<int>, greater<int>> rightPart;

public:
    MedianFinder() {}

    void addNum(int num) {
        // Step 1: always push into left heap
        leftPart.push(num);

        // Step 2: maintain ordering property
        if (!rightPart.empty() && leftPart.top() > rightPart.top()) {
            rightPart.push(leftPart.top());
            leftPart.pop();
        }

        // Step 3: balance sizes
        if (leftPart.size() > rightPart.size() + 1) {
            rightPart.push(leftPart.top());
            leftPart.pop();
        }

        if (rightPart.size() > leftPart.size() + 1) {
            leftPart.push(rightPart.top());
            rightPart.pop();
        }
    }

    double findMedian() {
        if (leftPart.size() == rightPart.size()) {
            return (leftPart.top() + rightPart.top()) / 2.0;
        }
        return (leftPart.size() > rightPart.size())
               ? leftPart.top()
               : rightPart.top();
    }
};
```

---

## Dry Run (Two Heaps)

### Stream: `1, 5, 2, 10`

#### Add 1

```
left = [1]
right = []
median = 1
```

#### Add 5

```
left = [1]
right = [5]
median = (1+5)/2 = 3
```

#### Add 2

```
left = [2,1]
right = [5]
median = 2
```

#### Add 10

```
left = [2,1]
right = [5,10]
median = (2+5)/2 = 3.5
```

---

## Complexity (Two Heaps)

```
addNum   → O(log n)
findMedian → O(1)
Space → O(n)
```

✅ **Best possible for streaming**

---

# 🔵 Solution 2 — Sorting Every Time (Brute Force)

### Idea

- Store all numbers in a vector
- Sort when median is needed
- Pick middle element(s)

### Simple but inefficient.

---

## Code (Brute Force)

```cpp
class MedianFinder {
private:
    vector<int> data;

public:
    MedianFinder() {}

    void addNum(int num) {
        data.push_back(num);
    }

    double findMedian() {
        sort(data.begin(), data.end());
        int n = data.size();

        if (n % 2 == 0) {
            return (data[n/2] + data[n/2 - 1]) / 2.0;
        } else {
            return data[n/2];
        }
    }
};
```

---

## Dry Run (Brute Force)

### Stream: `1, 5, 2`

Stored data:

```
[1,5,2]
→ sort → [1,2,5]
median = 2
```

Works, but expensive.

---

## Complexity (Brute Force)

```
addNum   → O(1)
findMedian → O(n log n)
Space → O(n)
```

❌ Too slow for large streams

---

# 🆚 Comparison

| Feature         | Two Heaps | Sort Every Time |
| --------------- | --------- | --------------- |
| addNum          | O(log n)  | O(1)            |
| findMedian      | O(1)      | O(n log n)      |
| Streaming       | ✅        | ❌              |
| Interview-ready | ✅        | ❌              |
| Optimal         | ✅        | ❌              |

---

## 🧠 Mental Model (Lock This In)

> Median splits numbers into **left half** and **right half**
> Heaps let you maintain this split dynamically.

---

## 🔑 Final Takeaways

- Streaming + median → **Two heaps**
- Keep heaps balanced
- Median always at heap tops
- Sorting approach is only for learning

---

### One-line Summary

> **Two heaps maintain a dynamic sorted split of the stream, giving O(1) median retrieval.**
