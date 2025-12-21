# 🎯 Guess Number Higher or Lower — Binary Search (Clean Explanation)

---

## 📘 Problem Summary

You are given a number `n`.

A secret number is chosen between **1 and n**.

You can only interact with the system using the API:

```cpp
int guess(int num);
```

### API behavior

| Return value | Meaning                                         |
| ------------ | ----------------------------------------------- |
| `-1`         | Your guess is **higher** than the secret number |
| `1`          | Your guess is **lower** than the secret number  |
| `0`          | Your guess is **correct**                       |

Your task is to **find the secret number** using the minimum number of guesses.

---

## 🧠 Why Binary Search?

- The search space is **sorted**: `[1 … n]`
- Each API call tells you whether to go **left or right**

This perfectly matches **binary search**.

---

## 💻 Correct Binary Search Implementation

```cpp
class Solution {
public:
    int guessNumber(int n) {
        int l = 1;
        int r = n;

        while (l <= r) {
            // Overflow-safe mid calculation
            int m = l + (r - l) / 2;
            int api = guess(m);

            if (api == 0) {
                return m;          // correct guess
            }
            else if (api == -1) {
                r = m - 1;         // guess too high
            }
            else {
                l = m + 1;         // guess too low
            }
        }

        return n; // fallback (never actually reached)
    }
};
```

---

## 🔑 Key Binary Search Invariant

> **The secret number always lies in the range `[l, r]`.**

Each API call shrinks this range until only one number remains.

---

## 🧪 Example Dry Run

```
Secret number = 6
n = 10
```

| l   | r   | m   | guess(m) | Action           |
| --- | --- | --- | -------- | ---------------- |
| 1   | 10  | 5   | 1        | Too low → l = 6  |
| 6   | 10  | 8   | -1       | Too high → r = 7 |
| 6   | 7   | 6   | 0        | Found answer     |

---

## ⚠️ Important: Mid Formula Difference

### ❌ Unsafe Formula

```cpp
m = (l + r) / 2;
```

### Problem

- `l + r` can **overflow** for large values
- Integer overflow causes **wrong mid values**
- Binary search may fail or loop incorrectly

---

### ✅ Safe Formula (Recommended)

```cpp
m = l + (r - l) / 2;
```

### Why this works

- `(r - l)` is always within bounds
- Prevents integer overflow
- Used in **FAANG interviews & production code**

---

## 🔍 Mathematical Note

Mathematically:

```
(l + r) / 2 == l + (r - l) / 2
```

But computers use **fixed-size integers**, not infinite precision math.

---

## 🧠 One-Line Mental Model (Lock This 🔒)

> **Binary search is correct only if mid calculation is overflow-safe.**

---

## ⏱️ Complexity Analysis

| Metric | Value    |
| ------ | -------- |
| Time   | O(log n) |
| Space  | O(1)     |

---

## ✅ Final Takeaways

- This problem is a textbook **binary search**
- Always search in `[1, n]`, not `[0, n]`
- Always use `l + (r - l) / 2` for mid
- Correct mid formula prevents silent bugs

---
