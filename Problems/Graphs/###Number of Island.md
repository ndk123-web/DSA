# 📘 Number of Islands (LeetCode 200)

---

## 🧠 Problem Intuition

You are given a 2D grid where:

- `'1'` represents **land**
- `'0'` represents **water**

An **island** is formed by connecting adjacent lands **horizontally or vertically**.

👉 Task: Count the number of **distinct islands**.

---

## 🔑 Core Insight

An island is not a single cell — it is a **connected component** of `'1'`s.

So the strategy is:

- Traverse the grid
- When a new land cell is found:
  - Count it as a new island
  - Explore and mark the entire connected land as visited

---

## 🧩 Approach (DFS Flood Fill)

1. Traverse every cell in the grid
2. If a cell contains `'1'`:
   - Increment island count
   - Run DFS from that cell to **mark the entire island as water (`'0'`)**

3. Continue traversal — already visited land won’t be counted again

This ensures:

- Each island is counted **exactly once**
- No extra `visited` array is needed

---

## 🛠️ Algorithm

### DFS Function

- Stop if:
  - Out of bounds
  - Cell is water (`'0'`)

- Otherwise:
  - Mark the current land as visited by setting it to `'0'`
  - Explore all 4 directions (up, down, left, right)

### Main Function

- Loop through the grid
- Start DFS whenever a fresh land cell is found

---

## ✅ Code Implementation

```cpp
class Solution {
private:
    int count;
    int rows, cols;

    void dfs(vector<vector<char>>& grid, int r, int c) {
        // boundary or water check
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == '0')
            return;

        // mark current land as visited
        grid[r][c] = '0';

        // explore neighbors
        dfs(grid, r + 1, c);
        dfs(grid, r - 1, c);
        dfs(grid, r, c - 1);
        dfs(grid, r, c + 1);
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        count = 0;
        rows = grid.size();
        cols = grid[0].size();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j); // explore full island
                }
            }
        }
        return count;
    }
};
```

---

## 🧪 Example Walkthrough

### Input

```
grid =
[
  ['1','1','0','0'],
  ['1','1','0','0'],
  ['0','0','1','0'],
  ['0','0','0','1']
]
```

### Execution

- First DFS → covers top-left island
- Second DFS → covers middle island
- Third DFS → covers bottom-right island

### Output

```
3
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
O(rows × cols)   // recursion stack in worst case
```

---

## 🔒 Key Takeaways

- An island is a **connected component**, not a special cell
- DFS/BFS is mandatory for such problems
- Marking the grid itself avoids extra memory
- Each DFS call represents **one island**
