# Intuition

Although the problem describes smashing stones, the real transformation is:

```text
Each stone can be assigned either + or -
```

So the final result becomes:

```text
|sum(group1) - sum(group2)|
```

This reduces to:

```text
Split stones into two subsets such that the difference of their sums is minimized.
```

---

# Approach 1: Top-Down (Recursion + Memoization)

## Idea

We try all possibilities:

* Either include current stone in **group1**
* Or exclude it (implicitly goes to group2)

Let:

```text
dfs(i, total) = minimum difference we can get
```

Where:

* `i` → current index
* `total` → sum of group1 so far

---

## Base Case

```text
When all stones are processed:
    difference = |total - (sum - total)|
```

---

## Transition

```text
Take current stone:
    dfs(i+1, total + stones[i])

Skip current stone:
    dfs(i+1, total)
```

Take minimum of both.

---

## Optimization (Important)

We stop early when:

```text
total >= sum/2
```

Because beyond this, symmetry starts repeating.

---

## Code

```cpp
class Solution {
private:
    map<pair<int,int>, int> dp;
    int sum, target;

    int dfs(vector<int>& stones, int i, int total) {

        if (i == stones.size() || total >= target) {
            return abs(total - (sum - total));
        }

        if (dp.find({i, total}) != dp.end()) {
            return dp[{i, total}];
        }

        return dp[{i, total}] = min(
            dfs(stones, i+1, total),
            dfs(stones, i+1, total + stones[i])
        );
    }

public:
    int lastStoneWeightII(vector<int>& stones) {

        sum = accumulate(stones.begin(), stones.end(), 0);
        target = sum / 2;

        return dfs(stones, 0, 0);
    }
};
```

---

## Complexity

* **Time Complexity:**

```text
O(n × sum)
```

* **Space Complexity:**

```text
O(n × sum)
```

---

# Approach 2: Bottom-Up (Subset Sum / 1D DP)

## Idea

Instead of trying all partitions, we build **possible sums**.

Let:

```text
dp[j] = can we form sum j using some subset?
```

---

## Goal

We want:

```text
j ≈ sum / 2
```

Because:

```text
difference = |sum - 2*j|
```

---

## Initialization

```text
dp[0] = true
```

---

## Transition

For each stone:

```text
for j = target → stone:
    dp[j] = dp[j] OR dp[j - stone]
```

---

## Why reverse loop?

```text
Ensures each stone is used only once (0/1 knapsack)
```

---

## Answer Extraction

Find largest `j` such that:

```text
dp[j] == true
```

Then:

```text
answer = sum - 2*j
```

---

## Code

```cpp
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {

        int sum = accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2;

        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int stone : stones) {
            for (int j = target; j >= stone; j--) {
                dp[j] = dp[j] || dp[j - stone];
            }
        }

        for (int j = target; j >= 0; j--) {
            if (dp[j]) {
                return sum - 2*j;
            }
        }

        return 0;
    }
};
```

---

## Complexity

* **Time Complexity:**

```text
O(n × sum)
```

* **Space Complexity:**

```text
O(sum)
```

---

# Key Concepts

### State Meaning

```text
Top-down: dp[i][total] → best answer from index i with sum total
Bottom-up: dp[j] → can we form sum j?
```

---

### Core Logic

* Partition into two groups
* Minimize difference
* Convert into subset sum

---

# Summary

```text
Smashing → Assign +/-
Assign +/- → Partition into 2 groups
Partition → Subset Sum (Knapsack)
```