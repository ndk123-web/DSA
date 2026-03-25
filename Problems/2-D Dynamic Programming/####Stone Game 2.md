# Intuition

This is a two-player game where both players play optimally. At every turn, a player can take between `1` and `2M` piles from the front, and the value of `M` dynamically changes based on the number of piles taken.

A greedy approach does not work here because:

- Taking more piles now increases your immediate gain
- But also increases `M`, which gives the opponent more power in future moves

So every decision affects future possibilities. This makes it a **game theory + dynamic programming** problem.

Instead of tracking both players’ scores separately, we observe that:

- The total number of stones remaining from index `i` is fixed
- If the opponent gets some portion, the rest must belong to the current player

So we can model the problem in terms of:

> “maximum stones current player can get from a given state”

---

# Approach

## State Definition

We define:

```text
dfs(i, M) = maximum stones the current player can get starting from index i with current M
```

---

## Key Idea

At index `i`, the player can take `X` piles where:

```text
1 ≤ X ≤ 2M
```

For each choice of `X`:

- Player takes piles from `i` to `i + X - 1`
- Remaining game starts from `i + X`
- New `M = max(M, X)`

---

## Optimization Using Suffix Sum

To efficiently compute remaining stones:

```text
suffix[i] = sum of piles from i to end
```

This allows:

```text
current player stones = suffix[i] - opponent stones
```

---

## Transition

```text
dfs(i, M) = max over all X:
    suffix[i] - dfs(i + X, max(M, X))
```

---

## Base Case

```text
if i >= n → return 0
```

---

## Memoization

We store results for `(i, M)` to avoid recomputation.

---

# Complexity

- Time complexity:
  $$O(n^3)$$
  (n states for `i`, n states for `M`, and up to `2M` transitions)

- Space complexity:
  $$O(n^2)$$
  (memoization table)

---

# Code

```cpp
class Solution {
private:
    vector<vector<int>> memo;
    vector<int> suffix;

    int dfs(int i, int M, vector<int>& piles) {
        int n = piles.size();

        if (i >= n) return 0;

        if (memo[i][M] != -1) return memo[i][M];

        int maxStones = 0;

        for (int X = 1; X <= 2 * M && i + X <= n; X++) {
            int opponent = dfs(i + X, max(M, X), piles);
            int current = suffix[i] - opponent;

            maxStones = max(maxStones, current);
        }

        return memo[i][M] = maxStones;
    }

public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        memo.assign(n, vector<int>(n + 1, -1));
        suffix.resize(n);

        // build suffix sum
        suffix[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = piles[i] + suffix[i + 1];
        }

        return dfs(0, 1, piles);
    }
};
```

---

# Key Concepts

1. **Game Theory + DP**
   - Both players play optimally
   - Each decision affects future moves

2. **State Representation**
   - `(i, M)` fully defines the game state
   - Avoid tracking scores directly

3. **Minimax Simplification**
   - Instead of simulating both players:

   ```text
   current = total remaining - opponent
   ```

4. **Suffix Sum Optimization**
   - Avoid recomputing sums repeatedly
