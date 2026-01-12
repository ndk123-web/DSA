# 📘 K Closest Points to Origin 

## Problem Summary

You are given a list of points on a 2D plane:

```
points[i] = [xi, yi]
```

The distance of a point from the origin `(0,0)` is:

```
distance = x² + y²
```

(We don’t take square root because relative order is enough.)

### Goal

Return the **k points closest to the origin**.

---

## Key Observation

This is a **Top-K problem**.

Whenever a problem asks for:

- k smallest
- k largest
- k closest
- k most frequent

👉 **Heap is the natural data structure**.

---

## Two Valid Approaches

We solve the same problem using **two heap strategies**:

1. **Min-Heap (n log n)** — simpler, but slower
2. **Max-Heap of size k (n log k)** — optimized and preferred

---

# 🟢 Solution 1 — Min-Heap (Straightforward)

### Code

```cpp
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<
            pair<int, vector<int>>,
            vector<pair<int, vector<int>>>,
            greater<pair<int, vector<int>>>
        > pq;

        vector<vector<int>> res;

        for (auto& point : points) {
            int dist = point[0]*point[0] + point[1]*point[1];
            pq.push({dist, point});
        }

        for (int i = 0; i < k; i++) {
            res.push_back(pq.top().second);
            pq.pop();
        }

        return res;
    }
};
```

---

## How This Works

1. Compute distance of **every point**
2. Push `(distance, point)` into a **min-heap**
3. Min-heap keeps **smallest distance at the top**
4. Pop top `k` elements → those are the k closest points

---

## Why This Is Correct

- Heap guarantees smallest distance on top
- We extract exactly `k` smallest distances
- Duplicates and order don’t matter

---

## Complexity Analysis

Let `n = number of points`

### Time

- Insert all points: `O(n log n)`
- Extract k points: `O(k log n)`

```
Overall: O(n log n)
```

### Space

```
O(n)  // heap stores all points
```

---

## Downsides

❌ Heap stores **all n points**
❌ More work than necessary
❌ Not optimal when `k << n`

---

## When to Use This

✅ When simplicity matters
✅ When n is small
❌ Not ideal for interviews or large inputs

---

# 🔵 Solution 2 — Max-Heap of Size k (Optimized)

### Code

```cpp
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<long long, pair<int,int>>> pq;
        vector<vector<int>> res;

        for (auto& point : points) {
            long long dist =
                (long long)point[0] * point[0] +
                (long long)point[1] * point[1];

            pq.push({dist, {point[0], point[1]}});

            if (pq.size() > k) {
                pq.pop(); // remove farthest
            }
        }

        while (!pq.empty()) {
            res.push_back({pq.top().second.first,
                           pq.top().second.second});
            pq.pop();
        }

        return res;
    }
};
```

---

## Core Idea (This Is the Key Insight)

> **We only care about the k closest points.
> Everything farther than the k-th closest is useless.**

So:

- Keep a heap of size **at most k**
- Always remove the **farthest** point when size exceeds k

---

## Why Max-Heap?

We want to remove the **farthest point** quickly.

So we use:

```
max-heap → top = farthest point
```

---

## How This Works (Step-by-Step)

For each point:

1. Compute distance
2. Push into max-heap
3. If heap size > k → pop the farthest point

At the end:

- Heap contains **exactly k closest points**
- Order does not matter

---

## Complexity Analysis

### Time

- For each point:

  - Push: `O(log k)`
  - Possible pop: `O(log k)`

```
Overall: O(n log k)
```

### Space

```
O(k)  // heap never grows beyond k
```

---

## Why This Is Better

| Aspect              | Min-Heap   | Max-Heap (k size) |
| ------------------- | ---------- | ----------------- |
| Time                | O(n log n) | ✅ O(n log k)     |
| Space               | O(n)       | ✅ O(k)           |
| Scales well         | ❌         | ✅                |
| Interview preferred | ❌         | ✅                |

---

## Why Distance Uses Squared Value

```cpp
x² + y²
```

- Square root is expensive
- Relative ordering is same
- Avoids floating-point issues

---

## Important Details

- Use `long long` for distance to avoid overflow
- Order of result does **not** matter
- Both solutions are correct

---

## Final Mental Model (Lock This In)

> **Top-K problems = Heap problems**

- Want smallest k → **max-heap of size k**
- Want largest k → **min-heap of size k**

---

## Final Recommendation

- Use **Solution 1** to understand the idea
- Use **Solution 2** in interviews and production
- If `k` is small and `n` is large → **always n log k**

---

### One-Line Takeaway

> **Don’t store everything if you only need the best k.**
