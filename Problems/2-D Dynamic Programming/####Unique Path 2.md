# Unique Paths II

## Problem

You are given an `m x n` grid. A robot starts at the **top-left cell** `(0,0)` and wants to reach the **bottom-right cell** `(m-1,n-1)`.

The robot can only move:

- **Right →**
- **Down ↓**

Some cells contain **obstacles (`1`)**, and the robot **cannot pass through them**.

Return the **total number of unique paths** the robot can take to reach the destination.

Constraints ensure the answer fits within a **32-bit integer**.

---

# Key Idea

This problem is an extension of **Unique Paths**.

In the original problem:

```
dp[i][j] = ways from top + ways from left
```

But now we add one rule:

```
If a cell contains an obstacle → ways = 0
```

So the recurrence becomes:

```
dp[i][j] = dp[i-1][j] + dp[i][j-1]   (if not obstacle)
```

---

# Important Observation

The **first row and first column** need special handling.

Because the robot can only move:

```
RIGHT → or DOWN ↓
```

If an obstacle appears in the first row or column, **all cells after it become unreachable**.

Example:

```
0
1
0
```

Correct paths:

```
1
0
0
```

Once the obstacle blocks the path, the robot cannot move further.

---

# Approach 1 — Bottom Up (Tabulation)

## Idea

We build the DP table iteratively.

Each cell represents:

```
dp[i][j] = number of ways to reach cell (i,j)
```

Steps:

1. Convert obstacles into `-1` in the DP grid.
2. Initialize first row and column until an obstacle appears.
3. Fill remaining cells using the recurrence relation.
4. If the destination cell is an obstacle, return `0`.

---

## Code

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dp[i][j] = -1;
                }
            }
        }

        bool isAppear = false;
        for (int i = 0; i < m; i++) {
            if (!isAppear) {
                if (dp[i][0] == -1) {
                    isAppear = true;
                } else {
                    dp[i][0] = 1;
                }
            }
        }

        isAppear = false;
        for (int i = 0; i < n; i++) {
            if (!isAppear) {
                if (dp[0][i] == -1) {
                    isAppear = true;
                } else {
                    dp[0][i] = 1;
                }
            }
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {

                if (dp[i][j] == -1) {
                    continue;
                }

                if (dp[i-1][j] > 0) {
                    dp[i][j] += dp[i-1][j];
                }

                if (dp[i][j-1] > 0) {
                    dp[i][j] += dp[i][j-1];
                }
            }
        }

        return dp[m - 1][n - 1] == -1 ? 0 : dp[m-1][n-1];
    }
};
```

---

## Complexity

Time Complexity

```
O(m × n)
```

Space Complexity

```
O(m × n)
```

---

# Approach 2 — Top Down (DFS + Memoization)

## Idea

Instead of filling the table iteratively, we compute the number of paths **recursively**.

Define a function:

```
dfs(r,c)
```

Meaning:

```
number of ways to reach cell (r,c)
```

Transition:

```
ways(r,c) = ways(r-1,c) + ways(r,c-1)
```

Base rules:

- If out of bounds → return `0`
- If obstacle → return `0`
- If value already computed → return stored value

Memoization avoids recomputation of states.

---

## Code

```cpp
class Solution {
private:
    int dfs(vector<vector<int>>& dp, int r, int c) {
        if (r < 0 || c < 0 || dp[r][c] == -1) {
            return 0;
        }

        if (dp[r][c] > 0) {
            return dp[r][c];
        }

        dp[r][c] = dfs(dp, r - 1, c) + dfs(dp, r, c - 1);
        return dp[r][c];
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dp[i][j] = -1;
                }
            }
        }

        bool isAppear = false;
        for (int i = 0; i < m; i++) {
            if (!isAppear) {
                if (dp[i][0] == -1) {
                    isAppear = true;
                } else {
                    dp[i][0] = 1;
                }
            }
        }

        isAppear = false;
        for (int i = 0; i < n; i++) {
            if (!isAppear) {
                if (dp[0][i] == -1) {
                    isAppear = true;
                } else {
                    dp[0][i] = 1;
                }
            }
        }

        return dfs(dp, m - 1, n - 1);
    }
};
```

---

# Example

Input

```
grid =
[
 [0,0,0],
 [0,1,0],
 [0,0,0]
]
```

Obstacle blocks the center cell.

Possible paths:

```
Right → Right → Down → Down
Down → Down → Right → Right
```

Result

```
2
```

---

# Key Takeaways

- This is a classic **2D Dynamic Programming** problem.
- Each state depends on **two previous states** (top and left).
- Obstacles act as **blocking states with zero paths**.
- Border initialization must stop when an obstacle appears.

DP definition used:

```
dp[i][j] = number of ways to reach cell (i,j)
```
