# House Robber

You are given an array `nums` where `nums[i]` is the money in house `i`.

You cannot rob two adjacent houses.

Return the maximum money you can rob.

---

# 🔵 Solution 1: Bottom-Up DP (Tabulation)

## Intuition

At every house `i`, you have two choices:

1. Skip the house → profit remains `dp[i-1]`
2. Rob the house → profit becomes `nums[i] + dp[i-2]`

So recurrence becomes:

```
dp[i] = max(dp[i-1], nums[i] + dp[i-2])
```

We build the solution from left to right.

---

## State Definition

```
dp[i] = maximum money that can be robbed from houses 0 to i
```

---

## Base Cases

- If `n == 1` → return `nums[0]`
- If `n == 2` → return `max(nums[0], nums[1])`

Initialization:

```
dp[0] = nums[0]
dp[1] = max(nums[0], nums[1])
```

---

## Algorithm

Loop from `i = 2` to `n-1`:

```
dp[i] = max(dp[i-1], nums[i] + dp[i-2])
```

Return `dp[n-1]`.

---

## Complexity

- Time Complexity: **O(n)**
- Space Complexity: **O(n)**

---

## Code (Bottom-Up)

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);

        vector<int> dp(n);

        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
        }

        return dp[n-1];
    }
};
```

---

# 🔴 Solution 2: Top-Down DP (Memoization)

## Intuition

Instead of building from start, we define the problem recursively.

From index `i`, we have two options:

1. Skip house `i` → move to `i+1`
2. Rob house `i` → move to `i+2`

So:

```
dfs(i) = max(
    dfs(i+1),
    nums[i] + dfs(i+2)
)
```

This explores all valid combinations, but memoization ensures each state is computed only once.

---

## State Definition

```
dfs(i) = maximum money that can be robbed starting from index i
```

---

## Base Case

If `i >= n`, return 0.

---

## Algorithm

1. If result already computed → return from memo.
2. Otherwise compute recursively.
3. Store result in memo.
4. Return memoized value.

---

## Complexity

- Time Complexity: **O(n)**
- Space Complexity: **O(n)**
  (memo array + recursion stack)

---

## Code (Top-Down)

```cpp
class Solution {
private:
    vector<int> memo;

    int dfs(vector<int>& nums, int i) {
        if (i >= nums.size())
            return 0;

        if (memo[i] != -1)
            return memo[i];

        memo[i] = max(
            dfs(nums, i + 1),
            nums[i] + dfs(nums, i + 2)
        );

        return memo[i];
    }

public:
    int rob(vector<int>& nums) {
        memo.assign(nums.size(), -1);
        return dfs(nums, 0);
    }
};
```

---

# Key Insight

Bottom-Up defines:

```
dp[i] = best from 0 to i
```

Top-Down defines:

```
dfs(i) = best from i to end
```

They are mathematically equivalent.

One builds forward.
One breaks the problem recursively.

Same recurrence.
Different traversal direction.

This is classic 1D DP with decision per index.

Once this structure becomes automatic, most linear DP problems follow the same pattern.
