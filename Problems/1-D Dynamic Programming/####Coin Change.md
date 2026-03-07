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
    unordered_map<int,int> memo;

    int dfs(vector<int>& coins, int amount){

        if(amount == 0)
            return 0;

        if(amount < 0)
            return INT_MAX;

        if(memo.count(amount))
            return memo[amount];

        int ans = INT_MAX;

        for(int &coin : coins){

            int res = dfs(coins, amount - coin);

            if(res != INT_MAX)
                ans = min(ans, res + 1);
        }

        return memo[amount] = ans;
    }

public:
    int coinChange(vector<int>& coins, int amount){

        int res = dfs(coins, amount);

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

        vector<int> dp(amount + 1, INT_MAX);

        dp[0] = 0;

        for(int i = 1; i <= amount; i++){

            for(int coin : coins){

                if(i - coin >= 0 && dp[i - coin] != INT_MAX){
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
