# 📘 Rotting Fruit (LeetCode 994 – Rotting Oranges)

---

## 🧠 Problem Intuition

You are given a 2D grid where:

- `0` → empty cell
- `1` → fresh fruit
- `2` → rotten fruit

Every **minute**, any fresh fruit that is **adjacent (up, down, left, right)** to a rotten fruit becomes rotten.

### Goal

Return the **minimum number of minutes** required so that **no fresh fruit remains**.
If it is **impossible**, return `-1`.

---

## 🔑 Key Insight

This is a **shortest time / minimum steps** problem on a grid.

Important observations:

- Rotting spreads **simultaneously** from all rotten fruits.
- Time progresses in **layers** (minutes).
- This is a classic **Multi-Source BFS** problem.

👉 Each BFS **level = 1 minute**.

---

## 🧩 Approach (Multi-Source BFS)

1. Traverse the grid:
   - Push all rotten fruits (`2`) into a queue.
   - Count total fresh fruits (`1`).

2. Perform BFS:
   - Each BFS level represents **one minute**.
   - From all currently rotten fruits, rot adjacent fresh fruits.

3. Decrease the fresh count whenever a fruit rots.
4. Stop BFS when:
   - No fresh fruits remain, or
   - BFS finishes but fresh fruits are still left.

---

## 🛠️ Algorithm

1. Initialize a queue with all rotten fruits.
2. Count fresh fruits.
3. While the queue is not empty **and** fresh fruits exist:
   - Process the current queue size (one minute).
   - For each rotten fruit:
     - Check all 4 directions.
     - If a neighbor is fresh:
       - Mark it rotten.
       - Decrease fresh count.
       - Add it to the queue.

4. After BFS:
   - If `fresh == 0` → return minutes
   - Else → return `-1`

---

## ✅ Code Implementation

```cpp
class Solution {
private:
    queue<pair<int,int>> q;
    int fresh;
    int ROWS, COLS;

public:
    int orangesRotting(vector<vector<int>>& grid) {
        ROWS = grid.size();
        COLS = grid[0].size();
        fresh = 0;

        // Initialize queue with all rotten fruits
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }

        int minutes = 0;
        vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        // Multi-source BFS
        while (!q.empty() && fresh > 0) {
            int size = q.size();
            minutes++;

            for (int i = 0; i < size; i++) {
                auto [r, c] = q.front();
                q.pop();

                for (auto& d : dirs) {
                    int nr = r + d[0];
                    int nc = c + d[1];

                    if (nr < 0 || nc < 0 || nr >= ROWS || nc >= COLS || grid[nr][nc] != 1)
                        continue;

                    grid[nr][nc] = 2;
                    fresh--;
                    q.push({nr, nc});
                }
            }
        }

        return fresh == 0 ? minutes : -1;
    }
};
```

---

## 🧪 Example Walkthrough

### Input

```
grid = [
  [1,1,0],
  [0,1,1],
  [0,1,2]
]
```

### Process

- Minute 0: rotten at (2,2)
- Minute 1: adjacent fresh rot
- Minute 2–4: rotting spreads layer by layer

### Output

```
4
```

---

## ⏱️ Complexity Analysis

### Time Complexity

```
O(ROWS × COLS)
```

Each cell is processed at most once.

### Space Complexity

```
O(ROWS × COLS)
```

Queue can store all cells in the worst case.

---

## 🔒 Key Takeaways

- This is **not DFS**, because we need the **shortest time**
- BFS naturally handles **minimum distance / time**
- Multiple starting points → **Multi-Source BFS**
- Time is counted by **levels**, not nodes

---

## 🧠 One-Line Lock

> **In grid problems where change spreads over time,
> BFS levels represent time.**
