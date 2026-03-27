# Distinct Subsequences

## Intuition

We are given two strings `s` and `t`. The goal is to count how many distinct subsequences of `s` equal `t`.

At any position:

- We try to match characters of `t` using characters from `s`
- For each character in `s`, we have two choices:
  - **Take it** (if it matches current character in `t`)
  - **Skip it**

This naturally leads to a **decision tree**, which can be optimized using **Dynamic Programming**.

---

# Approach 1: Top-Down DP (Recursion + Memoization)

## Idea

Define:

```text
dfs(i, j) = number of ways to form t[j:] from s[i:]
```

---

## Transition

- If characters match:

```text
take + skip
```

- If not:

```text
skip only
```

---

## Base Cases

- If `j == t.size()` → matched entire `t` → return 1
- If `i == s.size()` → `s` exhausted → return 0

---

## Code

```cpp
class Solution {
private:
    vector<vector<long long>> memo;

    int dfs(const string& s,const string& t, int i, int j) {
        if (j >= t.size()) return 1;
        if (i >= s.size()) return 0;

        if (memo[i][j] != -1) return memo[i][j];

        long long cnt = 0;

        if (s[i] == t[j]) {
            cnt += dfs(s, t, i + 1, j + 1);
        }

        cnt += dfs(s, t, i + 1, j);

        return memo[i][j] = cnt;
    }

public:
    int numDistinct(string s, string t) {
        memo.assign(s.size(), vector<long long>(t.size(), -1));
        return dfs(s, t, 0, 0);
    }
};
```

---

## Complexity

- Time: $$O(n \times m)$$
- Space: $$O(n \times m)$$ (memo + recursion stack)

---

# Approach 2: Bottom-Up DP (2D Table)

## Idea

Convert recursion into tabulation.

Define:

```text
dp[i][j] = number of ways to form t[j:] from s[i:]
```

---

## Base Case

```text
dp[i][m] = 1  (empty t)
dp[n][j] = 0  (s exhausted but t not)
```

---

## Transition

```text
if s[i] == t[j]:
    dp[i][j] = dp[i+1][j+1] + dp[i+1][j]
else:
    dp[i][j] = dp[i+1][j]
```

---

## Code

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        int r = s.size();
        int c = t.size();

        vector<vector<unsigned long long>> dp(r + 1, vector<unsigned long long>(c + 1, 0));

        for (int i = 0; i <= r; i++) {
            dp[i][c] = 1;
        }

        for (int i = r - 1; i >= 0; i--) {
            for (int j = c - 1; j >= 0; j--) {
                if (s[i] == t[j]) {
                    dp[i][j] = dp[i+1][j+1] + dp[i+1][j];
                } else {
                    dp[i][j] = dp[i+1][j];
                }
            }
        }

        return dp[0][0];
    }
};
```

---

## Complexity

- Time: $$O(n \times m)$$
- Space: $$O(n \times m)$$

---

# Approach 3: Bottom-Up DP (1D Optimization)

## Idea

We observe:

```text
dp[i][j] depends only on dp[i+1][j] and dp[i+1][j+1]
```

So we can compress 2D → 1D.

---

## Important Detail

We must update carefully to avoid overwriting needed values.

---

## Code

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        vector<unsigned long long> dp(t.size() + 1, 0);

        dp[t.size()] = 1;

        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = 0; j < t.size(); j++) {
                if (s[i] == t[j]) {
                    dp[j] = dp[j] + dp[j + 1];
                }
            }
        }

        return dp[0];
    }
};
```

---

## Complexity

- Time: $$O(n \times m)$$
- Space: $$O(m)$$

---

# Key Concepts

### 1. Decision at each step

```text
Take OR Skip
```

---

### 2. Counting problem

```text
Use addition, not max
```

---

### 3. DP State

```text
dp[i][j] = ways to form t[j:] from s[i:]
```

---

### 4. Optimization path

```text
Recursion → Memoization → Tabulation → Space Optimization
```
