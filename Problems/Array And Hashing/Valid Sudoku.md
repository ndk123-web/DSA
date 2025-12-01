---

# **Valid Sudoku — C++ Solution (Row, Column, 3×3 Checks)**

This solution validates whether a given **9×9 Sudoku board** is valid according to:

1. Each row must contain digits **1–9** without repetition
2. Each column must contain digits **1–9** without repetition
3. Each 3×3 subgrid must contain digits **1–9** without repetition
4. Empty cells are denoted with `'.'`

---

# ## **Approach Summary**

We validate the Sudoku board in **3 phases**:

### ✔ 1. Check all **rows**

- For each row, use an unordered set
- Insert digits as they appear
- If a digit repeats → return `false`

---

### ✔ 2. Check all **columns**

- For each column, use a new unordered set
- Insert digits top-to-bottom
- If a digit repeats → return `false`

---

### ✔ 3. Check all **3×3 subgrids**

We iterate each subgrid using:

```
(r1,c1) → top-left corner
(r2,c2) → bottom-right corner (always +2)
```

Cycle pattern:

```
(0,0)  (0,3)  (0,6)
(3,0)  (3,3)  (3,6)
(6,0)  (6,3)  (6,6)
```

Each subgrid gets its own set.
If a duplicate digit appears inside a subgrid → return `false`.

---

# ## **C++ Code (with short clean comments)**

```cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {

        unordered_set<char> sett;
        int row = board.size();
        int col = board[0].size();


        // 1) Check each row
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (board[i][j] == '.') continue;
                if (sett.count(board[i][j])) return false;
                sett.insert(board[i][j]);
            }
            sett.clear();
        }

        // 2) Check each column
        for (int i = 0; i < col; i++) {
            for (int j = 0; j < row; j++) {
                if (board[j][i] == '.') continue;
                if (sett.count(board[j][i])) return false;
                sett.insert(board[j][i]);
            }
            sett.clear();
        }

        // 3) Check each 3×3 subgrid
        int increment = 3;
        int blockRowCount = 3;
        int r1 = 0, c1 = 0, r2 = 2, c2 = 2;

        for (int block = 0; block < 9; block++) {
            unordered_set<char> tSet;

            // scan inside this 3×3 block
            for (int r = r1; r <= r2; r++) {
                for (int c = c1; c <= c2; c++) {
                    if (board[r][c] == '.') continue;
                    if (tSet.count(board[r][c])) return false;
                    tSet.insert(board[r][c]);
                }
            }

            blockRowCount--;

            // Move to next row of blocks after 3
            if (blockRowCount == 0) {
                r1 += increment;
                r2 += increment;
                blockRowCount = 3;
                c1 = 0;
                c2 = 2;
                continue;
            }

            // Move to next block in same row
            c1 += increment;
            c2 += increment;
        }

        return true;
    }
};
```

---

# ## **Example**

Input board:

```
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  ["." ,"9","8",".",".",".",".","6","."],
  ...
]
```

Output:

```
true
```

---

# ## **Time & Space Complexity**

| Step            | Complexity                             |
| --------------- | -------------------------------------- |
| Row checks      | O(9×9)                                 |
| Column checks   | O(9×9)                                 |
| Subgrid checks  | O(9×9)                                 |
| **Total Time**  | **O(81)** = O(1) (constant board size) |
| **Extra Space** | O(9) per set                           |

Sudoku board is fixed size, so algorithm is effectively **constant time**.

---

# ## **Summary**

This solution ensures:

- No duplicate digits in any row
- No duplicate digits in any column
- No duplicate digits in any 3×3 subgrid

If any rule breaks → function returns `false`,
otherwise returns `true`.

---
