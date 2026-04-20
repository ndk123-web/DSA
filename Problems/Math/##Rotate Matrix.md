# Rotate Image (90° Clockwise)

## Intuition

Rotating a matrix by 90° clockwise can be broken into two simpler operations:

1. Transpose the matrix (convert rows into columns)
2. Reverse each row

Why this works:

* Transpose flips the matrix over its main diagonal
* Reversing each row shifts elements to their correct rotated positions

This avoids using extra space and achieves the rotation in-place.

---

## Reasoning

### Step 1: Transpose

Transpose converts:

```
matrix[i][j] → matrix[j][i]
```

Example:

```
Original:
1 2 3
4 5 6
7 8 9

After Transpose:
1 4 7
2 5 8
3 6 9
```

We only swap elements in the **upper triangle (j >= i)** to avoid double swapping.

---

### Step 2: Reverse Each Row

After transpose, reversing each row gives the final rotated matrix:

```
Before reverse:
1 4 7
2 5 8
3 6 9

After reverse:
7 4 1
8 5 2
9 6 3
```

This is exactly a 90° clockwise rotation.

---

## Logic

1. Traverse upper triangle of matrix

   * Swap `matrix[i][j]` with `matrix[j][i]`
2. For each row:

   * Reverse the row

---

## Approach

### Steps

* Transpose the matrix in-place
* Reverse each row

---

## Code

```cpp id="f2g0np"
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {

        int r = matrix.size();
        int c = matrix[0].size();

        // Step 1: transpose matrix (swap across diagonal)
        for (int i = 0; i < r; i++) {
            for (int j = i; j < c; j++)
                swap(matrix[i][j], matrix[j][i]);
        }

        // Step 2: reverse each row
        for (int i = 0; i < r; i++)
            reverse(matrix[i].begin(), matrix[i].end());
    }
};
```

---

## Complexity Analysis

* Time Complexity: O(n²)
  Each element is visited once during transpose and once during reversal.

* Space Complexity: O(1)
  In-place transformation, no extra space used.

---

## Key Insight

* Transpose changes orientation (rows ↔ columns)
* Row reversal aligns elements to simulate rotation
* Combining both operations results in 90° clockwise rotation

---

## Notes

* This approach works only for square matrices (n × n)
* Using full matrix traversal for transpose causes double swaps; restricting to upper triangle avoids that
* This is the most optimal and standard interview solution