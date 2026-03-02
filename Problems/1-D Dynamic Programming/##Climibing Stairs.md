# ✅ Solution 1: Normal Recursion (Brute Force)

## Intuition

To reach step `n`, you must have come from:

- Step `n-1` (taking 1 step)
- Step `n-2` (taking 2 steps)

So the recurrence is:

```
f(n) = f(n-1) + f(n-2)
```

This naturally forms a Fibonacci-like structure.

However, this approach recalculates the same subproblems multiple times.

---

## Approach

- Define base cases:
  - `f(1) = 1`
  - `f(2) = 2`

- Recursively compute:
  - `f(n) = f(n-1) + f(n-2)`

---

## Complexity

- Time Complexity: **O(2^n)** (exponential due to repeated calls)
- Space Complexity: **O(n)** (recursion stack)

---

## Code (C++)

```cpp
class Solution {
private:
    int solve(int n) {
        if (n == 1) return 1;
        if (n == 2) return 2;

        return solve(n - 1) + solve(n - 2);
    }

public:
    int climbStairs(int n) {
        return solve(n);
    }
};
```

---

# ✅ Solution 2: Top-Down DP (Memoization)

## Intuition

The recursive solution recalculates the same values again and again.

To optimize:

- Store already computed results.
- If the value exists, reuse it.

This avoids overlapping subproblems.

---

## Approach

- Use an `unordered_map<int, int>` to store computed values.
- Before computing `f(n)`, check if it already exists in `memo`.
- If yes → return it.
- Otherwise compute and store it.

---

## Complexity

- Time Complexity: **O(n)** (each state computed once)
- Space Complexity: **O(n)** (memo + recursion stack)

---

## Code (C++)

```cpp
#include <unordered_map>
using namespace std;

class Solution {
private:
    unordered_map<int, int> memo;

    int fibonacci(int n) {
        if (n <= 0) return 1;
        if (n == 1) return 1;
        if (n == 2) return 2;

        if (memo.find(n) != memo.end()) {
            return memo[n];
        }

        memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
        return memo[n];
    }

public:
    int climbStairs(int n) {
        return fibonacci(n);
    }
};
```

---

# ✅ Solution 3: Bottom-Up DP (Tabulation)

## Intuition

Instead of going deep into recursion and coming back up,
we build the solution from smaller values to larger values.

Since:

```
dp[i] = dp[i-1] + dp[i-2]
```

We compute from left to right.

---

## Approach

1. Create an array `dp` of size `n+1`.
2. Initialize:
   - `dp[0] = 1`
   - `dp[1] = 1`

3. Fill the table using the recurrence.
4. Return `dp[n]`.

---

## Complexity

- Time Complexity: **O(n)**
- Space Complexity: **O(n)**

---

## Code (C++)

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        if (n == 2)
            return 2;

        int dp[n + 1];

        for (int i = 0; i <= n; i++) {
            dp[i] = 0;
        }

        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};
```

---

# 🔥 What Type of DP Is Used?

- Normal recursion → Not DP
- Memoization → Top-Down DP
- Tabulation → Bottom-Up DP
