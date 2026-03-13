# Approach 1 — Brute Force (DFS)

## Intuition

The goal is to represent `n` as a sum of **perfect squares** while minimizing the number of squares used.

One simple idea is to **try all possible perfect squares at every step**.
If we are currently at some sum `t`, we can try adding:

```
1²
2²
3²
...
```

and recursively check how many squares are needed to reach `n`.

This generates a recursion tree where each node represents the current sum and branches represent adding a square number.

However, this approach recomputes many states repeatedly.

---

## Approach

Define a recursive function:

```
dfs(current_sum)
```

At each step:

1. If `current_sum == n` → we reached the target, return `0`.
2. If `current_sum > n` → invalid path.
3. Try every perfect square `j*j` and recursively compute:

```
1 + dfs(current_sum + j*j)
```

Take the minimum among all possibilities.

---

## Complexity

- Time complexity:
  $$O(\text{exponential})$$

- Space complexity:
  $$O(n)$$ recursion stack depth.

---

## Code

```cpp
class Solution {
public:
    int dfs(int n, int current) {

        if (current == n) return 0;
        if (current > n) return INT_MAX;

        int ans = INT_MAX;

        for (int j = 1; j * j <= n; j++) {
            int sq = j * j;
            int res = dfs(n, current + sq);

            if (res != INT_MAX)
                ans = min(ans, res + 1);
        }

        return ans;
    }

    int numSquares(int n) {
        return dfs(n, 0);
    }
};
```

---

# Approach 2 — Top Down DP (Memoization)

## Intuition

The brute force solution repeatedly solves the same subproblems.

Example:

```
dfs(9)
dfs(10)
dfs(7)
```

These states can appear many times in different branches.

To avoid recomputation, we store the result for each state in a **memo table**.

---

## Approach

Define a memo table:

```
memo[t] = minimum squares required to reach n from sum t
```

When we compute a state `t`, we store the answer in `memo`.
If the same state appears again, we reuse the stored value instead of recomputing it.

Transition:

```
f(t) = min(1 + f(t + square))
```

Where `square = j*j`.

---

## Complexity

- Time complexity:
  $$O(n\sqrt{n})$$

- Space complexity:
  $$O(n)$$

---

## Code

```cpp
class Solution {
private:
    unordered_map<int,int> memo;

    int dfs(int n, int t){

        if(t == n) return 0;
        if(t > n) return INT_MAX;

        if(memo.count(t))
            return memo[t];

        int ans = INT_MAX;

        for(int j = 1; j * j <= n; j++){

            int sq = j * j;
            int res = dfs(n, t + sq);

            if(res != INT_MAX)
                ans = min(ans, res + 1);
        }

        return memo[t] = ans;
    }

public:
    int numSquares(int n) {
        return dfs(n,0);
    }
};
```

---

# Approach 3 — Bottom Up DP

## Intuition

Instead of solving the problem recursively, we can build the solution **from smaller numbers to larger numbers**.

Define:

```
dp[i] = minimum number of perfect squares needed to build i
```

Example:

```
dp[4] = 1 (4)
dp[8] = 2 (4 + 4)
dp[9] = 1 (9)
dp[13] = 2 (9 + 4)
```

For each number `i`, we try subtracting every perfect square ≤ `i`.

---

## Approach

For each number `i`:

1. Try all squares `j*j` such that `j*j ≤ i`.
2. Check the remaining value:

```
i - j*j
```

3. Update:

```
dp[i] = min(dp[i], 1 + dp[i - j*j])
```

This works because the optimal solution for `i` must use one square plus the optimal solution for the remaining value.

---

## Complexity

- Time complexity:
  $$O(n\sqrt{n})$$

- Space complexity:
  $$O(n)$$

---

## Code

```cpp
class Solution {
public:
    int numSquares(int n) {

        vector<int> dp(n + 1, INT_MAX);

        dp[0] = 0;

        for (int i = 1; i <= n; i++) {

            for (int j = 1; j * j <= i; j++) {

                int sq = j * j;
                dp[i] = min(dp[i], dp[i - sq] + 1);

            }
        }

        return dp[n];
    }
};
```
