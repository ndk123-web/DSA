# Interleaving String

## Intuition

The problem asks whether a third string `s3` can be formed by interleaving two strings `s1` and `s2` while preserving the order of characters in both strings.

At each step, we have two choices:

- Take a character from `s1`
- Take a character from `s2`

However, the chosen character must match the current character in `s3`.

A key observation:
If we have used `i` characters from `s1` and `j` characters from `s2`, then we must have formed `i + j` characters in `s3`.

So:

```text
k = i + j
```

This removes the need to track `k` separately.

---

## Approach

### Top-Down (Recursion + Memoization)

We define a recursive function:

```text
dfs(i, j)
```

Meaning:
Can we form `s3[i+j:]` using `s1[i:]` and `s2[j:]`?

---

### Base Case

```text
if i == n1 and j == n2 → return true
```

All characters are used successfully.

---

### Transition

At each state `(i, j)`:

```text
k = i + j
```

- If `s1[i] == s3[k]`, we can take from `s1`
- If `s2[j] == s3[k]`, we can take from `s2`

```text
dfs(i, j) =
    (s1[i] == s3[k] AND dfs(i+1, j))
 OR (s2[j] == s3[k] AND dfs(i, j+1))
```

---

### Memoization

We store results for `(i, j)` using a map to avoid recomputation.

---

### Code (Top-Down using map)

```cpp
class Solution {
private:
    map<pair<int,int>, bool> memo;

    bool dfs(string& s1, string& s2, string& s3, int i, int j) {
        if (i == s1.size() && j == s2.size()) return true;

        if (memo.find({i, j}) != memo.end()) {
            return memo[{i, j}];
        }

        int k = i + j;

        bool res = false;

        if (i < s1.size() && s1[i] == s3[k]) {
            res |= dfs(s1, s2, s3, i + 1, j);
        }

        if (j < s2.size() && s2[j] == s3[k]) {
            res |= dfs(s1, s2, s3, i, j + 1);
        }

        return memo[{i, j}] = res;
    }

public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size()) return false;
        return dfs(s1, s2, s3, 0, 0);
    }
};
```

---

## Bottom-Up (Tabulation)

We define a DP table:

```text
dp[i][j]
```

Meaning:
Can `s1[i:]` and `s2[j:]` form `s3[i+j:]`?

---

### Base Case

```text
dp[n1][n2] = true
```

Both strings are fully used.

---

### Last Row (i = n1)

Only `s2` remains:

```text
dp[n1][j] = (s2[j] == s3[n1 + j]) AND dp[n1][j+1]
```

---

### Last Column (j = n2)

Only `s1` remains:

```text
dp[i][n2] = (s1[i] == s3[i + n2]) AND dp[i+1][n2]
```

---

### Transition

For remaining cells:

```text
k = i + j

dp[i][j] =
    (s1[i] == s3[k] AND dp[i+1][j])
 OR (s2[j] == s3[k] AND dp[i][j+1])
```

---

### Code (Bottom-Up)

```cpp
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size();

        if (n1 + n2 != s3.size()) return false;

        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));

        dp[n1][n2] = true;

        for (int j = n2 - 1; j >= 0; j--) {
            dp[n1][j] = (s2[j] == s3[n1 + j]) && dp[n1][j + 1];
        }

        for (int i = n1 - 1; i >= 0; i--) {
            dp[i][n2] = (s1[i] == s3[i + n2]) && dp[i + 1][n2];
        }

        for (int i = n1 - 1; i >= 0; i--) {
            for (int j = n2 - 1; j >= 0; j--) {

                int k = i + j;

                bool takeS1 = (s1[i] == s3[k]) && dp[i + 1][j];
                bool takeS2 = (s2[j] == s3[k]) && dp[i][j + 1];

                dp[i][j] = takeS1 || takeS2;
            }
        }

        return dp[0][0];
    }
};
```

---

## Complexity

### Time Complexity

```text
O(n1 * n2)
```

Each state `(i, j)` is computed once.

---

### Space Complexity

```text
O(n1 * n2)
```

DP table size.

---

## Key Insight

- The state is fully defined by `(i, j)`
- The index in `s3` is derived: `k = i + j`
- The problem reduces to checking if a valid path exists in a grid
- Each cell depends on future states (down or right)

This is a classic 2D DP problem based on string matching and state transitions.
