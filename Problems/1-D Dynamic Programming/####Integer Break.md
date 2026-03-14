# Approach 1 — Brute Force (Recursion)

## Intuition

The problem asks us to split an integer `n` into at least two positive integers such that their **product is maximized**.

If we split `n` into two parts:

```
n = i + (n - i)
```

we have two possibilities for each part:

1. Keep the number as it is.
2. Break it further into smaller parts.

So for every split we compare the product of the two parts and keep the maximum.

---

## Approach

We recursively try all possible splits of `n`:

```
n = i + (n-i)
```

For each split we calculate:

```
max(i, dfs(i)) * max(n-i, dfs(n-i))
```

This allows both numbers to either stay whole or be further broken.

---

## Complexity

- **Time complexity:**
  $$O(2^n)$$ (exponential because the recursion explores many repeated states)

- **Space complexity:**
  $$O(n)$$ recursion stack

---

## Code

```cpp
class Solution {
private:
    int dfs(int n) {
        if (n == 1) return 1;

        int res = 0;

        for (int i = 1; i < n; i++) {
            int left = max(i, dfs(i));
            int right = max(n - i, dfs(n - i));
            res = max(res, left * right);
        }

        return res;
    }

public:
    int integerBreak(int n) {
        return dfs(n);
    }
};
```

---

# Approach 2 — Top Down DP (Memoization)

## Intuition

The brute force solution recomputes the same subproblems multiple times.

For example:

```
dfs(5)
dfs(6)
dfs(7)
```

may appear repeatedly in different recursion branches.

To avoid redundant computation, we store the results in a **memo table**.

---

## Approach

We store previously computed results:

```
memo[n] = maximum product obtainable from n
```

Before computing `dfs(n)`, we check if the result already exists in the memo map.

The recurrence remains the same:

```
max(i, dfs(i)) * max(n-i, dfs(n-i))
```

---

## Complexity

- **Time complexity:**
  $$O(n^2)$$

- **Space complexity:**
  $$O(n)$$ for recursion + memo

---

## Code

```cpp
class Solution {
private:
    unordered_map<int,int> memo;

    int dfs(int n) {
        if (n == 1) return 1;

        if (memo.count(n))
            return memo[n];

        int res = 0;

        for (int i = 1; i < n; i++) {
            int left = max(i, dfs(i));
            int right = max(n - i, dfs(n - i));
            res = max(res, left * right);
        }

        return memo[n] = res;
    }

public:
    int integerBreak(int n) {
        return dfs(n);
    }
};
```

---

# Approach 3 — Bottom Up DP

## Intuition

Instead of solving the problem recursively, we can build answers from **smaller numbers to larger numbers**.

Define:

```
dp[i] = maximum product obtainable from integer i
```

For every number `i`, we try all possible splits:

```
i = j + (i - j)
```

Each part can either stay whole or be broken further.

So the transition becomes:

```
dp[i] = max(dp[i], max(j, dp[j]) * max(i-j, dp[i-j]))
```

---

## Approach

1. Create a DP array of size `n + 1`.
2. Iterate from `2` to `n`.
3. For each number, try all splits `1..i-1`.
4. Update the maximum product.

---

## Complexity

- **Time complexity:**
  $$O(n^2)$$

- **Space complexity:**
  $$O(n)$$

---

## Code

```cpp
class Solution {
public:
    int integerBreak(int n) {

        vector<int> dp(n + 1, 0);

        for (int i = 2; i <= n; i++) {

            for (int j = 1; j < i; j++) {

                int left = max(j, dp[j]);
                int right = max(i - j, dp[i - j]);

                dp[i] = max(dp[i], left * right);
            }
        }

        return dp[n];
    }
};
```
