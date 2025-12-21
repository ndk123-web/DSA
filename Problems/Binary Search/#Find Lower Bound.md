# 🔍 Search Insert Position (Lower Bound Problem)

---

## 📘 Problem Summary

You are given a **sorted array** `nums` and an integer `target`.

You must return:

- The **index of `target`** if it exists
- Otherwise, the **index where `target` should be inserted** to keep the array sorted

---

## 🧠 Core Insight (Very Important)

> This problem is exactly the definition of **lower_bound**

### What is `lower_bound`?

> The **first index `i` such that `nums[i] ≥ target`**

That index is either:

- the position of `target`
- or the correct insertion position

---

## ✅ Solution 1 — Manual Binary Search

### 💡 Idea

We maintain two pointers:

- `l` → possible insertion start
- `r` → possible insertion end

Binary search shrinks the range.

When the loop ends:

- `l` always points to the **correct insertion index**

---

### 💻 Code (With Short Comments)

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r) {
            int m = (l + r) / 2;

            if (nums[m] < target) {
                l = m + 1;      // target is on the right
            }
            else if (nums[m] > target) {
                r = m - 1;      // target is on the left
            }
            else {
                return m;       // exact match found
            }
        }

        // l is the correct insertion position
        return l;
    }
};
```

---

### 🧠 Why `return l` Works

At loop end:

```
l > r
```

This means:

- all elements **before `l` are < target**
- all elements **from `l` onward are ≥ target**

So inserting at index `l` keeps the array sorted.

---

### ⏱️ Complexity

| Metric | Value    |
| ------ | -------- |
| Time   | O(log n) |
| Space  | O(1)     |

---

## ✅ Solution 2 — Using STL `lower_bound`

### 💡 Idea

C++ STL already provides this logic.

```cpp
lower_bound(begin, end, target)
```

Returns an iterator pointing to:

> **first element ≥ target**

---

### 💻 Code (Cleanest Form)

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    }
};
```

---

### ⏱️ Complexity

| Metric | Value    |
| ------ | -------- |
| Time   | O(log n) |
| Space  | O(1)     |

---

## 🔍 Example Dry Run

```
nums   = [-1, 0, 2, 4, 6, 8]
target = 5
```

`lower_bound` returns index **4** because:

```
nums[3] = 4 < 5
nums[4] = 6 ≥ 5
```

So insert position = **4**

---

## 🧠 Final Comparison

| Approach             | Pros                         | Cons          |
| -------------------- | ---------------------------- | ------------- |
| Manual Binary Search | Interview‑ready, logic clear | More code     |
| `lower_bound`        | Clean, safe, standard        | Must know STL |

---

## 🔒 One‑Line Mental Model (Lock This)

> **Search Insert Position = lower_bound = first index where value ≥ target**

---

## ✅ Final Takeaway

Both solutions are **100% correct**.

- Use **manual binary search** in interviews
- Use **`lower_bound`** in production code

Once you understand `return l`, this problem becomes trivial.
