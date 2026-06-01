# 120. Triangle — Memoization / Top-Down DP

## Intuition

We start from the top of the triangle and want the **minimum path sum** till the bottom.

From any cell `(row, col)`:

we have only **2 possible moves**:

* move to same index in next row → `(row+1, col)`
* move to next index in next row → `(row+1, col+1)`

So for every cell:

```text
minimum path from current cell
=
current value
+
minimum of both child paths
```

---

## Example

Triangle:

```text
       2
      3 4
     6 5 7
    4 1 8 3
```

Start from `2`

Possible:

```text
2 -> 3 -> 6 -> 4 = 15
2 -> 3 -> 5 -> 1 = 11
2 -> 4 -> 5 -> 1 = 12
2 -> 4 -> 7 -> 3 = 16
```

Minimum:

```text
11
```

---

# Recursive relation

If we are standing at:

```text
(row, col)
```

then:

```cpp
dfs(row,col)
=
triangle[row][col]
+
min(
    dfs(row+1,col),
    dfs(row+1,col+1)
)
```

---

# Base Case

When we reach last row:

there is nowhere else to move.

So:

```cpp
if(row == triangle.size()-1)
    return triangle[row][col];
```

---

# Why Memoization?

Without memoization:

same cell gets recalculated many times.

Example:

```text
        2
       / \
      3   4
       \ /
        5
```

Cell `5` may be reached from multiple paths.

Without caching:

we solve it repeatedly.

---

With memoization:

store:

```text
dp[row][col]
=
minimum path sum starting from this cell till bottom
```

Then next time:

reuse directly.

---

# Important DP insight

### Why `sum` parameter was removed?

Initially recursive function was:

```cpp
dfs(row, col, sum)
```

Problem:

same `(row,col)` can be reached with different `sum`.

Then memoization breaks because:

```text
(row,col) same
but sum different
```

So cache key becomes invalid.

---

Instead we define:

```text
dfs(row,col)
=
minimum path from this cell to bottom
```

Now answer depends only on:

```text
row + col
```

So memoization works correctly.

---

# Hash for `unordered_map<pair<int,int>>`

`unordered_map` internally needs hash for key.

C++ knows how to hash:

```cpp
int
string
char
```

but not `pair<int,int>`.

So we provide custom hash.

---

## Custom Pair Hash

```cpp
struct pair_hash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};
```

---

### How it works

For pair:

```text
(row,col)
```

we generate:

```text
hash(row) XOR hash(col)
```

which becomes hash key for unordered_map.

---

# Code

```cpp
class Solution {
public:
    struct pair_hash {
        size_t operator()(const pair<int, int>& p) const {
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        }
    };

    unordered_map<pair<int, int>, int, pair_hash> dp;

    int dfs(vector<vector<int>>& triangle, int row, int index) {

        if (row == triangle.size() - 1)
            return triangle[row][index];

        if (dp.count({row, index}))
            return dp[{row, index}];

        return dp[{row, index}] =
            triangle[row][index] +
            min(
                dfs(triangle, row + 1, index),
                dfs(triangle, row + 1, index + 1)
            );
    }

    int minimumTotal(vector<vector<int>>& triangle) {
        return dfs(triangle, 0, 0);
    }
};
```

---

# Complexity Analysis

Let:

```text
n = number of rows
```

Total cells:

```text
1 + 2 + 3 + ... + n
= n(n+1)/2
```

≈

```text
O(n²)
```

---

## Time Complexity

Each cell computed only once.

```text
O(n²)
```

---

## Space Complexity

Memo stores each cell once:

```text
O(n²)
```

Recursion stack:

```text
O(n)
```

Overall:

```text
O(n²)
```

---

# Key Takeaways

### Movement

From `(row,col)`:

```text
↓
(row+1,col)

↘
(row+1,col+1)
```

---

### DP State

```text
dp[row][col]
=
minimum path from this cell till bottom
```

---

### Transition

```text
current value
+
min(left child, right child)
```

---

### Base

```text
last row => return itself
```

---

### Final Answer

```cpp
dfs(0,0)
```

because top of triangle is:

```text
(0,0)
```
