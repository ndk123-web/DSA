# 🔁 Partition to K Equal Sum Subsets

## 📌 Problem Statement

Given an integer array `nums` and an integer `k`, determine if it is possible to divide the array into **k non-empty subsets** such that the **sum of each subset is equal**.

---

## 🔍 Key Observation

- Let total sum = `S`
- Each subset must have sum = `S / k`
- If `S % k != 0`, it is **impossible**
- Each element must be used **exactly once**

---

# 🟠 Solution 1 — Basic Backtracking (Brute Force)

## 🧠 Intuition

- Try to build subsets one by one
- Maintain a `used[]` array to avoid reusing elements
- Keep adding elements to current subset until its sum reaches `target`
- Once a subset is complete, move to the next subset

This solution is **correct**, but **inefficient**.

---

## 🛠️ Approach

1. Compute total sum
2. If `sum % k != 0`, return false
3. Use DFS to build subsets
4. When current subset reaches `target`, move to next subset
5. Stop when all `k` subsets are formed

---

## 💻 Code

```cpp
class Solution {
private:
    vector<bool> used;
    int target;

    bool backtrack(vector<int>& nums, int k, int cSum, int st) {
        if (k == 0)
            return true;

        if (cSum == target)
            return backtrack(nums, k - 1, 0, 0);

        for (int i = st; i < nums.size(); i++) {
            if (used[i] || nums[i] + cSum > target)
                continue;

            used[i] = true;
            if (backtrack(nums, k, cSum + nums[i], i + 1))
                return true;
            used[i] = false;
        }
        return false;
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0)
            return false;

        target = sum / k;
        used.assign(nums.size(), false);

        sort(nums.rbegin(), nums.rend());
        return backtrack(nums, k, 0, 0);
    }
};
```

---

## ⏱️ Complexity

- **Time:** `O(k^n)` (very slow in worst case)
- **Space:** `O(n)` (recursion + used array)

---

## ❌ Drawback

- Explores many unnecessary branches
- No symmetry pruning
- Likely to TLE on large inputs

---

# 🟡 Solution 2 — Backtracking + `k == 1` Optimization

## 🧠 Key Improvement

> If `k - 1` subsets are successfully formed,
> the remaining elements **must** form the last subset.

So:

```cpp
if (k == 1) return true;
```

This avoids building the final subset explicitly.

---

## 🛠️ Approach Changes

- Same DFS logic
- Add early exit when `k == 1`

---

## 💻 Code

```cpp
class Solution {
private:
    vector<bool> used;
    int target;

    bool backtrack(vector<int>& nums, int k, int cSum, int st) {
        if (k == 1)
            return true;

        if (cSum == target)
            return backtrack(nums, k - 1, 0, 0);

        for (int i = st; i < nums.size(); i++) {
            if (used[i] || cSum + nums[i] > target)
                continue;

            used[i] = true;
            if (backtrack(nums, k, cSum + nums[i], i + 1))
                return true;
            used[i] = false;
        }
        return false;
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0)
            return false;

        target = sum / k;
        used.assign(nums.size(), false);

        sort(nums.rbegin(), nums.rend());
        return backtrack(nums, k, 0, 0);
    }
};
```

---

## ⏱️ Complexity

- **Time:** `O(k^n)` (still exponential)
- **Space:** `O(n)`

---

## 🟢 Improvement

- Avoids unnecessary DFS for last subset
- Faster than brute force
- Still has duplicate symmetric states

---

# 🟢 Solution 3 — Optimized Backtracking (Final Accepted)

## 🧠 Core Insight (Most Important)

> Subsets are **indistinguishable**
> Trying the same value as the first element of an empty subset multiple times creates **duplicate states**

### Symmetry Pruning Rule

```cpp
if (cSum == 0)
    break;
```

Meaning:

- If starting a subset with one value fails,
- Starting with another identical value is pointless

---

## 🛠️ Full Optimized Approach

- Sort descending → fail fast
- `k == 1` early return
- `used[]` to prevent reuse
- Symmetry pruning when `cSum == 0`

---

## 💻 Code (Final Version)

```cpp
class Solution {
private:
    vector<bool> used;
    int target;

    bool backtrack(vector<int>& nums, int k, int cSum, int st) {
        if (k == 1)
            return true;

        if (cSum == target)
            return backtrack(nums, k - 1, 0, 0);

        for (int i = st; i < nums.size(); i++) {
            if (used[i] || cSum + nums[i] > target)
                continue;

            used[i] = true;
            if (backtrack(nums, k, cSum + nums[i], i + 1))
                return true;
            used[i] = false;

            // symmetry pruning
            if (cSum == 0)
                break;
        }
        return false;
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0)
            return false;

        target = sum / k;
        used.assign(nums.size(), false);

        sort(nums.rbegin(), nums.rend());
        if (nums[0] > target)
            return false;

        return backtrack(nums, k, 0, 0);
    }
};
```

---

## ⏱️ Final Complexity

- **Time:** `O(k^n)` worst case
  (much faster in practice due to pruning)
- **Space:** `O(n)`

---

## 🔑 Final Takeaways

- Target sum is **fixed**, not guessed
- DFS state design matters more than brute force
- Symmetry pruning reduces exponential explosion
- This pattern generalizes:
  - Matchsticks to Square
  - Partition to K Subsets
  - Subset-based backtracking problems

---

## 🎯 Interview One-Liner

> “We backtrack by filling subsets up to `sum/k`, marking used elements, and prune symmetric states when starting a new subset.”
