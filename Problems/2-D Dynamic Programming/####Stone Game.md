# 1. Brute Force (Your Initial Idea)

## Intuition

The game involves two players making optimal choices. At every step, a player can choose either the leftmost or rightmost pile. So the natural thought is to simulate all possible choices and determine whether Alice can end up with more stones than Bob.

---

## Approach

Use recursion to simulate both players’ moves:

- Alice tries both options (left and right)
- Bob also tries both options
- Track scores of both players

At each step:

- If it's Alice’s turn → maximize outcome
- If it's Bob’s turn → minimize Alice’s winning chances

However:

- You used `erase()` which makes it inefficient
- You tracked `(x, y)` which is not a valid DP state

Correct state should be `(i, j)` representing remaining range.

---

## Complexity

- Time complexity:
  $$O(2^n)$$ (exponential due to all possibilities)

- Space complexity:
  $$O(n)$$ recursion stack

---

## Code (your idea, simplified conceptual version)

```cpp
class Solution {
private:

    map<pair<int,int>, bool> memo;

    bool dfs(vector<int>& piles, int x, int y, int i, int j, bool turn) {
        if (i == 0 && j == -1) {
            return (x > y) ? true: false;
        }

        if (memo.find({x,y}) != memo.end()) {
            return memo[{x,y}];
        }

        vector<int> tempPiles = piles;

        if (turn) {
            tempPiles.erase(tempPiles.begin() + i);
            bool takeFirst = dfs(tempPiles, x+piles[i], y, 0, tempPiles.size()-1, !turn);

            tempPiles = piles;
            tempPiles.erase(tempPiles.begin() + j);
            bool takeLast = dfs(tempPiles, x+piles[j], y, 0, tempPiles.size()-1, !turn);
            return memo[{x,y}] = takeFirst || takeLast;
        }

        else {
            tempPiles.erase(tempPiles.begin() + i);
            bool takeFirst = dfs(tempPiles, x, y + piles[i], 0, tempPiles.size()-1, !turn);

            tempPiles = piles;
            tempPiles.erase(tempPiles.begin() + j);
            bool takeLast = dfs(tempPiles, x, y+piles[j], 0, tempPiles.size()-1, !turn);
            return memo[{x,y}] = takeFirst || takeLast;
        }

    }
public:
    bool stoneGame(vector<int>& piles) {
       return dfs(piles, 0,0,0,piles.size()-1,true);
    }
};
```

---

# 2. Parity Strategy (Optimal Insight)

## Intuition

Since the number of piles is even, we can divide them into:

- even indices
- odd indices

The total number of stones is odd, so:

- evenSum ≠ oddSum
- one must be strictly greater

Alice can choose which parity to follow from the first move and will always pick from that group.

---

## Approach

- Compute sum of even indices
- Compute sum of odd indices
- Alice chooses the larger one

Since she can always enforce that choice, she is guaranteed to win.

---

## Complexity

- Time complexity:
  $$O(n)$$

- Space complexity:
  $$O(1)$$

---

## Code

```cpp
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};
```

---

# 3. Top-Down DP (Recursion + Memoization)

## Intuition

Instead of tracking both players separately, we track the **score difference** between the current player and the opponent.

This simplifies the problem:

- current player tries to maximize advantage
- opponent’s best move is automatically subtracted

---

## Approach

Define:

```text
dfs(i, j) = maximum score difference current player can achieve from piles[i...j]
```

Transition:

```text
dfs(i, j) = max(
    piles[i] - dfs(i+1, j),
    piles[j] - dfs(i, j-1)
)
```

Base case:

```text
i == j → piles[i]
```

Use memoization to avoid recomputation.

---

## Complexity

- Time complexity:
  $$O(n^2)$$

- Space complexity:
  $$O(n^2)$$

---

## Code

```cpp
class Solution {
private:
    vector<vector<int>> memo;

    int dfs(vector<int>& piles, int i, int j) {
        if (i == j) return piles[i];

        if (memo[i][j] != -1) return memo[i][j];

        int takeLeft = piles[i] - dfs(piles, i+1, j);
        int takeRight = piles[j] - dfs(piles, i, j-1);

        return memo[i][j] = max(takeLeft, takeRight);
    }

public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        memo.assign(n, vector<int>(n, -1));

        return dfs(piles, 0, n-1) > 0;
    }
};
```

---

# 4. Bottom-Up DP (Tabulation)

## Intuition

Same idea as top-down, but instead of recursion, we build the solution iteratively using a table.

We again track **score difference**, not individual scores.

---

## Approach

Define:

```text
dp[i][j] = max difference current player can achieve from piles[i...j]
```

Base case:

```text
dp[i][i] = piles[i]
```

Transition:

```text
dp[i][j] = max(
    piles[i] - dp[i+1][j],
    piles[j] - dp[i][j-1]
)
```

Fill table from smaller ranges to larger ranges.

---

## Complexity

- Time complexity:
  $$O(n^2)$$

- Space complexity:
  $$O(n^2)$$

---

## Code

```cpp
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            dp[i][i] = piles[i];
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;

                dp[i][j] = max(
                    piles[i] - dp[i+1][j],
                    piles[j] - dp[i][j-1]
                );
            }
        }

        return dp[0][n-1] > 0;
    }
};
```

---

Yes — this is your **parity-based constructive method**. It deserves its own proper section because it shows _how Alice actually wins_, not just “return true”.

---

# 5. Parity-Based Constructive Method (Your Code)

## Intuition

Since the number of piles is even, we can divide them into two groups:

- even indices → 0, 2, 4, ...
- odd indices → 1, 3, 5, ...

The total sum is **odd**, so:

```text
evenSum ≠ oddSum
```

So one group must have strictly more stones.

---

## Key Observation

Alice can **force herself to pick from only one group (even OR odd indices)**.

How?

- First move decides the parity:
  - pick left → locks one parity
  - pick right → locks the other

After that:

- Whatever Bob picks, Alice always has access to the required parity element on the next move

So she keeps collecting from the chosen group.

---

## Approach

1. Compute:
   - `alice1 = sum of even indices`
   - `alice2 = sum of odd indices`

2. Compute Bob’s corresponding scores:
   - `bob1 = total - alice1`
   - `bob2 = total - alice2`

3. Check:
   - If Alice can win by choosing either parity

---

## Simplification

Your condition:

```cpp
(alice1 > bob1 || alice2 > bob2)
```

is equivalent to:

```text
max(alice1, alice2) > total / 2
```

And due to constraints (even length + odd total):

```cpp
return true;
```

---

## Complexity

- Time complexity:
  $$O(n)$$

- Space complexity:
  $$O(1)$$

---

## Code (Your Version)

```cpp
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int alice1 = 0;
        int alice2 = 0;
        int sum = accumulate(piles.begin(), piles.end(), 0);

        for (int i = 0; i < piles.size(); i += 2) {
            alice1 += piles[i];
        }
        for (int i = 1; i < piles.size(); i += 2) {
            alice2 += piles[i];
        }

        int bob1 = sum - alice1;
        int bob2 = sum - alice2;

        return (alice1 > bob1 || alice2 > bob2);
    }
};
```

---

## Concept

This method is not DP.

This is:

```text
Game theory + invariant (parity control)
```

# Final Summary

- Brute force → correct thinking, wrong execution
- Parity → best and simplest
- Top-down DP → clean recursive logic
- Bottom-up DP → iterative version of same
