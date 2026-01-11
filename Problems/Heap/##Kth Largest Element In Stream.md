# 📘 Kth Largest Element in a Stream 

## Problem Recap (Plain English)

- You are given:

  - an integer `k`
  - a stream of integers (numbers come one by one)

- After each new number is added, you must return the **kth largest element so far**
- **Duplicates count**
- The stream is **not sorted**

---

## What “kth largest” really means

If `k = 3` and numbers are:

```
[1, 2, 3, 3]
```

Sorted descending:

```
3 (1st), 3 (2nd), 2 (3rd)
```

So the **3rd largest = 2**.

---

# ✅ Solution 1 — Sort Every Time (Brute Force)

### Code

```cpp
class KthLargest {
private:
    vector<int> arr;
    int kk;

public:
    KthLargest(int k, vector<int>& nums) {
        kk = k;
        for (auto& num : nums) {
            arr.push_back(num);
        }
    }

    int add(int val) {
        arr.push_back(val);

        // Sort in descending order
        sort(arr.begin(), arr.end(),
             [](int a, int b) { return a > b; });

        return arr[kk - 1];
    }
};
```

---

## How this solution works

### Constructor

- Stores all initial numbers in a vector

### add(val)

1. Add `val` to the vector
2. Sort the **entire vector** in descending order
3. Return the element at index `k-1`

---

## Why this solution is correct

- Sorting gives you the exact order
- Index `k-1` is always the kth largest
- Very easy to understand
- Good for learning and testing logic

---

## Why this solution is **bad**

### Time Complexity

Let `n` be total elements so far.

- `sort()` → **O(n log n)**
- This happens **every time `add()` is called**

This is extremely inefficient for a stream.

### Space Complexity

- **O(n)** (stores all numbers)

---

## When this solution is acceptable

- Small input
- One-time operation
- Learning / debugging
- **Not acceptable in interviews**

---

# ✅ Solution 2 — Min-Heap of Size `k` (Optimal)

### Code

```cpp
class KthLargest {
private:
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for (auto& num : nums) {
            pq.push(num);
            if (pq.size() > k)
                pq.pop();
        }
    }

    int add(int val) {
        pq.push(val);
        if (pq.size() > k)
            pq.pop();

        return pq.top();
    }
};
```

---

## Core Idea (This is the key insight)

> **Keep only the k largest elements seen so far.**

If you do that, then:

- The **smallest among those k elements**
- is exactly the **kth largest overall**

---

## Why a **min-heap**?

- Min-heap keeps the **smallest element on top**
- Heap size is always `k`
- So:

  ```
  pq.top() = kth largest
  ```

---

## How this solution works

### Constructor

For each number:

1. Push into min-heap
2. If heap size exceeds `k`, pop the smallest

Result:

- Heap contains only the `k` largest numbers so far

---

### add(val)

1. Push `val`
2. If heap size > `k`, pop smallest
3. Return `pq.top()`

---

## Dry Run Example

### k = 3

Initial nums = `[1, 2, 3, 3]`

Min-heap states:

```
[1]
[1,2]
[1,2,3]
[2,3,3]   // size > k → pop 1
```

`pq.top() = 2` → correct

### add(5)

```
push 5 → [2,3,3,5]
pop → [3,3,5]
```

`pq.top() = 3`

---

## Complexity Analysis

### Time Complexity

- Each `add()` → **O(log k)**
- Much faster than sorting

### Space Complexity

- **O(k)** (only stores k elements)

---

## Why this is the correct design

| Aspect             | Sorting Solution | Heap Solution |
| ------------------ | ---------------- | ------------- |
| Correctness        | ✅               | ✅            |
| Time               | ❌ O(n log n)    | ✅ O(log k)   |
| Space              | ❌ O(n)          | ✅ O(k)       |
| Streaming-friendly | ❌               | ✅            |
| Interview-ready    | ❌               | ✅            |

---

## Common Doubts Explained

### ❓ Why not max-heap?

Because:

- Max-heap gives **largest**
- We need **kth largest**
- We’d have to pop `k-1` times every add → inefficient

---

### ❓ Why duplicates are not a problem?

Because:

- Heap stores values, not indices
- Each value counts separately

---

### ❓ Why we don’t store all elements?

Because:

- Elements smaller than kth largest are useless
- They can never affect future answers

---

## Final Mental Model (Lock This)

> **Min-heap of size `k` = sliding window of k largest elements**

- Top of heap = answer
- Everything else is irrelevant
