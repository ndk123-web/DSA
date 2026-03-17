# Intuition

We are given a grid where each cell contains a non-negative number. We need to find a path from the **top-left** cell `(0,0)` to the **bottom-right** cell `(m-1,n-1)` such that the **sum of all numbers along the path is minimized**.

The robot can only move:

- **Right →**
- **Down ↓**

This means every cell `(i, j)` can only be reached from:

- `(i-1, j)` → from **top**
- `(i, j-1)` → from **left**

So the minimum cost to reach a cell depends on the **minimum cost of its previous cells**.

The key recurrence relation becomes:

```text
dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
```

This is a classic **2D Dynamic Programming** problem where each state depends on previously solved subproblems.

---

# Approach 1: Top-Down Dynamic Programming (DFS + Memoization)

### Idea

We define a recursive function:

```text
dfs(r, c)
```

which represents the **minimum path sum required to reach cell (r,c)**.

Base cases:

- If `(r,c)` is outside the grid → return a large value (`INT_MAX`) so it won't affect the minimum.
- If `(r,c)` is `(0,0)` → return `grid[0][0]`.

To avoid recomputing the same states, we store results in a **memo table**.

For each cell:

```text
dfs(r,c) = min(dfs(r-1,c), dfs(r,c-1)) + grid[r][c]
```

---

### Code

```cpp
class Solution {
private:
    vector<vector<int>> memo;

    int dfs(vector<vector<int>>& grid, int r, int c) {

        if (r < 0 || c < 0) return INT_MAX;

        if (r == 0 && c == 0) return grid[0][0];

        if (memo[r][c] != -1) return memo[r][c];

        int left = dfs(grid, r, c-1);
        int up   = dfs(grid, r-1, c);

        return memo[r][c] = min(left, up) + grid[r][c];
    }

public:
    int minPathSum(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        memo = vector<vector<int>>(m, vector<int>(n, -1));

        return dfs(grid, m-1, n-1);
    }
};
```

---

### Complexity

**Time Complexity**

```text
O(m × n)
```

Each state `(i,j)` is computed only once.

**Space Complexity**

```text
O(m × n)
```

For the memoization table and recursion stack.

---

# Approach 2: Bottom-Up Dynamic Programming (Tabulation)

### Idea

Instead of recursion, we fill a DP table iteratively.

Let:

```text
dp[i][j] = minimum path sum to reach (i,j)
```

Steps:

1. Initialize the first cell:

```text
dp[0][0] = grid[0][0]
```

2. Fill the **first column** (only downward movement possible):

```text
dp[i][0] = dp[i-1][0] + grid[i][0]
```

3. Fill the **first row** (only right movement possible):

```text
dp[0][j] = dp[0][j-1] + grid[0][j]
```

4. Fill the rest of the grid using the recurrence:

```text
dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
```

---

### Code

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n));

        dp[0][0] = grid[0][0];

        for(int i = 1; i < m; i++){
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }

        for(int j = 1; j < n; j++){
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }

        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }

        return dp[m-1][n-1];
    }
};
```

---

### Complexity

**Time Complexity**

```text
O(m × n)
```

We process every cell once.

**Space Complexity**

```text
O(m × n)
```

For the DP table.

---

# Key Takeaways

- Each cell depends only on **two previous states**.
- The problem is a classic **2D Dynamic Programming pattern**.
- Both **Top-Down (memoization)** and **Bottom-Up (tabulation)** implement the same recurrence.
- Bottom-Up is usually preferred because it avoids recursion overhead.

---
