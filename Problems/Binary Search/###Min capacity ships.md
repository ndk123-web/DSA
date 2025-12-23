# 🚢 Capacity To Ship Packages Within D Days

---

## 🔹 Problem Restatement (Simple Words)

- You are given package weights in a **fixed order**
- You have exactly **`days` number of shipments**
- Every day:

  - You load packages **from left to right**
  - You stop when capacity is exceeded
  - Remaining packages go to the next day

- You **cannot reorder or split packages**

👉 Find the **minimum ship capacity** so all packages are shipped within `days`.

---

## 🔑 Key Insight (Most Important)

For a given ship capacity `C`:

- We can **simulate** shipping
- Count how many days (`ships`) it takes
- If `ships ≤ days` → capacity works
- If `ships > days` → capacity too small

Also:

- Smaller capacity → more days
- Larger capacity → fewer days

👉 This monotonic behavior enables **Binary Search**

---

# ✅ Solution 1: Brute Force (Linear Capacity Increase)

### 🧠 Idea

- Minimum capacity must be at least `max(weights)`
- Try increasing capacity until shipping fits in `days`

---

### 💻 Code with Proper Comments

```cpp
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        // Minimum possible capacity
        int res = *max_element(weights.begin(), weights.end());

        while (true) {
            int cap = res;     // remaining capacity for the day
            int ships = 1;     // day count (at least 1 day)

            for (auto& w : weights) {
                // If current package doesn't fit, use a new day
                if (cap - w < 0) {
                    ships++;
                    cap = res;
                }
                cap -= w;
            }

            // If total days used is within limit, return capacity
            if (ships <= days) return res;

            // Otherwise, increase capacity
            res++;
        }
    }
};
```

---

### ⏱ Time Complexity

```
O((sum(weights) - max(weights)) × n)
```

❌ Can be slow for large inputs
✅ Good for understanding logic

---

# ✅ Solution 2: Binary Search (Optimal & Expected)

---

## 🔍 Why Binary Search Works Here

Capacity range:

```
min = max(weights)
max = sum(weights)
```

This range is **monotonic**:

- If capacity works → any bigger capacity also works
- If capacity fails → any smaller capacity also fails

Perfect for binary search.

---

### 🧠 Helper Function Logic

```cpp
bool canShip(int cap, vector<int>& weights, int days)
```

- Simulates shipping
- Returns whether capacity `cap` finishes within `days`

---

### 💻 Code with Proper Comments

```cpp
class Solution {
private:
    bool canShip(int minCap, vector<int>& weights, int days) {
        int ships = 1;        // current day
        int cap = minCap;    // remaining capacity

        for (auto& w : weights) {
            if (cap - w < 0) {
                ships++;         // need another day
                cap = minCap;
            }
            cap -= w;
        }

        return ships <= days;
    }

public:
    int shipWithinDays(vector<int>& nums, int days) {
        int left = *max_element(nums.begin(), nums.end());
        int right = accumulate(nums.begin(), nums.end(), 0);
        int res = left;

        while (left <= right) {
            int minCap = left + (right - left) / 2;

            if (canShip(minCap, nums, days)) {
                res = minCap;          // possible answer
                right = minCap - 1;    // try smaller
            } else {
                left = minCap + 1;     // need larger capacity
            }
        }

        return res;
    }
};
```

---

### ⏱ Time Complexity

```
O(n log(sum(weights)))
```

✅ Optimal
✅ Interview-ready
✅ Scales well

---

# 🧪 Simple Dry Run

### Input

```
weights = [1,2,3,4,5]
days = 3
```

---

### Try capacity = 5

| Day | Packages | Load |
| --- | -------- | ---- |
| 1   | 1,2      | 3    |
| 2   | 3        | 3    |
| 3   | 4        | 4    |
| 4   | 5        | 5    |

❌ 4 days → fails

---

### Try capacity = 6

| Day | Packages | Load |
| --- | -------- | ---- |
| 1   | 1,2,3    | 6    |
| 2   | 4        | 4    |
| 3   | 5        | 5    |

✅ 3 days → works
➡ Minimum capacity = **6**

---

# 🧠 Final Takeaways (Must Remember)

- Order **cannot** change
- Capacity must be ≥ max weight
- Simulation is straightforward
- Binary Search is applied on **answer space**
- Pattern repeats in many problems:

  - Koko Eating Bananas
  - Split Array Largest Sum
  - Allocate Books

---

## 🎯 Interview One-Liner

> “We binary search on ship capacity since required days decrease monotonically as capacity increases.”

---
