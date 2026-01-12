# 📘 K Closest Points to Origin

## Problem Summary

You are given a list of points on a 2D plane:

```
points[i] = [xi, yi]
```

The distance of a point from the origin `(0, 0)` is:

```
distance = x² + y²
```

> We do **not** take the square root because relative ordering is sufficient.

### Goal

Return the **k points closest to the origin**.
The order of the returned points does **not** matter.

---

## Key Observation

This is a classic **Top-K problem**.

Whenever a problem asks for:

- k smallest
- k largest
- k closest
- k most frequent

👉 **Heap or Selection algorithms are the natural tools**.

---

## Approaches Covered

We solve the same problem using **three different strategies**, each with different trade-offs:

1. **Min-Heap (n log n)** — simple, brute-force
2. **Max-Heap of size k (n log k)** — optimized and preferred
3. **Quickselect (average O(n))** — fastest in practice for static input

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

1. Compute distance for **every point**
2. Push `(distance, point)` into a **min-heap**
3. The heap keeps the **closest point on top**
4. Pop the top `k` elements

---

## Complexity Analysis

Let `n = number of points`.

### Time

```
O(n log n)
```

### Space

```
O(n)   // heap stores all points
```

---

## Downsides

❌ Stores all `n` points
❌ More work than necessary
❌ Not optimal when `k << n`

---

## When to Use

✅ Easy to understand
❌ Not interview-optimal
❌ Poor scalability

---

# 🔵 Solution 2 — Max-Heap of Size k (Optimized Heap)

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
            res.push_back({
                pq.top().second.first,
                pq.top().second.second
            });
            pq.pop();
        }

        return res;
    }
};
```

---

## Core Idea

> **We only care about the k closest points.
> Everything farther than the k-th closest is irrelevant.**

So we:

- Keep a heap of size **at most k**
- Remove the **farthest** point whenever size exceeds k

---

## Why Max-Heap?

We want to remove the **farthest** point quickly:

```
max-heap → top = farthest point
```

---

## Complexity Analysis

### Time

```
O(n log k)
```

### Space

```
O(k)
```

---

## Why This Is Better Than Solution 1

| Aspect           | Min-Heap   | Max-Heap (k size) |
| ---------------- | ---------- | ----------------- |
| Time             | O(n log n) | ✅ O(n log k)     |
| Space            | O(n)       | ✅ O(k)           |
| Scales well      | ❌         | ✅                |
| Interview choice | ❌         | ✅                |

---

# 🟣 Solution 3 — Quickselect (Selection Algorithm)

### Code

```cpp
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        quickselect(points, 0, points.size() - 1, k);
        return vector<vector<int>>(points.begin(), points.begin() + k);
    }

    void quickselect(vector<vector<int>>& points, int left, int right, int k) {
        if (left >= right) return;

        int pivotIndex = partition(points, left, right);

        if (pivotIndex == k) return;
        else if (pivotIndex < k)
            quickselect(points, pivotIndex + 1, right, k);
        else
            quickselect(points, left, pivotIndex - 1, k);
    }

    int partition(vector<vector<int>>& points, int left, int right) {
        long long pivotDist = dist(points[right]);
        int p = left;

        for (int i = left; i < right; i++) {
            if (dist(points[i]) <= pivotDist) {
                swap(points[i], points[p]);
                p++;
            }
        }
        swap(points[p], points[right]);
        return p;
    }

    long long dist(const vector<int>& p) {
        return (long long)p[0]*p[0] + (long long)p[1]*p[1];
    }
};
```

---

## Core Idea

Quickselect is based on **Quicksort’s partitioning**, but:

> Instead of fully sorting the array,
> we recurse only into the side that contains the k closest points.

After partitioning:

```
[ closer points | pivot | farther points ]
```

We only continue on the side that still needs processing.

---

## Why This Works

- After Quickselect finishes, the **first k elements** are the k closest
- Order inside those k elements does **not** matter
- No heap required
- In-place algorithm

---

## Complexity Analysis

### Average Case

```
Time  : O(n)
Space : O(1)
```

### Worst Case

```
Time  : O(n²)
```

Worst case occurs with consistently bad pivot choices.

---

## Heap vs Quickselect — Comparison

| Aspect         | Heap (n log k) | Quickselect |
| -------------- | -------------- | ----------- |
| Average Time   | O(n log k)     | ✅ O(n)     |
| Worst Case     | O(n log k)     | ❌ O(n²)    |
| Space          | O(k)           | ✅ O(1)     |
| Streaming      | ✅ Yes         | ❌ No       |
| Deterministic  | ✅ Yes         | ❌ No       |
| Interview Safe | ✅ Yes         | ⚠️ Depends  |

---

## When to Use Which

- **Streaming input** → Heap
- **Large n, small k** → Max-heap of size k
- **Static input, fastest average** → Quickselect
- **Interview safest** → Heap

---

## Why Distance Uses Squared Value

```cpp
x² + y²
```

- Square root is unnecessary
- Ordering remains the same
- Avoids floating-point errors

---

## Final Mental Model (Lock This In)

> **Top-K problems have two families of solutions:**
>
> - **Heap** → stable, streaming, guaranteed
> - **Quickselect** → fast, in-place, average-optimal

---

## Final Recommendation

- Learn **Solution 2 (Heap)** first
- Understand **Solution 3 (Quickselect)** for optimization
- Choose based on **constraints**, not preference

---

### One-Line Takeaway

> **Don’t sort the whole world when you only need the best k.**
