# 📘 Island Perimeter

**(DFS + Boundary Counting)**

---

## 🧠 Problem Intuition

You are given a 2D grid where:

- `1` represents land
- `0` represents water
- There is **exactly one island**
- The island has **no lakes** (water inside)

👉 The task is to compute the **perimeter** of the island.

---

## 🔑 Key Observation

Each land cell has **4 sides**.

A side contributes to the perimeter if:

- it touches water (`0`)
- or it is outside the grid boundary

So perimeter is essentially:

> **number of land edges exposed to water or boundary**

---

## 🧠 Why DFS Works Here

Instead of iterating all cells and checking neighbors, we can:

- start DFS from **any one land cell**
- traverse the entire island
- count perimeter contribution **during traversal**

DFS ensures:

- every land cell is visited once
- perimeter is accumulated correctly
- no double counting (using `visited`)

---

## 🧩 DFS Logic (Most Important Part)

### DFS Function Meaning

```cpp
dfs(r, c)
```

Returns:

> **perimeter contributed by the land cell at `(r, c)`**

---

### 🔹 Base Case 1: Out of bounds OR water

```cpp
if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == 0)
    return 1;
```

👉 This means:

- current land edge touches water or boundary
- **this edge contributes 1 to perimeter**

---

### 🔹 Base Case 2: Already visited land

```cpp
if (visited[r][c])
    return 0;
```

👉 Already counted earlier
👉 Avoid double counting

---

### 🔹 Recursive Case: Unvisited land

```cpp
visited[r][c] = true;
return dfs(left) + dfs(right) + dfs(up) + dfs(down);
```

👉 Explore all 4 directions
👉 Accumulate perimeter contributions

---

## 🛠️ Full Solution Code

```cpp
class Solution {
private:
    vector<vector<bool>> visited;
    vector<vector<int>> grid;
    int rows, cols;

    int dfs(int r, int c) {
        // Water or boundary contributes to perimeter
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == 0) {
            return 1;
        }

        // Already visited land
        if (visited[r][c]) {
            return 0;
        }

        visited[r][c] = true;

        return dfs(r, c - 1)   // left
             + dfs(r, c + 1)   // right
             + dfs(r + 1, c)   // down
             + dfs(r - 1, c);  // up
    }

public:
    int islandPerimeter(vector<vector<int>>& grid) {
        this->grid = grid;
        rows = grid.size();
        cols = grid[0].size();

        visited = vector<vector<bool>>(rows, vector<bool>(cols, false));

        // Start DFS from the first land cell found
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1) {
                    return dfs(i, j);
                }
            }
        }
        return 0;
    }
};
```

---

## 🧪 Example Walkthrough

### Input

```
grid =
[
  [0,1,0,0],
  [1,1,1,0],
  [0,1,0,0],
  [1,1,0,0]
]
```

DFS starts at first `1`.

Each time DFS:

- touches water → +1
- touches boundary → +1
- touches visited land → +0

Final accumulated value = **16**

---

## ⏱️ Time & Space Complexity

### Time Complexity

- **O(rows × cols)**
  Each cell visited at most once.

### Space Complexity

- **O(rows × cols)**
  For `visited` array and recursion stack.

---

## 🧠 Why This Solution Is Elegant

- No manual edge checking
- No special cases
- Boundary and water handled uniformly
- DFS naturally accumulates perimeter

---

## 🧩 Comparison with Iterative Solution

| Approach            | Uses DFS | Uses visited | Clean |
| ------------------- | -------- | ------------ | ----- |
| Brute force         | ❌       | ❌           | ❌    |
| Cell-based counting | ❌       | ❌           | ✅    |
| DFS perimeter       | ✅       | ✅           | ✅    |

Both DFS and non-DFS solutions are valid.
DFS is more **conceptually powerful** for graph thinking.
