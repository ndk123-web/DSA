# 📘 Kth Largest Element in an Array 

## Problem Summary

You are given an integer array `nums` and an integer `k`.

### Goal

Return the **kth largest element** in the array.

### Important Notes

- The array is **not sorted**
- **Duplicates count**
- You need the **value**, not the index

---

## Understanding “kth largest”

Example:

```
nums = [3, 2, 1, 5, 6, 4]
k = 2
```

Sorted descending:

```
6 (1st), 5 (2nd), 4, 3, 2, 1
```

Answer:

```
5
```

---

## Approaches Covered

We solve the same problem using **four different strategies**, from simplest to most optimized:

1. Sorting (ascending)
2. Sorting (descending with comparator)
3. Min-Heap of size `k` (Top-K pattern)
4. Quickselect (selection algorithm)

---

# 🟢 Solution 1 — Sort (Ascending)

### Code

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};
```

---

## How This Works

1. Sort the array in **ascending order**
2. The kth largest element will be at index:

   ```
   nums.size() - k
   ```

---

## Complexity

```
Time  : O(n log n)
Space : O(1) / O(n) (depends on sort implementation)
```

---

## Pros / Cons

✅ Very simple
❌ Sorts entire array (unnecessary work)
❌ Not optimal for large inputs

---

## When to Use

- Learning
- Small input sizes
- Quick sanity checks

---

# 🟢 Solution 2 — Sort (Descending with Comparator)

### Code

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end(),
             [](auto& a, auto& b) { return a > b; });
        return nums[k - 1];
    }
};
```

---

## How This Works

1. Sort the array in **descending order**
2. The kth largest element is directly at index:

   ```
   k - 1
   ```

---

## Complexity

```
Time  : O(n log n)
Space : O(1) / O(n)
```

---

## Pros / Cons

✅ Very intuitive
❌ Same inefficiency as Solution 1
❌ Still sorts everything

---

## When to Use

- When clarity > performance
- Interviews only if constraints are small

---

# 🔵 Solution 3 — Min-Heap of Size k (Optimized)

### Code

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;

        for (auto& num : nums) {
            pq.push(num);
            if (pq.size() > k) {
                pq.pop();
            }
        }

        return pq.top();
    }
};
```

---

## Core Idea (Top-K Pattern)

> **Keep only the k largest elements seen so far.**

- Use a **min-heap**
- Heap size never exceeds `k`
- The smallest element in the heap = kth largest overall

---

## How This Works

For each number:

1. Push it into the heap
2. If heap size exceeds `k`, pop the smallest element

At the end:

- Heap contains the **k largest elements**
- `pq.top()` is the **kth largest**

---

## Complexity

```
Time  : O(n log k)
Space : O(k)
```

---

## Why This Is Better Than Sorting

| Aspect         | Sorting    | Heap          |
| -------------- | ---------- | ------------- |
| Time           | O(n log n) | ✅ O(n log k) |
| Space          | O(n)       | ✅ O(k)       |
| Streaming      | ❌         | ✅            |
| Interview-safe | ❌         | ✅            |

---

## When to Use

✅ Best interview solution
✅ Best for large `n`, small `k`
✅ Works for streaming data

---

# 🟣 Solution 4 — Quickselect (Selection Algorithm)

### Code

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickselect(nums, 0, nums.size() - 1, nums.size() - k);
    }

    int quickselect(vector<int>& nums, int left, int right, int k) {
        int pivot = nums[right];
        int p = left;

        for (int i = left; i < right; i++) {
            if (nums[i] <= pivot) {
                swap(nums[i], nums[p]);
                p++;
            }
        }
        swap(nums[p], nums[right]);

        if (p < k)
            return quickselect(nums, p + 1, right, k);
        else if (p > k)
            return quickselect(nums, left, p - 1, k);
        else
            return nums[p];
    }
};
```

---

## Core Idea

Quickselect is based on **Quicksort partitioning**, but:

> Instead of fully sorting the array,
> we recurse only into the part that contains the answer.

---

## Why `nums.size() - k`?

Quickselect naturally finds the **kth smallest** element.

But:

```
kth largest = (n - k)th smallest
```

So we convert the problem.

---

## Complexity

### Average Case

```
Time  : O(n)
Space : O(1)
```

### Worst Case

```
Time  : O(n²)
```

Worst case happens with poor pivot choices.

---

## Heap vs Quickselect

| Aspect        | Heap       | Quickselect |
| ------------- | ---------- | ----------- |
| Average Time  | O(n log k) | ✅ O(n)     |
| Worst Case    | O(n log k) | ❌ O(n²)    |
| Space         | O(k)       | ✅ O(1)     |
| Streaming     | ✅ Yes     | ❌ No       |
| Deterministic | ✅ Yes     | ❌ No       |

---

## Final Comparison of All Solutions

| Solution     | Time          | Space   | Use Case      |
| ------------ | ------------- | ------- | ------------- |
| Sort (asc)   | O(n log n)    | O(n)    | Learning      |
| Sort (desc)  | O(n log n)    | O(n)    | Clarity       |
| Min-Heap (k) | ✅ O(n log k) | ✅ O(k) | Best overall  |
| Quickselect  | ✅ O(n) avg   | O(1)    | Static arrays |

---

## Final Mental Model (Lock This In)

> **If the problem says “kth”, think Top-K.**
>
> - Streaming / safe → Heap
> - Static / fastest → Quickselect

---

## Final Recommendation

- **Interview default** → Heap (Solution 3)
- **Performance-critical, static input** → Quickselect
- **Never sort blindly if k is small**

---

### One-Line Takeaway

> **Don’t fully sort the array when you only need one rank.**
