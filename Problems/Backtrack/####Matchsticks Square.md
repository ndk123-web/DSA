# 🟦 Matchsticks to Square

## 📌 Problem Statement

You are given an integer array `matchsticks`, where each element represents the length of a matchstick.
You must use **all matchsticks exactly once** to form **one square**.

Rules:

- You cannot break any stick
- You can connect sticks
- All four sides of the square must have equal length

Return `true` if it is possible, otherwise `false`.

---

## 🔍 Key Observation

- A square has **4 sides**
- Let total length = `sum`
- For a square to exist:

  ```
  sum % 4 == 0
  ```

- Each side must have length:

  ```
  target = sum / 4
  ```

---

## 🧠 Approach Overview

We solve this problem using **backtracking**, with two approaches:

1. **Brute Force DFS (Top/Bottom/Left/Right variables)**
2. **Optimized DFS using 4 Buckets (Accepted Solution)**

---

## 🟥 Approach 1 — Brute Force DFS (Initial Intuition)

### 💡 Idea

- Try to place each matchstick into one of the four sides:
  - `top`, `bottom`, `left`, `right`

- At every step, check:
  - No side exceeds `target`

- At the end:
  - All sides must be equal
  - All matchsticks must be used

---

### 💻 Code (Brute Force)

```cpp
class Solution {
private:
    bool dfs(vector<int>& nums, int t, int b, int l, int r,
             int idx, int total) {

        int side = total / 4;
        if (t > side || b > side || l > side || r > side)
            return false;

        if (t == b && l == r && t == l && idx == nums.size())
            return true;

        return dfs(nums, t + nums[idx], b, l, r, idx + 1, total) ||
               dfs(nums, t, b + nums[idx], l, r, idx + 1, total) ||
               dfs(nums, t, b, l + nums[idx], r, idx + 1, total) ||
               dfs(nums, t, b, l, r + nums[idx], idx + 1, total);
    }

public:
    bool makesquare(vector<int>& matchsticks) {
        int total = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        return dfs(matchsticks, 0, 0, 0, 0, 0, total);
    }
};
```

---

### ❌ Why This Approach Is Inefficient

- Each stick has **4 choices**
- Total states ≈ `4^n`
- **Symmetric states are explored repeatedly**

Example (same logical state, different variable names):

```
(2,0,0,0)
(0,2,0,0)
(0,0,2,0)
(0,0,0,2)
```

These are **identical**, but DFS explores all of them.

👉 Result: **Time Limit Exceeded (TLE)** for larger inputs.

---

## 🟩 Approach 2 — Optimized Backtracking (4 Buckets)

### 💡 Core Insight

> **Sides are interchangeable, matchsticks are not.**

So instead of tracking `top, bottom, left, right` separately, we use:

```
vector<int> sides(4)
```

This allows us to:

- Detect **symmetric duplicate states**
- Prune unnecessary branches early

---

### 🛠️ Optimizations Used

1. **Divisibility Check**

   ```
   if (sum % 4 != 0) return false;
   ```

2. **Descending Sort**

   ```
   sort(matchsticks.rbegin(), matchsticks.rend());
   ```

   → Big sticks fail early (fail-fast strategy)

3. **Capacity Pruning**

   ```
   if (sides[i] + stick > target) skip
   ```

4. **Symmetry Pruning (Most Important)**

   ```
   if (i > 0 && sides[i] == sides[i-1]) skip
   ```

---

### 💻 Code (Optimized & Accepted)

```cpp
class Solution {
private:
    vector<int> sq = vector<int>(4, 0);
    int target;

    bool dfs(vector<int>& nums, int idx) {
        if (idx == nums.size())
            return true;

        for (int i = 0; i < 4; i++) {
            // skip symmetric duplicate states
            if (i > 0 && sq[i] == sq[i - 1]) continue;

            if (sq[i] + nums[idx] > target) continue;

            sq[i] += nums[idx];
            if (dfs(nums, idx + 1))
                return true;
            sq[i] -= nums[idx];
        }
        return false;
    }

public:
    bool makesquare(vector<int>& matchsticks) {
        int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (sum % 4 != 0) return false;

        target = sum / 4;

        sort(matchsticks.rbegin(), matchsticks.rend());
        return dfs(matchsticks, 0);
    }
};
```

---

## ⏱️ Time Complexity

### Brute Force

- **O(4^n)**
- No symmetry pruning
- Explores redundant states

### Optimized

- Worst case: `O(4^n)`
- Practical runtime is **much faster** due to:
  - Early pruning
  - Symmetry elimination
  - Sorting

---

## 📦 Space Complexity

- Recursion depth: `O(n)`
- Side storage: constant `O(1)`

---

## 🔑 Key Insight (Interview Gold)

> “Using a 4-bucket array allows us to prune symmetric states, which drastically reduces the search space compared to tracking sides separately.”

---

## 🔄 Comparison Summary

| Aspect            | Brute Force | Optimized |
| ----------------- | ----------- | --------- |
| Idea clarity      | High        | High      |
| Symmetry handling | ❌ No       | ✅ Yes    |
| Pruning           | Weak        | Strong    |
| Performance       | TLE         | Accepted  |
| Interview-ready   | ❌          | ✅        |
