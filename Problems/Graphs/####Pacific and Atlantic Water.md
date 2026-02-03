# 🌊 Pacific Atlantic Water Flow

## 📌 Problem Summary

You are given a grid `heights[r][c]` representing an island.

- **Pacific Ocean** touches the **top & left** borders
- **Atlantic Ocean** touches the **bottom & right** borders
- Water can move **up, down, left, right**
- Water flows only to cells of **equal or lower height**

### Objective

Find all cells from which water can flow to **both oceans**.

---

## 🧠 Core Logic & Concept

Instead of checking **each cell → ocean** (slow & repetitive), we reverse the logic:

> If water can flow from a cell to an ocean,
> then starting **from the ocean**, we should be able to reach that cell
> by moving only to **equal or higher height** cells.

So:

- Run DFS from **Pacific borders**
- Run DFS from **Atlantic borders**
- Mark reachable cells
- Take intersection

This is a **reverse graph traversal** problem.

---

## 🧩 Algorithm Breakdown

1. Create two boolean matrices:
   - `pac[r][c]` → reachable from Pacific
   - `atl[r][c]` → reachable from Atlantic

2. DFS rules:
   - From ocean, move **uphill or same height**
   - Avoid revisiting cells

3. Final result:
   - Cells where `pac[r][c] && atl[r][c]` is true

---

## ✅ C++ Implementation

```cpp
class Solution {
private:
    vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    vector<vector<bool>> pac, atl;
    int ROWS, COLS;

    void dfs(int r, int c, vector<vector<bool>>& ocean, vector<vector<int>>& heights) {
        ocean[r][c] = true;

        for (auto& d : dirs) {
            int nr = r + d[0];
            int nc = c + d[1];

            if (nr < 0 || nc < 0 || nr >= ROWS || nc >= COLS)
                continue;

            if (ocean[nr][nc])
                continue;

            // Reverse flow condition
            if (heights[nr][nc] >= heights[r][c]) {
                dfs(nr, nc, ocean, heights);
            }
        }
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        ROWS = heights.size();
        COLS = heights[0].size();

        pac = vector<vector<bool>>(ROWS, vector<bool>(COLS, false));
        atl = vector<vector<bool>>(ROWS, vector<bool>(COLS, false));

        // Pacific Ocean (top row & left column)
        for (int c = 0; c < COLS; c++)
            dfs(0, c, pac, heights);
        for (int r = 0; r < ROWS; r++)
            dfs(r, 0, pac, heights);

        // Atlantic Ocean (bottom row & right column)
        for (int c = 0; c < COLS; c++)
            dfs(ROWS - 1, c, atl, heights);
        for (int r = 0; r < ROWS; r++)
            dfs(r, COLS - 1, atl, heights);

        vector<vector<int>> res;

        // Intersection
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (pac[r][c] && atl[r][c]) {
                    res.push_back({r, c});
                }
            }
        }

        return res;
    }
};
```

---

## 🧪 Example

Input:

```
4 2 7 3 4
7 4 6 4 7
6 3 5 3 6
```

Output:

```
[[0,2],[0,4],[1,0],[1,1],[1,2],[1,3],[1,4],[2,0]]
```

---

## ⏱ Complexity Analysis

- **Time:** `O(ROWS × COLS)`
  - Each cell visited at most twice

- **Space:** `O(ROWS × COLS)`
  - Visited matrices + recursion stack
