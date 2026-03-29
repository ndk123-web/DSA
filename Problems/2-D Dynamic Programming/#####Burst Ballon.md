# Burst Balloons (LeetCode 312)

## Intuition

This problem looks like a greedy or simulation problem at first:

```text
Burst balloons one by one and collect coins
```

But that approach fails because:

```text
Bursting changes neighbors dynamically → hard to track
```

---

## Key Idea (Important Insight)

Instead of thinking:

```text
Which balloon to burst FIRST ❌
```

We think:

```text
Which balloon to burst LAST ✅
```

---

## Why LAST works?

If we choose a balloon `k` as the **last balloon** in interval `[i, j]`:

* All other balloons in `[i, j]` are already burst
* So neighbors of `k` become:

```text
nums[i-1] and nums[j+1] (fixed and stable)
```

---

## DP Definition

```text
dfs(i, j) = maximum coins from bursting balloons in range [i, j]
```

---

## Transition

For each `k ∈ [i, j]`:

```text
dfs(i, j) = max(
    dfs(i, k-1) + 
    nums[i-1] * nums[k] * nums[j+1] + 
    dfs(k+1, j)
)
```

---

## Base Case

```text
If i > j → no balloons → 0
```

---

## Boundary Trick (Very Important)

We add `1` at both ends:

```text
[1, nums..., 1]
```

This removes edge cases and guarantees valid neighbors.

---

## Code (Top-Down DP)

```cpp
class Solution {
private: 
    vector<vector<int>> dp;

    // dfs(i, j) = max coins from interval [i, j]
    int dfs(vector<int>& nums, int i, int j) {
        // no balloons left
        if (i > j) {
            return 0;
        }
        
        // already computed
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        int res = 0;

        // try every k as the LAST balloon to burst
        for (int k = i; k <= j; k++) {

            // coins gained when k is last
            // neighbors are fixed: nums[i-1] and nums[j+1]
            int prodBallon = nums[k] * nums[i-1] * nums[j + 1];

            // left + current + right
            int currRes = dfs(nums, i, k - 1) + prodBallon + dfs(nums, k + 1, j);

            res = max(res, currRes);
        }

        return dp[i][j] = res;
    }

public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();

        // new array with boundaries
        vector<int> newnums(n + 2, 0);

        // dp table
        dp.assign(n + 1, vector<int>(n + 1, -1));

        // shift original values
        for (int i = 1; i <= n; i++) {
            newnums[i] = nums[i - 1];
        }      

        // neutral boundaries
        newnums[0] = 1;
        newnums[newnums.size() - 1] = 1;

        // solve for full range
        return dfs(newnums, 1, newnums.size() - 2);
    }
};
```

---

# Dry Run (Deep Understanding)

## Input

```text
nums = [3,1,5]
```

After adding boundaries:

```text
[1, 3, 1, 5, 1]
index: 0  1  2  3  4
```

We solve:

```text
dfs(1, 3)
```

---

## Try all k

---

### 🔹 Case 1: k = 1 (3 is LAST)

```text
coins = nums[0] * nums[1] * nums[4] = 1 * 3 * 1 = 3
```

Subproblems:

```text
left  = dfs(1,0) = 0
right = dfs(2,3)
```

---

#### Solve dfs(2,3)

* k = 2 → total = 8
* k = 3 → total = 30

```text
dfs(2,3) = 30
```

---

Total:

```text
3 + 30 = 33
```

---

### 🔹 Case 2: k = 2 (1 is LAST)

```text
coins = 1 * 1 * 1 = 1
```

Subproblems:

```text
left  = dfs(1,1) = 3
right = dfs(3,3) = 5
```

Total:

```text
1 + 3 + 5 = 9
```

---

### 🔹 Case 3: k = 3 (5 is LAST)

```text
coins = 1 * 5 * 1 = 5
```

Subproblems:

```text
left  = dfs(1,2) = 30
right = 0
```

Total:

```text
5 + 30 = 35
```

---

## Final Answer

```text
max(33, 9, 35) = 35
```

---

# Key Concepts

### 1. Reverse Thinking

```text
Think LAST, not FIRST
```

---

### 2. Stable Neighbors

```text
nums[i-1] and nums[j+1] are always valid
```

---

### 3. Interval DP

```text
Problem splits into left and right independent parts
```

---

# Complexity

* Time: $$O(n^3)$$
* Space: $$O(n^2)$$