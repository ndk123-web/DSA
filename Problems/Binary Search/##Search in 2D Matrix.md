# 🔍 Search a 2D Matrix — All Approaches Explained

We are given a matrix with **special properties**:

### Given Matrix Properties

1. Each row is sorted in ascending order
2. The **first element of a row is greater than the last element of the previous row**

That means the matrix is **globally sorted**.

Example:

```
[
  [1,  2,  4,  8],
  [10, 11, 12, 13],
  [14, 20, 30, 40]
]
```

---

## 🎯 Goal

Return `true` if `target` exists in the matrix, otherwise `false`.

---

# 1️⃣ Method 1 — Brute Force (Naive)

### 💡 Idea

- Simply check **every element**
- No use of sorting property

### Code

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (int i = 0 ; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (target == matrix[i][j])
                    return true;
            }
        }
        return false;
    }
};
```

### ⏱️ Complexity

| Metric | Value             |
| ------ | ----------------- |
| Time   | O(ROWS × COLS) ❌ |
| Space  | O(1)              |

### ❌ Why not good?

- Ignores sorted nature
- Too slow for large matrices

---

# 2️⃣ Method 2 — Binary Search on Each Row

### 💡 Idea

- Each row is sorted
- Apply **binary search on every row**

### Code

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int r = matrix.size();
        int c = matrix[0].size();

        for (int i = 0; i < r; i++) {
            int l = 0, h = c - 1;
            while (l <= h) {
                int m = l + (h - l) / 2;
                if (matrix[i][m] < target) {
                    l = m + 1;
                } else if (matrix[i][m] > target) {
                    h = m - 1;
                } else {
                    return true;
                }
            }
        }
        return false;
    }
};
```

### ⏱️ Complexity

| Metric | Value              |
| ------ | ------------------ |
| Time   | O(ROWS × log COLS) |
| Space  | O(1)               |

### ✅ Better, but still not optimal

- Still searching row-by-row
- Doesn’t fully exploit **global ordering**

---

# 3️⃣ Method 3 — Flattened Binary Search (BEST 🔥)

👉 **This is the most important method**
👉 Interviewers LOVE this approach

---

## 🧠 Core Concept (MOST IMPORTANT)

Because of matrix properties:

```
Row sorted
AND
Row[i][0] > Row[i-1][last]
```

👉 The entire matrix behaves like a **sorted 1D array**.

If we flatten it row-wise:

```
[1,2,4,8,10,11,12,13,14,20,30,40]
```

So we can apply **binary search directly**.

---

## 🔑 Index Mapping Logic (Heart of the Solution)

Let:

```
ROWS = matrix.size()
COLS = matrix[0].size()
```

If we imagine a 1D index `mid`:

```
row = mid / COLS
col = mid % COLS
```

This maps 1D index → correct 2D position.

---

## Code (Clean & Optimal)

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int ROWS = matrix.size();
        int COLS = matrix[0].size();

        int left = 0, right = ROWS * COLS - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            int r = mid / COLS;
            int c = mid % COLS;

            if (matrix[r][c] < target) {
                left = mid + 1;
            }
            else if (matrix[r][c] > target) {
                right = mid - 1;
            }
            else {
                return true;
            }
        }
        return false;
    }
};
```

---

## 🧪 Dry Run (Important Example)

### Input

```
matrix = [
  [1,  2,  4,  8],
  [10, 11, 12, 13],
  [14, 20, 30, 40]
]
target = 10
```

```
ROWS = 3, COLS = 4
left = 0, right = 11
```

| mid | row = mid/4 | col = mid%4 | value | action    |
| --- | ----------- | ----------- | ----- | --------- |
| 5   | 1           | 1           | 11    | right = 4 |
| 2   | 0           | 2           | 4     | left = 3  |
| 3   | 0           | 3           | 8     | left = 4  |
| 4   | 1           | 0           | 10    | FOUND ✅  |

---

## ⏱️ Complexity (BEST)

| Metric | Value                  |
| ------ | ---------------------- |
| Time   | O(log(ROWS × COLS)) ✅ |
| Space  | O(1)                   |

Note:

```
log(ROWS × COLS) = log ROWS + log COLS
```

So this is **asymptotically optimal**.

---

## 🧠 One-Line Mental Model (LOCK THIS 🔒)

> **If a 2D matrix is globally sorted, treat it like a 1D sorted array and binary search on indices.**

---

## 🔚 Final Comparison

| Method       | Time        | Uses Sorting Fully? | Recommended |
| ------------ | ----------- | ------------------- | ----------- |
| Brute Force  | O(R×C)      | ❌                  | No          |
| Row-wise BS  | O(R log C)  | Partial             | Sometimes   |
| Flattened BS | O(log(R×C)) | ✅                  | ⭐ BEST ⭐  |

---
