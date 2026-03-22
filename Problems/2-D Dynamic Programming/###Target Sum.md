# Target Sum

## Intuition

This problem asks us to assign either a `+` or `-` sign to each element in the array such that the final sum equals the given target.

At each index, we have exactly two choices:

* Add the current number
* Subtract the current number

This naturally leads to a decision tree where each level corresponds to an index, and each branch corresponds to choosing `+` or `-`.

Instead of explicitly generating all combinations, we can observe that many states repeat. A state is uniquely defined by:

* Current index
* Current accumulated sum

This allows us to apply Dynamic Programming to avoid recomputation.

---

## Approach

### Top-Down (Recursion + Memoization)

We define a recursive function:

```text
dfs(i, currentSum)
```

This represents the number of ways to reach the final target using elements from index `i` onward, given the current accumulated sum.

### Base Cases:

* If `i == n` and `currentSum == target`, return 1 (valid way)
* If `i == n` and `currentSum != target`, return 0

### Transitions:

At each index:

* Add current number → `dfs(i+1, currentSum + nums[i])`
* Subtract current number → `dfs(i+1, currentSum - nums[i])`

The result is the sum of both choices.

Memoization is used to store results for `(i, currentSum)` to avoid recomputation.

---

### Bottom-Up (Tabulation)

Instead of recursion, we build a DP table iteratively.

We define:

```text
dp[i][sum]
```

Meaning:
Number of ways to reach a sum `sum` using the first `i` elements.

Since sums can be negative, we use an offset:

```text
offset = total sum of all elements
```

This allows us to map:

* range `[-sum, +sum]` → `[0, 2*sum]`

### Initialization:

```text
dp[0][offset] = 1
```

This represents that using 0 elements, we can form sum = 0 in one way.

---

### Transition:

For each number:

```text
dp[i+1][s + nums[i]] += dp[i][s]
dp[i+1][s - nums[i]] += dp[i][s]
```

We iterate through all possible sums and update the next row accordingly.

---

### Final Answer:

```text
dp[n][target + offset]
```

---

## Complexity

### Time Complexity:

```text
O(n * totalSum)
```

### Space Complexity:

```text
O(n * totalSum)
```

---

## Code

### Top-Down (Memoization)

```cpp
class Solution {
private:
    map<pair<int,int>, int> memo;
    int gtarget;

    int dfs(vector<int>& nums, int currentSum, int i) {
        if (i >= nums.size()) {
            return currentSum == gtarget ? 1 : 0;
        }

        if (memo.find({i, currentSum}) != memo.end()) {
            return memo[{i, currentSum}];
        }

        int add = dfs(nums, currentSum + nums[i], i + 1);
        int sub = dfs(nums, currentSum - nums[i], i + 1);

        return memo[{i, currentSum}] = add + sub;
    }

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        gtarget = target;
        return dfs(nums, 0, 0);
    }
};
```

---

### Bottom-Up (Tabulation)

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int x : nums) sum += x;

        if (abs(target) > sum) return 0;

        int offset = sum;
        vector<vector<int>> dp(nums.size() + 1, vector<int>(2 * sum + 1, 0));

        dp[0][offset] = 1;

        for (int i = 0; i < nums.size(); i++) {
            for (int s = 0; s <= 2 * sum; s++) {
                if (dp[i][s] != 0) {
                    dp[i+1][s + nums[i]] += dp[i][s];
                    dp[i+1][s - nums[i]] += dp[i][s];
                }
            }
        }

        return dp[nums.size()][target + offset];
    }
};
```

---

## Key Insight

* This is not a standard knapsack problem.
* It is a state transition problem where each step branches into two possibilities.
* The DP table captures how many ways each intermediate sum can be formed.

The main difficulty lies in handling negative sums, which is solved using the offset technique.
