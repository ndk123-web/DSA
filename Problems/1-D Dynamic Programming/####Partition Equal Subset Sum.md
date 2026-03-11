# Partition Equal Subset Sum

## Problem

Given an integer array `nums`, return **true** if the array can be partitioned into two subsets such that the **sum of elements in both subsets is equal**.

Example:

```
Input: nums = [1,2,3,4]
Output: true
Explanation:
subset1 = [1,4]
subset2 = [2,3]
```

---

# Key Observation

Let:

```
totalSum = sum(nums)
```

If we split the array into two equal subsets:

```
subset1 + subset2 = totalSum
subset1 = subset2
```

So:

```
2 * subset1 = totalSum
subset1 = totalSum / 2
```

Therefore the problem becomes:

> **Can we find a subset whose sum = totalSum / 2 ?**

If `totalSum` is odd, it is impossible.

---

# Approach 1 — Backtracking (Brute Force)

## Idea

At every element we have **two choices**:

```
1. Take the number
2. Skip the number
```

We explore all possible subsets and check if any subset reaches the target sum.

---

## Recursion State

```
index → which number we are considering
currentSum → current subset sum
```

Goal:

```
currentSum == target
```

---

## Example Dry Run

```
nums = [1,2,3,4]
target = 5
```

Start with index 0:

```
choose 1 → sum = 1
```

Next number:

```
choose 2 → sum = 3
```

Next number:

```
choose 3 → sum = 6 (too big)
skip 3
```

Next number:

```
choose 4 → 1 + 4 = 5
```

Target reached.

---

## Backtracking Code

```cpp
class Solution {
public:

    bool dfs(vector<int>& nums, int index, int currentSum, int target){

        if(currentSum == target)
            return true;

        if(index >= nums.size() || currentSum > target)
            return false;

        // take
        if(dfs(nums, index+1, currentSum + nums[index], target))
            return true;

        // skip
        return dfs(nums, index+1, currentSum, target);
    }

    bool canPartition(vector<int>& nums) {

        int totalSum = accumulate(nums.begin(), nums.end(), 0);

        if(totalSum % 2 != 0)
            return false;

        int target = totalSum / 2;

        return dfs(nums, 0, 0, target);
    }
};
```

---

## Complexity

```
Time Complexity  : O(2^n)
Space Complexity : O(n) recursion stack
```

Backtracking becomes very slow for large inputs.

---

# Approach 2 — Bottom-Up DP (0/1 Knapsack Pattern)

Instead of exploring all subsets, we track **which sums are achievable**.

---

## State Definition

```
dp[s] = true if we can build sum s using some elements
```

Range:

```
0 → target
```

---

## Base Case

```
dp[0] = true
```

Because we can always make sum `0` by choosing nothing.

---

## Transition

For each number `num`:

```
dp[j] = dp[j] OR dp[j - num]
```

Meaning:

```
If we could make sum (j - num),
then by adding num we can make j.
```

---

## Important Detail

We iterate **backwards**:

```
for j = target → num
```

This ensures each number is used **only once** (0/1 knapsack).

---

## Example Dry Run

```
nums = [1,2,3,4]
target = 5
```

Initial:

```
dp = [T F F F F F]
```

After `1`:

```
dp = [T T F F F F]
```

After `2`:

```
dp = [T T T T F F]
```

After `3`:

```
dp = [T T T T T T]
```

Now:

```
dp[5] = true
```

So partition exists.

---

## Bottom-Up Code

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {

        int totalSum = accumulate(nums.begin(), nums.end(), 0);

        if(totalSum % 2 != 0)
            return false;

        int target = totalSum / 2;

        vector<bool> dp(target + 1, false);

        dp[0] = true;

        for(int num : nums){

            for(int j = target; j >= num; j--){

                dp[j] = dp[j] || dp[j - num];

            }
        }

        return dp[target];
    }
};
```

---

# Complexity

```
Time Complexity  : O(n * target)
Space Complexity : O(target)
```

Where:

```
target = totalSum / 2
```

Good README already 👍. I’ll add the **third approach (Set / Reachable Sums method)** in the same LeetCode-style format so it fits naturally with the rest of your document.

You can append this section after the DP approach.

---

# Approach 3 — HashSet (Track Reachable Subset Sums)

## Idea

Instead of using a DP array, we maintain a **set of all possible subset sums** that can be formed so far.

At each number we **expand the reachable sums**.

Example:

If we currently can make sums:

```
{0,1,5}
```

and the next number is `3`, we generate new sums:

```
0+3 = 3
1+3 = 4
5+3 = 8
```

New reachable sums become:

```
{0,1,5,3,4,8}
```

If at any time the **target sum appears**, we can immediately return `true`.

---

# State Meaning

```
existing = set of reachable sums
```

Initially:

```
existing = {0}
```

Because we can always form sum `0` by selecting no elements.

---

# Transition

For each number `num`:

```
newSums = {}

for each sum s in existing:
    newSums.add(s + num)

existing = existing ∪ newSums
```

This simulates **choosing or skipping the number**.

---

# Example Dry Run

```
nums = [1,5,11,5]
target = 11
```

Start:

```
existing = {0}
```

---

After `1`:

```
new sums = {1}

existing = {0,1}
```

---

After `5`:

```
0+5 = 5
1+5 = 6
```

```
existing = {0,1,5,6}
```

---

After `11`:

```
0+11 = 11
1+11 = 12
5+11 = 16
6+11 = 17
```

```
existing = {0,1,5,6,11,12,16,17}
```

Now:

```
11 exists
```

So partition is possible.

Subset:

```
[11]
```

Other subset:

```
1 + 5 + 5 = 11
```

---

# HashSet Code

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {

        int total = accumulate(nums.begin(), nums.end(), 0);

        if(total % 2 != 0)
            return false;

        int target = total / 2;

        unordered_set<int> existing;
        existing.insert(0);

        for(int num : nums){

            unordered_set<int> newGen = existing;

            for(int s : existing){
                newGen.insert(s + num);
            }

            if(newGen.count(target))
                return true;

            existing.insert(newGen.begin(), newGen.end());
        }

        return false;
    }
};
```

---

# Complexity

```
Time Complexity  : O(n * target)
Space Complexity : O(target)
```

The set may grow up to the target sum range.

---

# Pattern Recognition

This problem is a classic **Subset Sum / 0-1 Knapsack** pattern.

Similar problems include:

```
Partition Equal Subset Sum
Target Sum
Last Stone Weight II
Subset Sum
0/1 Knapsack
```

They all revolve around the same idea:

```
Can we build a target sum using given numbers?
```

---

# Key Takeaways

• Convert equal partition into **subset sum**
• Check if `totalSum` is even
• Backtracking explores all subsets
• DP tracks **reachable sums efficiently**
• Reverse iteration ensures **each number used once**
