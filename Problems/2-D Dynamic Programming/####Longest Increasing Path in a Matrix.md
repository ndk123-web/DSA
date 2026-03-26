# Intuition

At each cell in the matrix, we want to explore all possible paths that are **strictly increasing**. From any cell, we can move in four directions (up, down, left, right), but only if the next cell has a **greater value**.

A brute force approach would try all paths starting from each cell, but that would lead to exponential time due to repeated computations.

The key observation is:

- If we already know the longest increasing path starting from a cell, we should **reuse that result** instead of recomputing it.

This leads to using **DFS with memoization (Top-Down DP)**.

---

# Approach

## Step 1: Define the State

We define:

```text
dfs(i, j) = length of the longest increasing path starting from cell (i, j)
```

---

## Step 2: Explore Neighbors

From `(i, j)`, we try all 4 directions:

- Move only if:
  - It is within bounds
  - `matrix[nr][nc] > matrix[i][j]` (strictly increasing)

---

## Step 3: Recurrence

```text
dfs(i, j) = 1 + max(dfs(nr, nc)) for all valid neighbors
```

If no valid neighbor exists:

```text
dfs(i, j) = 1
```

(The path includes at least the current cell)

---

## Step 4: Memoization

We store results in a 2D array `memo`:

- If `memo[i][j]` is already computed, return it directly
- This avoids recomputation and reduces time complexity

---

## Step 5: Compute Answer

Run DFS from every cell:

```text
result = max(dfs(i, j)) for all (i, j)
```

---

# Complexity

- Time complexity:
  $$O(m \times n)$$
  Each cell is computed once, and each computation explores at most 4 directions.

- Space complexity:
  $$O(m \times n)$$
  For memoization + recursion stack.

---

# Code

```cpp
class Solution {
private:
    int r, c;
    vector<vector<int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    vector<vector<int>> memo;

    int dfs(vector<vector<int>>& matrix, int i, int j) {
        if (memo[i][j] != -1) return memo[i][j];

        int res = 1; // include current cell

        for (auto& dir : dirs) {
            int nr = i + dir[0];
            int nc = j + dir[1];

            if (nr >= 0 && nc >= 0 && nr < r && nc < c &&
                matrix[nr][nc] > matrix[i][j]) {

                res = max(res, 1 + dfs(matrix, nr, nc));
            }
        }

        return memo[i][j] = res;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        r = matrix.size();
        c = matrix[0].size();

        memo.assign(r, vector<int>(c, -1));

        int res = 0;

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res = max(res, dfs(matrix, i, j));
            }
        }

        return res;
    }
};
```

---

# Key Concepts

1. **DFS + Memoization (Top-Down DP)**
   - Avoid recomputation by storing results

2. **Directed Acyclic Graph (DAG)**
   - Strictly increasing condition ensures no cycles

3. **Optimal Substructure**
   - Longest path from `(i, j)` depends on its neighbors
