# 📘 Max Area of Island (LeetCode 695)

---

## 🧠 Problem Intuition

You are given a 2D grid where:

- `1` represents **land**
- `0` represents **water**

An **island** is a group of `1`s connected **horizontally or vertically**.

The **area of an island** is the total number of land cells in that connected component.

👉 Goal: **Return the maximum area among all islands**.
If no island exists, return `0`.

---

## 🔑 Core Insight

This is a **connected components** problem.

For each unvisited land cell:

- Run DFS to explore the entire island
- Count how many cells belong to that island
- Update the maximum area

Key idea:

> **DFS returns the area contributed by the current cell**

---

## 🧩 Approach (DFS Flood Fill)

1. Traverse the grid cell by cell
2. When a land cell (`1`) is found:
   - Run DFS from that cell
   - DFS:
     - Marks the cell as visited by setting it to `0`
     - Recursively explores all 4 directions
     - Returns the total area of that island

3. Track the maximum area seen so far

No extra `visited` array is needed — the grid itself is modified.

---

## 🛠️ Algorithm

### DFS Function

- **Base case**:
  - Out of bounds
  - Water cell (`0`)

- **Recursive case**:
  - Mark current cell as visited
  - Return:

    ```
    1 + area(up) + area(down) + area(left) + area(right)
    ```

### Main Function

- Loop through all cells
- For every fresh land cell:
  - Compute island area using DFS
  - Update `maxArea`

---

## ✅ Code Implementation

```cpp
class Solution {
private:
    int maxArea;
    int rows, cols;

    int dfs(vector<vector<int>>& grid, int r, int c) {
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == 0)
            return 0;

        // mark as visited
        grid[r][c] = 0;

        return 1
            + dfs(grid, r+1, c)
            + dfs(grid, r-1, c)
            + dfs(grid, r, c+1)
            + dfs(grid, r, c-1);
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        maxArea = 0;
        rows = grid.size();
        cols = grid[0].size();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1) {
                    maxArea = max(maxArea, dfs(grid, i, j));
                }
            }
        }
        return maxArea;
    }
};
```

---

## 🧪 Example Walkthrough

### Input

```
grid =
[
  [0,0,1,0,0],
  [0,1,1,1,0],
  [0,0,1,0,0],
  [1,0,0,0,0]
]
```

### DFS Explorations

- First island → area = 5
- Second island → area = 1

### Output

```
5
```

---

## ⏱️ Complexity Analysis

### Time Complexity

```
O(rows × cols)
```

Each cell is visited at most once.

### Space Complexity

```
O(rows × cols)
```

Worst case recursion stack (entire grid is land).

---

## 🔒 Key Takeaways

- Islands are **connected components**
- DFS is used to **explore and count**
- Marking visited cells prevents revisiting
- DFS return value represents **area contribution**
- Counting happens **after DFS**, not during traversal
