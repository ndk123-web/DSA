# 1137. N-th Tribonacci Number

The Tribonacci sequence is defined as:

```
T0 = 0
T1 = 1
T2 = 1
Tn = Tn-1 + Tn-2 + Tn-3
```

This is a classic 1D Dynamic Programming problem.

---

# Solution 1: Bottom-Up DP (Tabulation)

## Intuition

Each state depends on the previous three states:

```
dp[i] = dp[i-1] + dp[i-2] + dp[i-3]
```

So we compute from small values upward until we reach `n`.

---

## Approach

1. Handle base cases:
   - If `n == 0`, return 0
   - If `n == 1 or 2`, return 1

2. Create a DP array of size `n+1`
3. Initialize:
   - `dp[0] = 0`
   - `dp[1] = 1`
   - `dp[2] = 1`

4. Fill from `i = 3` to `n`
5. Return `dp[n]`

---

## Complexity

- Time Complexity: **O(n)**
- Space Complexity: **O(n)**

---

## Code (Bottom-Up)

```cpp
class Solution {
public:
    int tribonacci(int n) {
        if (n == 0)
            return 0;
        if (n == 1 || n == 2)
            return 1;

        vector<int> dp(n + 1);

        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;

        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
        }

        return dp[n];
    }
};
```

---

# Solution 2: Top-Down DP (Memoization)

## Intuition

Instead of building from bottom, we define the recurrence recursively.

To compute `Tn`, we compute:

```
Tn = Tn-1 + Tn-2 + Tn-3
```

But without memoization, this becomes exponential.

So we store previously computed results in a map.

---

## Approach

1. Define recursive function `tribo(n)`
2. Base cases:
   - `n == 0 → 0`
   - `n == 1 or 2 → 1`

3. If `n` already computed → return from memo
4. Otherwise compute recursively and store result
5. Return memoized value

---

## Complexity

- Time Complexity: **O(n)**
  Each state computed once.
- Space Complexity: **O(n)**
  For recursion stack + memo storage.

---

## Code (Top-Down)

```cpp
class Solution {
private:
    unordered_map<int, int> memo;

    int tribo(int n) {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;

        if (memo.find(n) != memo.end())
            return memo[n];

        return memo[n] = tribo(n - 1) + tribo(n - 2) + tribo(n - 3);
    }

public:
    int tribonacci(int n) {
        return tribo(n);
    }
};
```

---

# Key Insight

This is pure 1D DP.

Difference from Fibonacci:

- Fibonacci depends on 2 previous states.
- Tribonacci depends on 3 previous states.

Pattern recognition:

If recurrence depends on `k` previous states,
you can always:

- Solve using Top-Down DP
- Solve using Bottom-Up DP
- Optimize space to O(1) using `k` variables
