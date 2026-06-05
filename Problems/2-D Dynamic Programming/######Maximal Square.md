# 221. Maximal Square

## Intuition

We are given a binary matrix containing:

```text
'0'
'1'
```

We need to find the **largest square consisting only of 1s** and return its **area**.

---

## First Thought (Brute Force)

For every cell:

```text
Try making a square
Check if all cells are 1
Expand further
```

This works but becomes expensive because every square needs to be validated repeatedly.

---

## Key Observation

Suppose we are at cell:

```text
(i,j)
```

and:

```text
matrix[i][j] = '1'
```

Can this cell become the bottom-right corner of a larger square?

---

Consider:

```text
1 1
1 1
```

At the bottom-right cell, a 2×2 square exists.

Why?

Because:

```text
Top      supports a square
Left     supports a square
Diagonal supports a square
Current cell is 1
```

---

Now consider:

```text
1 1
1 0
```

Even though:

```text
top = 1
left = 1
diagonal = 1
```

Current cell:

```text
0
```

So no square can end here.

---

Therefore:

```text
A square can only be formed if the current cell is 1.
```

---

# DP Definition

Let:

```text
dp[i][j]
```

represent:

```text
Side length of the largest square
whose bottom-right corner is (i,j)
```

---

Example:

```text
1 1
1 1
```

DP:

```text
1 1
1 2
```

The bottom-right cell can form a:

```text
2 × 2 square
```

---

# Why Minimum?

Suppose:

```text
top      = 3
left     = 3
diagonal = 1
```

Visualize:

```text
? ? ? ?
? ? ? ?
? ? ? ?
? X ? ?
```

Even though:

```text
top = 3
left = 3
```

the diagonal only supports a:

```text
1 × 1
```

square.

Therefore we cannot extend beyond:

```text
2 × 2
```

---

Similarly:

```text
top      = 5
left     = 2
diagonal = 5
```

The left side is the bottleneck.

The largest square is determined by the **smallest supporting square**.

Therefore:

```text
dp[i][j]
=
1 + min(
    top,
    left,
    diagonal
)
```

---

# Recurrence

If:

```text
matrix[i][j] == '0'
```

then:

```text
dp[i][j] = 0
```

because no square can end at a zero.

---

If:

```text
matrix[i][j] == '1'
```

then:

```text
dp[i][j]
=
1 + min(
    dp[i-1][j],
    dp[i][j-1],
    dp[i-1][j-1]
)
```

---

# Dry Run

Matrix:

```text
1 1
1 1
```

Initialize:

```text
1 1
1 1
```

---

At:

```text
(1,1)
```

we have:

```text
top      = 1
left     = 1
diagonal = 1
```

Therefore:

```text
dp[1][1]
=
1 + min(1,1,1)
=
2
```

DP:

```text
1 1
1 2
```

Largest side:

```text
2
```

Area:

```text
2 × 2 = 4
```

---

# Code

```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {

        int m = matrix.size();
        int n = matrix[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));

        int maxSide = 0;

        for (int i = 0; i < m; i++) {
            dp[i][0] = matrix[i][0] - '0';
            maxSide = max(maxSide, dp[i][0]);
        }

        for (int j = 0; j < n; j++) {
            dp[0][j] = matrix[0][j] - '0';
            maxSide = max(maxSide, dp[0][j]);
        }

        for (int i = 1; i < m; i++) {

            for (int j = 1; j < n; j++) {

                if (matrix[i][j] == '1') {

                    dp[i][j] =
                        min({
                            dp[i - 1][j],
                            dp[i][j - 1],
                            dp[i - 1][j - 1]
                        }) + 1;

                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }

        return maxSide * maxSide;
    }
};
```

---

# Correctness Proof

### Lemma 1

If:

```text
matrix[i][j] = 0
```

then no square can end at `(i,j)`.

Therefore:

```text
dp[i][j] = 0
```

is correct.

---

### Lemma 2

If:

```text
matrix[i][j] = 1
```

then the largest square ending at `(i,j)` can only extend as far as the smallest square among:

```text
top
left
diagonal
```

Otherwise one side of the square would be missing.

---

### Lemma 3

Adding the current cell extends that square by:

```text
1
```

Therefore:

```text
dp[i][j]
=
1 + min(top,left,diagonal)
```

correctly computes the largest square ending at `(i,j)`.

---

### Theorem

The maximum value present in the DP table represents the side length of the largest valid square.

Therefore:

```text
answer = side²
```

is correct.

---

# Complexity

### Time

```text
O(m × n)
```

Each cell is processed once.

---

### Space

```text
O(m × n)
```

for the DP table.

---

# Pattern Recognition

When you see:

```text
Largest square
Largest rectangle
Expand from neighbors
```

think:

```text
DP on Grid
```

and ask:

```text
Can I define
dp[i][j]
as the answer ending at this cell?
```
