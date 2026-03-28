
# Edit Distance

## Intuition

We are given two strings `word1` and `word2`. The goal is to convert `word1` into `word2` using the minimum number of operations:

* Insert
* Delete
* Replace

At any position `(i, j)`:

* We are comparing `word1[i]` with `word2[j]`
* If they match → no operation needed
* If they don’t match → we try all 3 operations and take the minimum

---

## Key Idea

Define:

```text
dp[i][j] = minimum operations to convert word1[i:] → word2[j:]
```

---

## Base Cases

* If `word1` is finished:

```text
We need to insert remaining characters of word2
```

* If `word2` is finished:

```text
We need to delete remaining characters of word1
```

---

# Approach 1: Top-Down DP (Memoization)

## Idea

Use recursion with memoization to avoid recomputation.

At `(i, j)`:

* If characters match → move both pointers
* Else → try:

  * Insert → move j
  * Delete → move i
  * Replace → move both

---

## Complexity

* Time: $$O(n \times m)$$
* Space: $$O(n \times m)$$

---

## Code

```cpp
class Solution {
private:
    vector<vector<int>> memo;

    int dfs(int i, int j, string& word1, string& word2) {

        // If word1 ends → need to insert remaining word2
        if (i == word1.size()) {
            return word2.size() - j;
        }

        // If word2 ends → need to delete remaining word1
        if (j == word2.size()) {
            return word1.size() - i;
        }

        // Return already computed result
        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        // If characters match → no operation needed
        if (word1[i] == word2[j]) {
            return dfs(i + 1, j + 1, word1, word2);
        }

        else {
            // Try all 3 operations

            // Insert: match word2[j], so move j
            int insert = dfs(i, j + 1, word1, word2);

            // Delete: remove word1[i], so move i
            int remove = dfs(i + 1, j, word1, word2);

            // Replace: fix both characters
            int replace = dfs(i + 1, j + 1, word1, word2);

            // Take minimum + 1 operation cost
            int res = 1 + min({insert, remove, replace});

            return memo[i][j] = res;
        }
    }

public:
    int minDistance(string word1, string word2) {
        memo.assign(word1.size(), vector<int>(word2.size(), -1));
        return dfs(0, 0, word1, word2);
    }
};
```

---

# Approach 2: Bottom-Up DP (Tabulation)

## Idea

Convert recursion into iterative DP table.

We build from **bottom-right → top-left**, because:

```text
dp[i][j] depends on:
dp[i+1][j], dp[i][j+1], dp[i+1][j+1]
```

---

## Base Cases

* `dp[i][c]` → delete remaining characters
* `dp[r][j]` → insert remaining characters

---

## Complexity

* Time: $$O(n \times m)$$
* Space: $$O(n \times m)$$

---

## Code

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int r = word1.size();
        int c = word2.size();

        // dp[i][j] = min operations to convert word1[i:] → word2[j:]
        vector<vector<int>> dp(r + 1, vector<int>(c + 1, INT_MAX));

        // Both empty → no operation
        dp[r][c] = 0;

        // word2 finished → delete remaining word1
        for (int i = 0; i < r; i++) {
            dp[i][c] = r - i;
        }

        // word1 finished → insert remaining word2
        for (int j = 0; j < c; j++) {
            dp[r][j] = c - j;
        }

        // Fill table bottom-up
        for (int i = r - 1; i >= 0; i--) {
            for (int j = c - 1; j >= 0; j--) {

                // If characters match → no cost
                if (word1[i] == word2[j]) {
                    dp[i][j] = dp[i + 1][j + 1];
                } 
                else {
                    // Try delete, insert, replace
                    dp[i][j] =
                        1 + min({
                            dp[i + 1][j],     // delete
                            dp[i][j + 1],     // insert
                            dp[i + 1][j + 1]  // replace
                        });
                }
            }
        }

        return dp[0][0];
    }
};
```

---

# Key Concepts

### 1. Pointer Movement Logic

```text
Delete  → move i
Insert  → move j
Replace → move both
```

---

### 2. DP State

```text
dp[i][j] = answer for suffixes
```

---

### 3. Problem Type

```text
Min-cost DP (NOT counting, NOT max)
```