# ♛ N-Queens

## 📌 Problem Statement

Given an integer `n`, return all distinct solutions to the **n-queens puzzle**.

Each solution contains a distinct board configuration of the `n` queens’ placement, where no two queens attack each other.

A queen can attack another queen if they share the same:

- Row
- Column
- Diagonal

---

## 🧠 Intuition

- We place **one queen per row**.
- For each row, we try all possible columns.
- Before placing a queen, we ensure it does not conflict with any previously placed queens.
- If a valid placement is found for all rows, we record the board configuration.

This is a classic **backtracking** problem.

---

## 🛠️ Approach

### 1. Board Representation

- The board is represented as a `vector<string>`.
- `'.'` represents an empty cell.
- `'Q'` represents a queen.

---

### 2. Safety Check (`isSafe`)

Before placing a queen at `(row, col)`, we check:

- **Same column above**
- **Upper-left diagonal**
- **Upper-right diagonal**

Only upward directions are checked because queens are placed **row by row from top to bottom**.

---

### 3. Backtracking (`putQueen`)

- Start from row `0`.
- Try placing a queen in every column of the current row.
- If placement is safe:
  - Place the queen
  - Recurse to the next row
  - Backtrack (remove the queen)

- When `row == n`, a valid configuration is found and added to the result.

---

## 💻 Code

```cpp
class Solution {
private:
    vector<vector<string>> res;

    bool isSafe(vector<string>& board, int row, int col) {
        int duprow = row, dupcol = col;

        // check same column
        while (row >= 0) {
            if (board[row][col] == 'Q') return false;
            row--;
        }

        // check upper-left diagonal
        row = duprow;
        col = dupcol;
        while (row >= 0 && col >= 0) {
            if (board[row][col] == 'Q') return false;
            row--;
            col--;
        }

        // check upper-right diagonal
        row = duprow;
        col = dupcol;
        while (row >= 0 && col < board[0].size()) {
            if (board[row][col] == 'Q') return false;
            row--;
            col++;
        }

        return true;
    }

    void putQueen(vector<string>& board, int row) {
        if (row == board.size()) {
            res.push_back(board);
            return;
        }

        for (int col = 0; col < board[0].size(); col++) {
            if (isSafe(board, row, col)) {
                board[row][col] = 'Q';
                putQueen(board, row + 1);
                board[row][col] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board;
        for (int i = 0; i < n; i++) {
            board.push_back(string(n, '.'));
        }

        putQueen(board, 0);
        return res;
    }
};
```

---

## ⏱️ Time Complexity

- **Worst case:** `O(N!)`
- For each row, we try all columns and backtrack on conflicts.

---

## 📦 Space Complexity

- **O(N²)** for storing board configurations
- **O(N)** recursion stack depth

---

## 🔑 Key Insights

- We only check **upward directions** because queens are placed row by row.
- Backtracking allows us to explore all valid configurations efficiently.
- Although a single board is reused during recursion, each valid configuration is **copied** into the result list.

---

## 🎯 Interview One-Liner

> “We place queens row by row using backtracking, ensuring no two queens attack each other by checking columns and diagonals.”
