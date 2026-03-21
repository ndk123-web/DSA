# `Coin Change II — Detailed Explanation (Top-Down + Bottom-Up)

---

# 🧠 Intuition

This problem is about **counting combinations**, not maximizing profit.

We are given:

- Coins (unlimited usage allowed)
- A target `amount`

We need:

> Number of **distinct combinations** (order doesn’t matter)

---

### 🔥 Key Observations

- Same coin can be used multiple times → **Unbounded**
- Order does NOT matter → **avoid permutations**
- So we must control order using **index-based decisions**

---

# 🧩 Core Idea

At every step, for a coin at index `i`, we have 2 choices:

```text
1. TAKE → use the coin again
2. SKIP → move to next coin
```

---

# 🧠 State Definition

```text
dp[i][amount]
```

👉 Meaning:

> Number of ways to make `amount` using coins from index `i` onward

---

# 🚀 Approach 1: Top-Down (Recursion + Memoization)

---

## 🔹 Decision Tree

```cpp
dfs(i, amount)
```

### If amount == 0:

```text
return 1 (valid combination)
```

### If out of coins or negative:

```text
return 0
```

---

## 🔹 Transitions

### TAKE (reuse same coin)

```cpp
dfs(i, amount - coins[i])
```

👉 Stay on same index → reuse allowed

---

### SKIP (ignore coin)

```cpp
dfs(i + 1, amount)
```

👉 Move forward → avoid duplicates

---

## 🔹 Final formula

```cpp
dp[i][amount] = take + skip
```

---

## 💻 Code (Top-Down)

```cpp
class Solution {
private:
    map<pair<int, int>, int> memo;

    int dfs(vector<int>& coins, int amount, int i) {
        if (amount == 0) return 1;
        if (i >= coins.size() || amount < 0) return 0;

        if (memo.find({i, amount}) != memo.end()) {
            return memo[{i, amount}];
        }

        int take = 0;
        if (coins[i] <= amount) {
            take = dfs(coins, amount - coins[i], i);
        }

        int skip = dfs(coins, amount, i + 1);

        return memo[{i, amount}] = take + skip;
    }

public:
    int change(int amount, vector<int>& coins) {
        return dfs(coins, amount, 0);
    }
};
```

---

# 🧠 Why Memoization?

Without memo:

- Same `(i, amount)` computed multiple times
- Time = exponential ❌

With memo:

- Each state computed once
- Time = O(n × amount) ✅

---

# 🚀 Approach 2: Bottom-Up (Tabulation)

---

## 🔹 DP Table

```text
dp[i][a] = ways to make amount `a` using coins from index `i`
```

---

## 🔹 Base Case

```cpp
dp[i][0] = 1
```

👉 Why?

> Amount 0 can be formed in **1 way (choose nothing)**

---

## 🔹 Transition

```cpp
dp[i][a] = dp[i+1][a] + dp[i][a - coins[i]]
```

---

### Explanation:

| Part               | Meaning           |
| ------------------ | ----------------- |
| dp[i+1][a]         | skip current coin |
| dp[i]a - coins[i]] | take current coin |

---

## 🔹 Code (Bottom-Up)

```cpp
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<uint>> dp(n + 1, vector<uint>(amount + 1, 0));

        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int a = 0; a <= amount; a++) {
                if (a >= coins[i]) {
                    dp[i][a] = dp[i + 1][a];             // skip
                    dp[i][a] += dp[i][a - coins[i]];     // take
                }
            }
        }

        return dp[0][amount];
    }
};
```

---

# 🔍 Dry Run

### Input:

```text
coins = [1,2,3]
amount = 4
```

---

## 🧾 Table Build

```text
i ↓ / a →   0  1  2  3  4
--------------------------------
3 (no coin) 1  0  0  0  0
2 (3)       1  0  0  1  0
1 (2)       1  0  1  1  1
0 (1)       1  1  2  3  4
```

---

## 🔥 Final Answer

```text
dp[0][4] = 4
```

---

## ✅ All combinations

```text
1+1+1+1
1+1+2
1+3
2+2
```

---

# 🧠 Deep Logic Breakdown

---

## ❓ Why `dp[i][0] = 1`?

> There is exactly 1 way to make amount 0 → choose nothing

---

## ❓ Why same row in TAKE?

```cpp
dp[i][a - coins[i]]
```

👉 because:

- we can reuse the same coin

---

## ❓ Why next row in SKIP?

```cpp
dp[i+1][a]
```

👉 because:

- we ignore current coin

---

## ❓ Why ADD (not max)?

Because:

> We are counting **number of ways**, not optimizing

---

# ⚙️ Complexity

### Time Complexity:

```text
O(n × amount)
```

---

### Space Complexity:

```text
O(n × amount)
```

---

# 🔥 Final Takeaway

> This is a **classic Unbounded Knapsack (Combination Count)** problem

---

# 💬 GOLD SUMMARY

```text
State     → dp[i][amount]
Decision  → take / skip
Transition→ dp[i][a] = dp[i+1][a] + dp[i][a - coin]
```

---

# 🚀 Master Insight

> TAKE = stay (reuse coin)
> SKIP = move (avoid duplicates)
> RESULT = sum (count all ways)
