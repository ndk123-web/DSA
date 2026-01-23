# 🔍 Word Search (Backtracking)

## 📌 Problem Statement

Given a 2D board of characters and a string `word`, return `true` if the word exists in the grid.

The word must be constructed from **sequentially adjacent cells**, where:

- Adjacent cells are horizontally or vertically neighboring
- The same cell **cannot be used more than once**

---

## 🔍 Key Observations

- Each character of the word must match a cell in the board.
- From any cell, we can move in **4 directions**: up, down, left, right.
- Once a cell is used in the current path, it cannot be reused.
- This is a classic **DFS + backtracking** problem on a grid.

---

## 🧠 Core Idea

We try to **start the word from every cell** in the board.

For each starting cell:

- Use DFS to check if the word can be formed
- Match characters one by one
- Mark visited cells temporarily
- Backtrack when the path fails

---

## 🛠️ Backtracking Strategy

We maintain:

- `(r, c)` → current cell position
- `idx` → current index in the word

At each step:

1. Check boundaries and validity
2. Match `board[r][c]` with `word[idx]`
3. Temporarily mark the cell as visited
4. Explore all 4 directions
5. Restore the cell (backtrack)

---

## 💻 Code (LeetCode Accepted)

```cpp
class Solution {
private:
    vector<vector<char>> board;
    string word;

    bool backtrack(int r, int c, int idx) {
        // all characters matched
        if (idx == word.size())
            return true;

        // invalid state
        if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size() ||
            board[r][c] == '#' || board[r][c] != word[idx])
            return false;

        // mark as visited
        board[r][c] = '#';

        bool res = backtrack(r + 1, c, idx + 1) ||
                   backtrack(r - 1, c, idx + 1) ||
                   backtrack(r, c + 1, idx + 1) ||
                   backtrack(r, c - 1, idx + 1);

        // restore cell (backtrack)
        board[r][c] = word[idx];

        return res;
    }

    bool helper(int row, int col) {
        int i = 0, j = 0;

        while (i < row) {
            if (j >= col) {
                i++;
                j = 0;
            }
            if (backtrack(i, j, 0)) {
                return true;
            }
            j++;
        }
        return false;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        int row = board.size();
        int col = board[0].size();

        this->board = board;
        this->word = word;

        return helper(row, col);
    }
};
```

---

## 🧠 Why This Works

- Every possible starting position is tried.
- DFS explores all valid paths.
- Invalid paths are **cut early** using checks.
- Backtracking ensures the board state is restored after each attempt.

---

## 🧠 Example

### Input

```
board = [
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED"
```

### Output

```
true
```

---

## ⏱️ Time Complexity

- **O(R × C × 4^L)**
  where:
  - `R × C` = number of cells
  - `L` = length of the word

Worst case: we explore all directions for each character.

---

## 📦 Space Complexity

- **O(L)** recursion stack (depth = word length)
- No extra visited array (board modified in-place)

---

## 🧠 Important Insight

> We do **not** generate all paths blindly.
> We stop immediately when:
>
> - characters don’t match
> - cell is already used
> - boundaries are crossed

This pruning makes the solution efficient.

---

## 🔑 Interview One-Liner

> “We perform DFS from each cell, matching characters sequentially and using backtracking to mark and restore visited cells.”

---

## 🔄 Pattern Recognition

This problem follows the **Grid DFS + Backtracking** pattern.

Same pattern appears in:

- Word Search II
- Flood Fill
- Number of Islands
- Maze problems
