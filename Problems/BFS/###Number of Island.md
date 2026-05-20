# Approach 1: Depth First Search (DFS)

## Intuition

Each island is a group of connected `'1'` cells.

Whenever we encounter a new land cell:

```text id="m0kc58"
grid[i][j] == '1'
```

it means we found a new island.

We then use DFS to traverse and mark all connected land cells as visited by converting them into `'0'`.

This ensures the same island is counted only once.

---

# DFS Traversal Logic

From one land cell, recursively visit:

* Up
* Down
* Left
* Right

until:

* boundary reached
* or water (`'0'`) reached.

---

# Algorithm

1. Traverse entire grid.
2. If current cell is `'1'`:

   * increment island count
   * run DFS from that cell
3. DFS floods the whole connected island.

---

# Complexity Analysis

## Time Complexity

Every cell is visited once:

```text id="m1kc59"
O(m × n)
```

---

## Space Complexity

Recursive call stack in worst case:

```text id="m2kc60"
O(m × n)
```

---

# DFS Code

```cpp id="m3kc61"
class Solution {
public:

    void dfs(vector<vector<char>>& grid,
             int row,
             int col) {

        // Out of bounds or water
        if (row < 0 ||
            col < 0 ||
            row >= grid.size() ||
            col >= grid[0].size() ||
            grid[row][col] == '0') {

            return;
        }

        // Mark visited
        grid[row][col] = '0';

        // Explore 4 directions
        dfs(grid, row + 1, col);
        dfs(grid, row - 1, col);
        dfs(grid, row, col + 1);
        dfs(grid, row, col - 1);
    }

    int numIslands(vector<vector<char>>& grid) {

        int islands = 0;

        for (int i = 0; i < grid.size(); i++) {

            for (int j = 0; j < grid[0].size(); j++) {

                // New island found
                if (grid[i][j] == '1') {

                    islands++;

                    dfs(grid, i, j);
                }
            }
        }

        return islands;
    }
};
```

---

# Approach 2: Breadth First Search (BFS)

## Intuition

Instead of recursively exploring deeply like DFS,

BFS explores neighboring land cells level by level using a queue.

Whenever a new `'1'` cell is found:

* increment island count
* push it into queue
* flood the whole island using BFS.

---

# BFS Traversal Logic

For every popped cell:

* check all 4 directions
* if neighboring cell is land (`'1'`)

  * mark visited
  * push into queue

---

# Algorithm

1. Traverse grid.
2. If new land found:

   * increment islands
   * run BFS traversal
3. BFS removes the entire connected component.

---

# Complexity Analysis

## Time Complexity

Every cell processed once:

```text id="m4kc62"
O(m × n)
```

---

## Space Complexity

Queue may contain many cells:

```text id="m5kc63"
O(m × n)
```

---

# BFS Code

```cpp id="m6kc64"
class Solution {
public:

    void bfs(vector<vector<char>>& grid,
             int row,
             int col) {

        queue<pair<int,int>> q;

        q.push({row, col});

        // Mark visited
        grid[row][col] = '0';

        vector<pair<int,int>> directions = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
        };

        while (!q.empty()) {

            auto [r, c] = q.front();
            q.pop();

            for (auto [dr, dc] : directions) {

                int nr = r + dr;
                int nc = c + dc;

                // Valid land cell
                if (nr >= 0 &&
                    nc >= 0 &&
                    nr < grid.size() &&
                    nc < grid[0].size() &&
                    grid[nr][nc] == '1') {

                    grid[nr][nc] = '0';

                    q.push({nr, nc});
                }
            }
        }
    }

    int numIslands(vector<vector<char>>& grid) {

        int islands = 0;

        for (int i = 0; i < grid.size(); i++) {

            for (int j = 0; j < grid[0].size(); j++) {

                if (grid[i][j] == '1') {

                    islands++;

                    bfs(grid, i, j);
                }
            }
        }

        return islands;
    }
};
```

---

# Key Pattern Learned

This problem is a classic:

```text id="m7kc65"
Connected Components in Grid
```