# Range Sum Query 2D — Two Solutions
---

## Problem Summary

We are given a 2D matrix and must support multiple queries:

```
sumRegion(row1, col1, row2, col2)
```

which returns the sum of the rectangle inside the matrix with:

* top-left corner → (row1, col1)
* bottom-right corner → (row2, col2)

The critical requirement:

```
sumRegion must work in O(1) time.
```

---

# Solution 1 — Prefix Sum Matrix (Optimal, O(1) per query)

## Idea

We precompute a prefix sum matrix of size `(rows + 1) × (cols + 1)` such that:

```
prefix[r][c] = sum of elements inside rectangle from (0,0) to (r−1,c−1)
```

This allows retrieving any rectangle's sum in constant time using the inclusion–exclusion formula:

```
sum = prefix[r2][c2]
    - prefix[r1−1][c2]
    - prefix[r2][c1−1]
    + prefix[r1−1][c1−1]
```

---

## Code

```cpp
class NumMatrix {
private:
    vector<vector<int>> prefixSum;

public:
    NumMatrix(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        // prefixSum has an extra row and column (0th row/col = 0)
        prefixSum = vector<vector<int>>(rows + 1, vector<int>(cols + 1, 0));

        // Build prefix sum matrix
        for (int r = 1; r <= rows; r++) {
            for (int c = 1; c <= cols; c++) {
                prefixSum[r][c] = matrix[r - 1][c - 1]
                                + prefixSum[r - 1][c]
                                + prefixSum[r][c - 1]
                                - prefixSum[r - 1][c - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        row1++;
        col1++;
        row2++;
        col2++;

        return prefixSum[row2][col2]
             - prefixSum[row1 - 1][col2]
             - prefixSum[row2][col1 - 1]
             + prefixSum[row1 - 1][col1 - 1];
    }
};
```

---

## Time and Space Complexity

* Prefix sum preprocessing: **O(m × n)**
* Query time: **O(1)**
* Extra space: **O(m × n)** for prefix matrix

### Why this works

The rectangle sum can be decomposed using inclusion–exclusion. The prefix matrix stores the cumulative sum up to each cell, allowing any region's sum to be computed from four prefix values.

---

# Solution 2 — Brute Force (O(n²) per query) — TLE

## Idea

For each query, simply iterate through the rectangle and accumulate the values. This is straightforward but too slow for large inputs or repeated queries.

---

## Code

```cpp
class NumMatrix {
public:
    vector<vector<int>> matrix;

    NumMatrix(vector<vector<int>>& matrix) {
        this->matrix = matrix;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;

        for (int r = row1; r <= row2; r++) {
            for (int c = col1; c <= col2; c++) {
                sum += matrix[r][c];
            }
        }
        return sum; 
    }
};
```

---

## Time and Space Complexity

* Query time: **O((row2−row1+1) × (col2−col1+1))** → worst case O(n²)
* Preprocessing: none
* Space: O(1)

### Why this fails

The problem allows up to **10,000 queries**, and the rectangle may be large. Worst case: 40,000 operations per query × 10,000 calls → TLE.

---

# Summary

| Approach    | Preprocessing | Query Time | Space  | Notes                      |
| ----------- | ------------- | ---------- | ------ | -------------------------- |
| Prefix Sum  | O(m×n)        | **O(1)**   | O(m×n) | Best and required solution |
| Brute Force | O(1)          | **O(n²)**  | O(1)   | Too slow for constraints   |

The prefix sum matrix is the only method that satisfies the O(1) query requirement.

---
