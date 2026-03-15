# Unique Paths

## Problem

You are given an `m x n` grid. A robot starts at the **top-left corner** `(0,0)` and wants to reach the **bottom-right corner** `(m-1,n-1)`.

The robot can only move:

- **Right →**
- **Down ↓**

Return the **number of unique paths** to reach the destination.

You may assume the answer fits within a **32-bit integer**.

---

# Intuition

At any cell `(i, j)` the robot could have come from only two places:

- **Top cell** `(i-1, j)`
- **Left cell** `(i, j-1)`

Therefore the number of ways to reach `(i, j)` is the sum of ways to reach those two cells.

```
dp[i][j] = dp[i-1][j] + dp[i][j-1]
```

---

# Base Case

Cells in the **first row** can only be reached by moving right.

```
(0,0) → (0,1) → (0,2) → ...
```

So:

```
dp[0][j] = 1
```

Cells in the **first column** can only be reached by moving down.

```
(0,0)
 ↓
(1,0)
 ↓
(2,0)
```

So:

```
dp[i][0] = 1
```

Example grid initialization:

```
1 1 1
1 0 0
1 0 0
```

---

# Approach 1: Top-Down (DFS + Memoization)

We recursively compute the number of ways to reach `(r,c)`.

If the value is already computed in `dp`, we reuse it.

### Key Idea

```
ways(r,c) = ways(r-1,c) + ways(r,c-1)
```

### Code

```cpp
class Solution {
public:
    int dfs(vector<vector<int>>& dp, int r, int c) {

        if (r < 0 || c < 0) {
            return 0;
        }

        if (dp[r][c] != 0) {
            return dp[r][c];
        }

        return dp[r][c] = dfs(dp, r - 1, c) + dfs(dp, r, c - 1);
    }

    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }

        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
        }

        return dfs(dp, m - 1, n - 1);
    }
};
```

### Complexity

Time Complexity

```
O(m × n)
```

Space Complexity

```
O(m × n)
```

Recursion stack may also go up to `O(m+n)`.

---

# Approach 2: Bottom-Up (Tabulation)

Instead of recursion, we directly build the DP table from the base cases.

We iterate over the grid and fill each cell using the recurrence:

```
dp[i][j] = dp[i-1][j] + dp[i][j-1]
```

### Code

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }

        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
    }
};
```

### Complexity

Time Complexity

```
O(m × n)
```

Space Complexity

```
O(m × n)
```

---

# Example

Input

```
m = 3
n = 3
```

DP table formation:

```
1 1 1
1 2 3
1 3 6
```

Result:

```
6 unique paths
```

---

# Key Takeaways

- Grid problems often lead to **2D Dynamic Programming**.
- Each cell depends on **previous reachable states**.
- The recurrence is derived from **valid movements**.
- Always define the **DP meaning clearly**:

```
dp[i][j] = number of ways to reach cell (i,j)
```
