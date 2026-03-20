# 🧠 Intuition

This problem is not about comparing prices or finding local differences.
The core idea is to model the problem as a **decision-making process over time with constraints**.

At any day `i`, we can only be in one of two meaningful states:

- **canBuy = 1** → we don’t have stock, so we can buy
- **canBuy = 0** → we already have stock, so we can sell

From each state, we have choices:

### If we can BUY:

- Buy the stock → spend money → `-prices[i]`
- Skip → do nothing

### If we can SELL:

- Sell the stock → gain money → `+prices[i]`
  → but next day is **cooldown**, so move to `i + 2`
- Hold → do nothing

👉 The key idea:
We don’t track stock price differences manually.
We **accumulate profit through decisions** using `+` and `-`.

---

# 🚀 Approach

---

## 🔹 Top-Down (Recursion + Memoization)

### Idea:

We define a recursive function:

```
dfs(i, canBuy)
```

Meaning:

- At index `i`
- Whether we can buy or not

We explore all valid decisions and take the maximum profit.

---

### Transitions:

#### If `canBuy == true`:

```
Buy  → -prices[i] + dfs(i+1, false)
Skip → dfs(i+1, true)
```

#### If `canBuy == false`:

```
Sell → +prices[i] + dfs(i+2, true)   // cooldown
Hold → dfs(i+1, false)
```

---

### Why Memoization?

The same state `(i, canBuy)` can be reached from multiple paths.

Example:

- From different sequences of buy/skip, we may reach the same `(i, canBuy)`
- Without memo → exponential calls
- With memo → each state computed once

---

### Top-Down Code

```cpp
class Solution {
private:
    vector<vector<int>> dp;

    int dfs(vector<int>& prices, int i, int canBuy) {
        if (i >= prices.size()) return 0;

        if (dp[i][canBuy] != -1) return dp[i][canBuy];

        if (canBuy) {
            return dp[i][canBuy] = max(
                -prices[i] + dfs(prices, i+1, 0),
                dfs(prices, i+1, 1)
            );
        } else {
            return dp[i][canBuy] = max(
                prices[i] + dfs(prices, i+2, 1),
                dfs(prices, i+1, 0)
            );
        }
    }

public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        dp.assign(n, vector<int>(2, -1));
        return dfs(prices, 0, 1);
    }
};
```

---

## 🔹 Bottom-Up (Tabulation)

### Idea:

Instead of solving recursively, we build answers from the end.

We define:

```
dp[i][canBuy]
```

Meaning:

- Maximum profit starting from day `i`
- Given current state

---

### Important Observation:

Each state depends on:

```
dp[i+1] and dp[i+2]
```

So we iterate **backwards**.

---

### Transitions:

#### canBuy = 1

```
dp[i][1] = max(
    -prices[i] + dp[i+1][0],
    dp[i+1][1]
)
```

#### canBuy = 0

```
dp[i][0] = max(
    prices[i] + dp[i+2][1],
    dp[i+1][0]
)
```

---

### Base Case:

```
dp[n][0] = dp[n][1] = 0
dp[n+1][0] = dp[n+1][1] = 0   // for cooldown access
```

---

### Bottom-Up Code

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        vector<vector<int>> dp(n + 2, vector<int>(2, 0));

        for (int i = n - 1; i >= 0; i--) {

            // canBuy = 1 → we can buy
            dp[i][1] = max(
                -prices[i] + dp[i + 1][0],  // buy
                dp[i + 1][1]                // skip
            );

            // canBuy = 0 → we have stock, can sell
            dp[i][0] = max(
                prices[i] + dp[i + 2][1],   // sell (cooldown)
                dp[i + 1][0]                // hold
            );
        }

        return dp[0][1];
    }
};
```

---

# ⚙️ Complexity

### Time Complexity:

```
O(n)
```

Each state `(i, canBuy)` is computed once.

---

### Space Complexity:

```
O(n)
```

DP table of size `n x 2`

---

# 🧠 Final Understanding (Important)

- This is not a greedy or subset problem
- This is a **state transition DP problem**
- We don’t compute profit directly → we **accumulate via decisions**
- Cooldown is handled by jumping `i + 2`
