# ✅ Solution 1: DFS (Direct 4 Calls)

## Intuition

A region of `'O'` is **not surrounded** if it is connected (directly or indirectly) to any **border `'O'`**.
So instead of checking each `'O'` locally, we first **protect all `'O'` cells connected to the border**.

Any `'O'` that cannot reach the border must be fully surrounded and should be converted to `'X'`.

---

## Approach

1. Traverse all **border cells** of the board.
2. Whenever a border cell contains `'O'`, run **DFS** from that cell.
3. During DFS:
   - Mark all connected `'O'` cells as `'T'` (temporary safe).

4. After DFS:
   - Convert remaining `'O'` cells to `'X'` (surrounded).
   - Convert `'T'` back to `'O'` (safe).

---

## Complexity

- **Time Complexity:** `O(ROWS × COLS)`
  Each cell is visited at most once.

- **Space Complexity:** `O(ROWS × COLS)`
  Due to recursion stack in worst case.

---

## Code

```cpp
class Solution {
private:
    int ROWS, COLS;

    void dfs(int r, int c, vector<vector<char>>& board) {
        if (r < 0 || c < 0 || r >= ROWS || c >= COLS || board[r][c] != 'O')
            return;

        board[r][c] = 'T';

        dfs(r + 1, c, board);
        dfs(r - 1, c, board);
        dfs(r, c + 1, board);
        dfs(r, c - 1, board);
    }

public:
    void solve(vector<vector<char>>& board) {
        ROWS = board.size();
        COLS = board[0].size();

        // Left and Right borders
        for (int r = 0; r < ROWS; r++) {
            if (board[r][0] == 'O') dfs(r, 0, board);
            if (board[r][COLS - 1] == 'O') dfs(r, COLS - 1, board);
        }

        // Top and Bottom borders
        for (int c = 0; c < COLS; c++) {
            if (board[0][c] == 'O') dfs(0, c, board);
            if (board[ROWS - 1][c] == 'O') dfs(ROWS - 1, c, board);
        }

        // Final conversion
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (board[r][c] == 'O') board[r][c] = 'X';
                else if (board[r][c] == 'T') board[r][c] = 'O';
            }
        }
    }
};
```

---

# ✅ Solution 2: DFS using Directions Array (`dirs`)

## Intuition

The idea remains the same:
**Only border-connected `'O'` cells are safe**.

Using a `dirs` array helps reduce repetitive DFS calls and makes the code cleaner and more scalable.

---

## Approach

1. Define a `dirs` array for 4-directional movement.
2. Start DFS from all border `'O'` cells.
3. Mark all reachable `'O'` cells as `'T'`.
4. Convert:
   - Remaining `'O'` → `'X'`
   - `'T'` → `'O'`

---

## Complexity

- **Time Complexity:** `O(ROWS × COLS)`
- **Space Complexity:** `O(ROWS × COLS)`

---

## Code

```cpp
class Solution {
private:
    int ROWS, COLS;
    vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    void dfs(int r, int c, vector<vector<char>>& board) {
        if (r < 0 || c < 0 || r >= ROWS || c >= COLS || board[r][c] != 'O')
            return;

        board[r][c] = 'T';

        for (auto& d : dirs) {
            dfs(r + d[0], c + d[1], board);
        }
    }

public:
    void solve(vector<vector<char>>& board) {
        ROWS = board.size();
        COLS = board[0].size();

        // Left and Right borders
        for (int r = 0; r < ROWS; r++) {
            if (board[r][0] == 'O') dfs(r, 0, board);
            if (board[r][COLS - 1] == 'O') dfs(r, COLS - 1, board);
        }

        // Top and Bottom borders
        for (int c = 0; c < COLS; c++) {
            if (board[0][c] == 'O') dfs(0, c, board);
            if (board[ROWS - 1][c] == 'O') dfs(ROWS - 1, c, board);
        }

        // Final conversion
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (board[r][c] == 'O') board[r][c] = 'X';
                else if (board[r][c] == 'T') board[r][c] = 'O';
            }
        }
    }
};
```

---

## 🧠 Final One-Line Insight

> **Surrounded means disconnected from the border, not just inside the board.**
