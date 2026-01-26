# ♛ N-Queens II

## 📌 Problem Statement

Given an integer `n`, return the **number of distinct solutions** to the **n-queens puzzle**.

A queen can attack another queen if they share the same:

- Row
- Column
- Diagonal

Unlike **N-Queens I**, here we only need to **count** the valid arrangements, not return the boards.

---

## 🧠 Intuition

- Place **one queen per row**.
- For each row, try placing a queen in every column.
- Before placing, ensure the position is **safe**.
- If a valid placement is found for all rows, increment the count.

This is a classic **backtracking** problem.

---

## 🛠️ Approach

### 1. Board Representation

- Use a `vector<string>` to represent the chessboard.
- `'.'` → empty cell
- `'Q'` → queen

---

### 2. Safety Check (`isSafe`)

Before placing a queen at `(row, col)`, check:

- **Same column above**
- **Upper-left diagonal**
- **Upper-right diagonal**

Only **upward directions** are checked because queens are placed **row by row from top to bottom**.

---

### 3. Backtracking (`putQueen`)

- Start placing queens from row `0`.
- For each row:
  - Try all columns.
  - If safe:
    - Place queen
    - Recurse to next row
    - Backtrack (remove queen)

- When `row == n`, one valid configuration is found → increment count.

---

## 💻 Code

```cpp
class Solution {
private:
    int cnt = 0;

    bool isSafe(vector<string>& board, int row, int col) {
        int dr = row, dc = col;

        // check same column
        while (row >= 0) {
            if (board[row][col] == 'Q') return false;
            row--;
        }

        // check upper-left diagonal
        row = dr;
        col = dc;
        while (row >= 0 && col >= 0) {
            if (board[row][col] == 'Q') return false;
            row--;
            col--;
        }

        // check upper-right diagonal
        row = dr;
        col = dc;
        while (row >= 0 && col < board[0].size()) {
            if (board[row][col] == 'Q') return false;
            row--;
            col++;
        }

        return true;
    }

    void putQueen(vector<string>& board, int row) {
        if (row == board.size()) {
            cnt++;
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
    int totalNQueens(int n) {
        vector<string> board;
        for (int i = 0; i < n; i++) {
            board.push_back(string(n, '.'));
        }

        putQueen(board, 0);
        return cnt;
    }
};
```

---

## ⏱️ Time Complexity

- **Worst-case:** `O(N!)`
- Each row tries up to `N` columns, and backtracking prunes invalid paths early.

---

## 📦 Space Complexity

- **Board storage:** `O(N²)`
- **Recursion stack:** `O(N)`

---

## 🔑 Key Insights

- We only check **upward directions** for safety.
- The same board is reused during recursion, but we **backtrack** after each attempt.
- Counting solutions is simpler than storing them.

---

## 🎯 Interview One-Liner

> “We place queens row by row using backtracking and count valid configurations by checking column and diagonal conflicts.”
