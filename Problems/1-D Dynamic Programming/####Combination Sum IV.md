# Combination Sum IV

## Problem

Given an array of **distinct integers** `nums` and an integer `target`, return the **number of possible combinations** that add up to `target`.

The order of numbers **matters**.

Example:

```
Input: nums = [1,2,3], target = 4
Output: 7
```

Explanation:

```
1 + 1 + 1 + 1
1 + 1 + 2
1 + 2 + 1
2 + 1 + 1
2 + 2
1 + 3
3 + 1
```

Total ways = **7**

---

# Key Insight

At any step we choose a number `num` from `nums`.

If the last number chosen is `num`, then the remaining sum must be:

```
target - num
```

So the recurrence becomes:

```
ways(x) = ways(x - num1) + ways(x - num2) + ...
```

for all `num ≤ x`.

---

# Approach 1 — Brute Force (DFS)

## Idea

At every step we try **all numbers** in `nums`.

Each choice reduces the remaining sum.

Recursively explore all possibilities until:

```
remaining == 0 → valid combination
remaining < 0 → invalid
```

---

## Recursion State

```
remainingSum
```

Goal:

```
remainingSum == 0
```

---

## Example Dry Run

```
nums = [1,2,3]
target = 4
```

Tree exploration:

```
4
├── 3
│   ├── 2
│   │   ├── 1
│   │   │   └── 0 ✔
│   │   └── 0 ✔
│   └── 1
│       └── 0 ✔
├── 2
│   ├── 1
│   │   └── 0 ✔
│   └── 0 ✔
└── 1
    └── 0 ✔
```

Total valid paths = **7**

---

## Brute Force Code

```cpp
class Solution {
public:
    int dfs(vector<int>& nums, int remaining){

        if(remaining == 0)
            return 1;

        if(remaining < 0)
            return 0;

        int ways = 0;

        for(int num : nums){
            ways += dfs(nums, remaining - num);
        }

        return ways;
    }

    int combinationSum4(vector<int>& nums, int target) {
        return dfs(nums, target);
    }
};
```

---

## Complexity

```
Time  : O(n^target)
Space : O(target)
```

Very slow due to repeated subproblems.

---

# Approach 2 — Top Down DP (Memoization)

## Idea

The brute force recomputes the same states many times.

Example:

```
ways(3) gets computed multiple times
ways(2) gets computed multiple times
```

We store previously computed results in a **memo table**.

---

## State Definition

```
memo[x] = number of ways to build sum x
```

---

## Transition

```
ways(x) = Σ ways(x - num)
```

---

## Top-Down Code

```cpp
class Solution {
private:
    unordered_map<int,int> memo;

    int dfs(vector<int>& nums, int remaining){

        if(remaining == 0)
            return 1;

        if(remaining < 0)
            return 0;

        if(memo.count(remaining))
            return memo[remaining];

        int ways = 0;

        for(int num : nums){
            ways += dfs(nums, remaining - num);
        }

        memo[remaining] = ways;
        return ways;
    }

public:
    int combinationSum4(vector<int>& nums, int target) {
        return dfs(nums, target);
    }
};
```

---

## Complexity

```
Time  : O(target * nums.size())
Space : O(target)
```

Much faster because each state is computed once.

---

# Approach 3 — Bottom Up DP

Instead of recursion, we build answers from **smaller sums to larger sums**.

---

## State Definition

```
dp[i] = number of ways to build sum i
```

Base case:

```
dp[0] = 1
```

Because there is **one way to build sum 0**:

```
choose nothing
```

---

## Transition

For each sum `i`:

```
dp[i] += dp[i - num]
```

for every `num` where `i - num ≥ 0`.

Meaning:

```
If the last number is num,
the remaining sum must be i - num.
```

---

## Example Dry Run

```
nums = [1,2,3]
target = 4
```

Initial:

```
dp = [1,0,0,0,0]
```

### i = 1

```
1 → dp[1] += dp[0]
```

```
dp = [1,1,0,0,0]
```

---

### i = 2

```
1 → dp[2] += dp[1]
2 → dp[2] += dp[0]
```

```
dp = [1,1,2,0,0]
```

---

### i = 3

```
1 → dp[3] += dp[2]
2 → dp[3] += dp[1]
3 → dp[3] += dp[0]
```

```
dp = [1,1,2,4,0]
```

---

### i = 4

```
1 → dp[4] += dp[3]
2 → dp[4] += dp[2]
3 → dp[4] += dp[1]
```

```
dp = [1,1,2,4,7]
```

Answer:

```
dp[4] = 7
```

---

## Bottom Up Code

```cpp
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {

        vector<long long> dp(target + 1, 0);

        dp[0] = 1;

        for(int i = 1; i <= target; i++){

            for(int num : nums){

                if(i - num >= 0){
                    dp[i] += dp[i - num];
                }

            }
        }

        return dp[target];
    }
};
```

---

# Complexity

```
Time  : O(target * nums.size())
Space : O(target)
```

---

# Important Pattern

This problem belongs to the **Counting DP** pattern.

Similar problems:

```
Combination Sum IV
Climbing Stairs
Coin Change (count ways)
Decode Ways
```

Common recurrence:

```
dp[x] = Σ dp[x - step]
```
