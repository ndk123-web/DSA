# 📘 Islands and Treasure (a.k.a. Walls and Gates)

---

## 🧠 Problem Overview

You are given an `m x n` grid where each cell can be:

- `-1` → Water / wall (cannot be crossed)
- `0` → Treasure (distance is 0)
- `INF (2147483647)` → Land (distance unknown)

### Goal

For every land cell (`INF`), fill it with the **shortest distance to the nearest treasure (`0`)**, moving only in **4 directions** (up, down, left, right).

If a land cell **cannot reach any treasure**, it should remain `INF`.

The grid must be **modified in-place**.

---

## 🔑 Key Insight

- Distance means **shortest valid path**, not straight-line distance.
- Walls (`-1`) can block paths.
- This is a **shortest path in an unweighted grid** problem.

---

# 🟡 Approach 1: DFS (Brute Force / Conceptual)

### 💡 Idea

For every land cell (`INF`):

- Run DFS in all directions
- Try to reach a treasure (`0`)
- Take the minimum distance among all possible paths

This approach **works logically**, but it is **inefficient**.

---

### 🧠 DFS Logic

- If you hit:
  - boundary
  - water (`-1`)
  - already visited cell
    → return `INF`

- If you reach treasure (`0`) → return `0`
- Otherwise:
  - explore all 4 directions
  - return `1 + minimum distance from neighbors`

---

### ✅ DFS Code (as given)

```cpp
class Solution {
public:
    vector<vector<int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int INF = 2147483647;
    vector<vector<bool>> visit;
    int ROWS, COLS;

    int dfs(vector<vector<int>>& grid, int r, int c) {
        if (r < 0 || c < 0 || r >= ROWS || c >= COLS ||
            grid[r][c] == -1 || visit[r][c]) {
            return INF;
        }

        if (grid[r][c] == 0) return 0;

        visit[r][c] = true;
        int res = INF;

        for (auto& dir : directions) {
            int cur = dfs(grid, r + dir[0], c + dir[1]);
            if (cur != INF) {
                res = min(res, 1 + cur);
            }
        }

        visit[r][c] = false;
        return res;
    }

    void islandsAndTreasure(vector<vector<int>>& grid) {
        ROWS = grid.size();
        COLS = grid[0].size();
        visit.assign(ROWS, vector<bool>(COLS, false));

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (grid[r][c] == INF) {
                    grid[r][c] = dfs(grid, r, c);
                }
            }
        }
    }
};
```

---

### ⏱️ Complexity (DFS)

- **Time**: Very high (can go exponential in worst case)
- **Space**: `O(ROWS × COLS)` due to recursion + visited

⚠️ This approach is **not optimal** and can TLE for large grids.

---

# 🟢 Approach 2: Multi-Source BFS (Optimal)

### 💡 Idea (MOST IMPORTANT)

Instead of starting DFS from every land cell:

👉 **Start BFS from all treasure cells (`0`) at the same time**

Why this works:

- BFS expands level by level
- First time you reach a land cell = shortest distance
- This guarantees minimum distance automatically

This is called **Multi-Source BFS**.

---

### 🧠 BFS Logic

1. Push **all treasure cells (`0`)** into a queue
2. Run BFS:
   - For each cell, visit its neighbors
   - If neighbor is `INF`, update:

     ```
     grid[neighbor] = grid[current] + 1
     ```

   - Push neighbor into queue

3. Skip walls (`-1`) and already updated cells

---

### ✅ BFS Code (Optimal Solution)

```cpp
class Solution {
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        queue<pair<int,int>> q;
        int ROWS = grid.size();
        int COLS = grid[0].size();

        // Push all treasures into queue
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (grid[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }

        vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();

            for (auto& d : dirs) {
                int r = row + d[0];
                int c = col + d[1];

                if (r < 0 || r >= ROWS || c < 0 || c >= COLS ||
                    grid[r][c] != INT_MAX) {
                    continue;
                }

                grid[r][c] = grid[row][col] + 1;
                q.push({r, c});
            }
        }
    }
};
```

---

## ⏱️ Complexity (BFS)

- **Time**: `O(ROWS × COLS)`
- **Space**: `O(ROWS × COLS)` (queue in worst case)

This is the **recommended and optimal solution**.

---

## 🆚 DFS vs BFS Comparison

| Aspect                  | DFS              | BFS                  |
| ----------------------- | ---------------- | -------------------- |
| Correctness             | ✅               | ✅                   |
| Efficiency              | ❌ Slow          | ✅ Fast              |
| Shortest path guarantee | ❌               | ✅                   |
| Interview preferred     | ❌               | ✅                   |
| Pattern name            | Backtracking DFS | **Multi-Source BFS** |

---

## 🔒 Final Takeaways

- `INF` means **distance not yet known**
- Walls block paths, so nearest ≠ reachable
- DFS checks all paths (slow)
- BFS finds shortest path naturally
- **Multiple starting points → Multi-Source BFS**

---

## 🧠 One-Line Lock

> **When distance to nearest source is required in a grid,
> always think Multi-Source BFS first.**
