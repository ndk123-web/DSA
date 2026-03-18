# Intuition

We are given two strings `text1` and `text2`. The goal is to find the **length of the longest subsequence** that exists in both strings.

A subsequence maintains order but can skip characters.

Key observation:

- At any position `(i, j)`:
  - If characters match → we **include it**
  - If not → we **skip one of them**

This leads to a classic **2D Dynamic Programming** problem.

---

# Approach 1: Top-Down (Recursion + Memoization)

## Idea

Define:

```text
dp[i][j] = LCS length of text1[i:] and text2[j:]
```

### Case 1: Characters match

```text
text1[i] == text2[j]
```

We include the character and move both pointers:

```text
dp[i][j] = 1 + dp[i+1][j+1]
```

---

### Case 2: Characters do not match

We try both possibilities:

```text
dp[i][j] = max(
    dp[i+1][j],   // skip text1[i]
    dp[i][j+1]    // skip text2[j]
)
```

---

## Code

```cpp
class Solution {
private:
    vector<vector<int>> dp;

    int dfs(string &a, string &b, int i, int j) {

        if (i == a.size() || j == b.size())
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (a[i] == b[j]) {
            return dp[i][j] = 1 + dfs(a, b, i+1, j+1);
        }

        return dp[i][j] = max(
            dfs(a, b, i+1, j),
            dfs(a, b, i, j+1)
        );
    }

public:
    int longestCommonSubsequence(string text1, string text2) {

        int m = text1.size();
        int n = text2.size();

        dp = vector<vector<int>>(m, vector<int>(n, -1));

        return dfs(text1, text2, 0, 0);
    }
};
```

---

## Complexity

- **Time Complexity:**

```text
O(m × n)
```

- **Space Complexity:**

```text
O(m × n) + recursion stack
```

---

# Approach 2: Bottom-Up (Tabulation)

## Idea

We build the solution iteratively.

Define:

```text
dp[i][j] = LCS length of text1[i:] and text2[j:]
```

We use a table of size `(m+1) x (n+1)`.

---

## Base Case

```text
dp[m][j] = 0
dp[i][n] = 0
```

If any string ends → LCS = 0

---

## Transition

### Case 1: Match

```text
if text1[i] == text2[j]
    dp[i][j] = 1 + dp[i+1][j+1]
```

---

### Case 2: Mismatch

```text
dp[i][j] = max(
    dp[i+1][j],   // skip from text1
    dp[i][j+1]    // skip from text2
)
```

---

## Filling Order

Since we depend on:

```text
dp[i+1][j], dp[i][j+1], dp[i+1][j+1]
```

We fill:

```text
from bottom-right → top-left
```

---

## Code

```cpp
class Solution {
public:
    int longestCommonSubsequence(string a, string b) {

        int m = a.size();
        int n = b.size();

        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {

                if (a[i] == b[j]) {
                    dp[i][j] = 1 + dp[i+1][j+1];
                }
                else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
                }
            }
        }

        return dp[0][0];
    }
};
```

---

## Complexity

- **Time Complexity:**

```text
O(m × n)
```

- **Space Complexity:**

```text
O(m × n)
```

---

# Key Concepts

### State Definition

```text
dp[i][j] = best LCS from index (i,j)
```

---

### Transitions

| Case     | Meaning                        |
| -------- | ------------------------------ |
| Match    | Take character → move diagonal |
| Mismatch | Skip one → take max            |

---

### Movement Interpretation

- **Diagonal (i+1, j+1)** → both characters used
- **Down (i+1, j)** → skip from text1
- **Right (i, j+1)** → skip from text2

---

# Summary

This problem follows a core DP pattern:

```text
2 strings + subsequence → branching decision DP
```

Core logic:

```text
Match → take both
Mismatch → try skipping both sides → take best
```
