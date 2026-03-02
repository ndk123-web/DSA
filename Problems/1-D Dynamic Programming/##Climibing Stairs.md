# ✅ Solution 1: Pure Recursion (Brute Force)

## Intuition

Har step par tum 1 ya 2 step le sakte ho.
To reach step `n`, tum ya toh `n-1` se aaye hoge ya `n-2` se.

Isliye recurrence ban gaya:

```
f(n) = f(n-1) + f(n-2)
```

Ye Fibonacci jaisa lagta hai — aur hai bhi.

Lekin yaha problem hai:
Same subproblems baar baar calculate ho rahe hain.

---

## Approach

- Base cases:
  - `f(0) = 1`
  - `f(1) = 1`

- Recursively call:
  - `f(n) = f(n-1) + f(n-2)`

---

## Complexity

- Time complexity: **O(2^n)**
  (Exponential, because of repeated subproblems)

- Space complexity: **O(n)**
  (Recursion stack)

---

## Code

```python
class Solution:
    def climbStairs(self, n: int) -> int:
        def stair(n):
            if n == 0 or n == 1:
                return 1
            return stair(n-1) + stair(n-2)

        return stair(n)
```

---

# ✅ Solution 2: Top-Down DP (Memoization)

## Intuition

Same recursion logic use karenge.
But ek baar koi value calculate ho gayi, dobara calculate nahi karenge.

Overlapping subproblems ko store karenge.

---

## Approach

- Use dictionary `memo`
- Base:
  - `memo = {0:1, 1:1}`

- If value already computed → return from memo
- Otherwise compute and store

---

## Complexity

- Time complexity: **O(n)**
  (Each state computed once)

- Space complexity: **O(n)**
  (Memo + recursion stack)

---

## Code

```python
class Solution:
    def climbStairs(self, n: int) -> int:
        memo = {0: 1, 1: 1}

        def stair(n):
            if n in memo:
                return memo[n]
            memo[n] = stair(n-1) + stair(n-2)
            return memo[n]

        return stair(n)
```

---

# ✅ Solution 3: Bottom-Up DP (Tabulation)

## Intuition

Recursion hata do.
Hum jaante hain:

```
dp[i] = dp[i-1] + dp[i-2]
```

Toh left se right build karenge.

---

## Approach

- Create dp array of size n+1
- Base:
  - `dp[0] = 1`
  - `dp[1] = 1`

- Loop from 2 to n
- Fill dp

---

## Complexity

- Time complexity: **O(n)**
- Space complexity: **O(n)**

---

## Code

```python
class Solution:
    def climbStairs(self, n: int) -> int:
        if n == 0:
            return 1

        dp = [0] * (n + 1)
        dp[0] = 1
        dp[1] = 1

        for i in range(2, n + 1):
            dp[i] = dp[i-1] + dp[i-2]

        return dp[n]
```

---

# ✅ Solution 4: Space Optimized DP

## Intuition

Notice karo:
Har step par sirf last 2 values chahiye.

Toh pura array rakhne ki zarurat nahi.

---

## Approach

Maintain two variables:

- prev2 (dp[i-2])
- prev1 (dp[i-1])

Update iteratively.

---

## Complexity

- Time complexity: **O(n)**
- Space complexity: **O(1)**

---

## Code

```python
class Solution:
    def climbStairs(self, n: int) -> int:
        if n == 0:
            return 1

        prev2 = 1
        prev1 = 1

        for _ in range(2, n + 1):
            curr = prev1 + prev2
            prev2 = prev1
            prev1 = curr

        return prev1
```

---

# Final Understanding

Climbing Stairs =
Counting paths in a 1D linear graph.

DP Type Used:

- Solution 1 → No DP
- Solution 2 → Top-Down DP
- Solution 3 → Bottom-Up DP
- Solution 4 → State Compression DP
