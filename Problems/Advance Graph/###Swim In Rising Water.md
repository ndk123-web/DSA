# 🧊 Solution 1 — Brute Force (DFS)

# Intuition

The water level rises uniformly across the grid.
To reach the bottom-right cell, we must choose a path such that the **maximum elevation on that path is minimized**.

A brute-force idea is to try all possible paths from `(0,0)` to `(n-1,n-1)` and compute:

```
max elevation along that path
```

Among all paths, return the minimum such value.

This guarantees correctness because we explore every possible path.

---

# Approach

1. Start DFS from `(0,0)`.
2. Maintain:
   - Current maximum elevation encountered so far.

3. When reaching bottom-right:
   - Update global minimum answer.

4. Backtrack to explore other paths.
5. Use `visited` matrix to avoid cycles.

This explores all possible paths and computes the minimum bottleneck path.

However, this is extremely slow for large grids.

---

# Complexity

- Time complexity:
  Worst case $$O(4^{n^2})$$
  (Explores all possible paths)

- Space complexity:
  $$O(n^2)$$ for recursion stack and visited array

---

# Code

```cpp
class Solution {
private:
    vector<vector<int>> grid;
    int minValue;
    int ROWS, COLS;
    vector<vector<bool>> visited;
    vector<vector<int>> dirs;

    void dfs(int h, int r, int c) {
        if (r == ROWS - 1 && c == COLS - 1) {
            minValue = min(h, minValue);
            return;
        }

        if (r < 0 || c < 0 || r >= ROWS || c >= COLS) return;
        if (visited[r][c]) return;

        visited[r][c] = true;

        for (vector<int>& dir : dirs) {
            int nr = r + dir[0];
            int nc = c + dir[1];

            if (nr >= 0 && nc >= 0 && nr < ROWS && nc < COLS) {
                dfs(max(h, grid[nr][nc]), nr, nc);
            }
        }

        visited[r][c] = false;
    }

public:
    int swimInWater(vector<vector<int>>& grid) {
        ROWS = grid.size();
        COLS = grid[0].size();
        visited.assign(ROWS, vector<bool>(COLS, false));
        minValue = INT_MAX;
        this->grid = grid;
        dirs = {{0,1},{0,-1},{1,0},{-1,0}};

        dfs(grid[0][0], 0, 0);
        return minValue;
    }
};
```

---

---

# 🌊 Solution 2 — Optimal (Dijkstra / Min-Heap)

# Intuition

We are not minimizing the sum of heights.

We are minimizing:

```
maximum height encountered along the path
```

This is a **minimum bottleneck path** problem.

At time `t`, we can only step on cells with height ≤ `t`.

So we want the smallest `t` such that start and end become connected.

This can be solved using a modified Dijkstra approach:

- Always expand the cell with the smallest height first.
- Keep track of the maximum height seen so far.

This effectively builds a Minimum Spanning Tree from `(0,0)` outward.

---

# Approach

1. Use a min-heap storing `{height, {row, col}}`.
2. Start from `(0,0)`.
3. Always expand the smallest available height.
4. Keep track of the maximum height encountered so far.
5. Once we reach `(n-1,n-1)`, return that value.

We use a `visited` matrix to avoid revisiting cells.

---

# Complexity

- Time complexity:
  $$O(n^2 \log n)$$
  (Each cell inserted into heap once)

- Space complexity:
  $$O(n^2)$$
  (Heap + visited matrix)

---

# Code

```cpp
class Solution {
private:
    int ROWS, COLS;
    priority_queue<pair<int, pair<int, int>>,
                   vector<pair<int, pair<int, int>>>,
                   greater<pair<int, pair<int, int>>>> minheap;
    vector<vector<int>> dirs;
    vector<vector<bool>> visited;

    bool isValid(int r, int c) {
        if (r < 0 || c < 0 || r >= ROWS || c >= COLS || visited[r][c]) {
            return false;
        }
        return true;
    }

public:
    int swimInWater(vector<vector<int>>& grid) {
        int res = 0;
        ROWS = grid.size();
        COLS = grid[0].size();

        visited.assign(ROWS, vector<bool>(COLS, false));
        dirs = {{0,1},{0,-1},{1,0},{-1,0}};

        minheap.push({grid[0][0], {0,0}});

        while (!minheap.empty()) {
            auto [height, cell] = minheap.top();
            minheap.pop();

            int r = cell.first;
            int c = cell.second;

            if (visited[r][c]) continue;

            visited[r][c] = true;
            res = max(res, grid[r][c]);

            if (r == ROWS - 1 && c == COLS - 1) {
                return res;
            }

            for (vector<int>& dir : dirs) {
                int nr = r + dir[0];
                int nc = c + dir[1];

                if (isValid(nr, nc)) {
                    minheap.push({grid[nr][nc], {nr, nc}});
                }
            }
        }

        return res;
    }
};
```
