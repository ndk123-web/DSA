# Intuition

In the classic **House Robber** problem, houses are arranged in a straight line and the recurrence is:

```id="mjlwmn"
dp[i] = max(dp[i-1], nums[i] + dp[i-2])
```

But in **House Robber II**, houses are arranged in a **circle**, meaning:

- The **first and last houses are adjacent**
- So they **cannot both be robbed**

To handle this, we split the problem into two linear cases:

1. Rob houses from **0 → n-2** (exclude the last house)
2. Rob houses from **1 → n-1** (exclude the first house)

The final answer is the maximum of these two cases.

---

# Approach 1: Top-Down DP (Memoization)

## Idea

Define a recursive function:

```id="px3z9s"
dfs(i) = maximum money we can rob starting from house i
```

At each house we have two choices:

- Skip the house → move to `i + 1`
- Rob the house → move to `i + 2`

Recurrence:

```id="ux06n4"
dfs(i) = max(
    dfs(i+1),
    nums[i] + dfs(i+2)
)
```

Memoization ensures each state is computed only once.

Since the problem is circular, we solve two ranges separately:

```id="f4nyjo"
case1 = dfs(0 → n-2)
case2 = dfs(1 → n-1)
```

Return the maximum.

---

## Complexity

Time Complexity:

```id="qj26yj"
O(n)
```

Each state is computed once.

Space Complexity:

```id="z4x8zn"
O(n)
```

For recursion stack and memo storage.

---

## Code (Top-Down)

```cpp id="1i6qxf"
class Solution {
private:
    vector<int> memo;

    int dfs(vector<int>& nums, int i, int n) {
        if (i > n)
            return 0;

        if (memo[i] != -1)
            return memo[i];

        memo[i] = max(
            dfs(nums, i + 1, n),
            nums[i] + dfs(nums, i + 2, n)
        );

        return memo[i];
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);

        memo.assign(n, -1);
        int case1 = dfs(nums, 0, n - 2);

        memo.assign(n, -1);
        int case2 = dfs(nums, 1, n - 1);

        return max(case1, case2);
    }
};
```

---

# Approach 2: Bottom-Up DP (Tabulation)

## Idea

We use the standard **House Robber recurrence**:

```id="fhtyap"
dp[i] = max(dp[i-1], nums[i] + dp[i-2])
```

But because of the circular constraint, we again solve two linear ranges:

1. **0 → n-2**
2. **1 → n-1**

Then return the maximum result.

---

## State Definition

```id="2ybz8s"
dp[i] = maximum money that can be robbed from index 0 to i
```

---

## Complexity

Time Complexity:

```id="j8vv0v"
O(n)
```

Space Complexity:

```id="2e4lnd"
O(n)
```

---

## Code (Bottom-Up)

```cpp id="5ip8yx"
class Solution {
public:
    int robLinear(vector<int>& nums, int start, int end) {
        int n = end - start + 1;
        vector<int> dp(n);

        dp[0] = nums[start];
        dp[1] = max(nums[start], nums[start + 1]);

        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 1], nums[start + i] + dp[i - 2]);
        }

        return dp[n - 1];
    }

    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1)
            return nums[0];

        return max(
            robLinear(nums, 0, n - 2),
            robLinear(nums, 1, n - 1)
        );
    }
};
```

---

# Key Insight

The only complication in **House Robber II** is the circular arrangement.

By splitting the problem into two independent linear robberies, we eliminate the adjacency conflict between the first and last houses and reuse the standard **House Robber dynamic programming strategy**.
