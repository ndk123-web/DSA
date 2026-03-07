# Coin Change

Given an integer array `coins` representing different coin denominations and an integer `amount`, return the **minimum number of coins** needed to make that amount.

If it is impossible to make the amount using the given coins, return `-1`.

Example:

```
coins = [1,2,5]
amount = 11
```

Possible combinations:

```
5 + 5 + 1 = 11  → 3 coins
```

Output:

```
3
```

---

# Intuition

At any point, if we want to build an amount `X`, we can pick any coin and reduce the problem into a smaller amount.

For example:

```
X → X - coin
```

So the main question becomes:

> If I take a coin now, what is the minimum number of coins required to build the **remaining amount**?

This leads to the recurrence:

```
minCoins(amount) = min(1 + minCoins(amount - coin))
```

The `+1` represents the coin we just used.

This structure naturally leads to **Dynamic Programming**, because the same sub-amounts appear repeatedly.

---

# Approach 1 — Top Down DP (Memoization)

### Idea

We recursively explore all possibilities of subtracting coins from the current amount.

Define:

```
dfs(amount) = minimum number of coins required to build this amount
```

Base cases:

```
amount == 0 → 0 coins needed
amount < 0  → impossible
```

To avoid recomputing the same states again and again, we store computed results in a **memo map**.

So whenever we encounter the same `amount` again, we directly return the stored answer.

This turns an exponential recursion into a linear number of states.

---

### Complexity

Time Complexity

```
O(amount × number_of_coins)
```

Each amount is computed once.

Space Complexity

```
O(amount)
```

Used for memoization and recursion stack.

---

### Code (Top Down)

```cpp
class Solution {
private:
    // it will store the min amount to make amount
    unordered_map<int, int> memo;

    int dfs(vector<int>& coins, int amount) {

        // it means we found that to make amount X we need 1 (afterward when
        // returns we automatically add 1 to it)
        if (amount == 0) {
            return 0;
        }

        // it means its not possible to get amount with this amount
        if (amount < 0) {
            return INT_MAX;
        }

        // if to generate amount the minimum coins we need is already computed
        // in memo if it presents then return it
        if (memo.count(amount)) {
            return memo[amount];
        }

        // for this amount initialize the minimum coins required is INT_MAX
        int ans = INT_MAX;
        for (int& coin : coins) {

            // now res either INT_MAX / number
            int res = dfs(coins, amount - coin);

            // if its not INT_MAX then its not negative number
            if (res != INT_MAX) {
                ans = min(ans, res + 1);
            }
        }

        // store the minimum coins to genearte amount
        return memo[amount] = ans;
    }

public:
    int coinChange(vector<int>& coins, int amount) {
        int res = dfs(coins, amount);

        // still there is possibility that it returns INT_MAX that we not found
        // any coins that sums to amount
        return res == INT_MAX ? -1 : res;
    }
};
```

---

# Approach 2 — Bottom Up DP (Tabulation)

### Idea

Instead of recursion, we solve the problem **iteratively from smaller amounts to larger amounts**.

Define:

```
dp[i] = minimum number of coins needed to make amount i
```

Base case:

```
dp[0] = 0
```

For each amount `i`, we try every coin:

```
dp[i] = min(dp[i], 1 + dp[i - coin])
```

if `i - coin ≥ 0`.

This means:

> If I use this coin, the remaining amount becomes `i - coin`, whose answer we already know.

---

### Complexity

Time Complexity

```
O(amount × number_of_coins)
```

Space Complexity

```
O(amount)
```

---

### Code (Bottom Up)

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1, INT_MAX);

        // we know that to build amount 0 we need 0 coins
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {

            for (int coin : coins) {
                
                // if amount i - coin >= 0 as well as inside dp[i-coin] is MAX means we cant build amount (we are going sequentially)
                if (i - coin >= 0 && dp[i - coin] != INT_MAX) {

                    // either dp[i] or 1 + previous coin 
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }

        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};
```

---

# Key Insight

Both approaches solve the same recurrence:

```
minCoins(x) = min(1 + minCoins(x - coin))
```

The difference is **how the subproblems are solved**.

Top Down:

```
Start with the large problem → break into smaller ones using recursion
```

Bottom Up:

```
Start from amount 0 → build solutions step by step until the target amount
```

Both methods ensure that each amount is computed only once.