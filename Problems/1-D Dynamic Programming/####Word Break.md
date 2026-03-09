# Word Break

## Intuition

We need to determine whether a string `s` can be segmented into valid dictionary words.

A key observation is that if we know some **prefix of the string is already valid**, and the **remaining part forms a dictionary word**, then the whole prefix becomes valid.

So we build the solution **incrementally using Dynamic Programming**.

Think of the string as **cut positions** rather than characters.

```
s = "applepenapple"

positions:
0 a 1 p 2 p 3 l 4 e 5 p 6 e 7 n 8 a 9 p 10 p 11 l 12 e
```

If `"apple"` exists in the dictionary:

```
0 → 5
```

If `"pen"` exists:

```
5 → 8
```

If `"apple"` exists again:

```
8 → 13
```

If we can reach the final position `n`, then the string can be segmented.

---

# Approach (Bottom-Up Dynamic Programming)

We define:

```
dp[i] = true if the first i characters of s can be segmented using dictionary words
```

Base case:

```
dp[0] = true
```

Because an **empty string is always valid**.

---

### Transition

For each index `i`, we check all possible previous cut positions `j`.

If:

```
dp[j] == true
AND
s[j:i] exists in dictionary
```

then

```
dp[i] = true
```

---

### Algorithm

1. Convert `wordDict` into a hash set for fast lookup.
2. Create a DP array of size `n + 1`.
3. Initialize `dp[0] = true`.
4. For every index `i` from `1 → n`:
   - Try every `j` from `0 → i-1`
   - Check substring `s[j:i]`
   - If it exists in dictionary and `dp[j]` is true:
     - mark `dp[i] = true`
     - break

5. Return `dp[n]`.

---

# Dry Run

Example

```
s = "aaaaaaa"
dict = ["aaaa","aaa"]
```

DP table:

```
index: 0 1 2 3 4 5 6 7
dp:    T F F F F F F F
```

### i = 3

```
s[0:3] = "aaa"
```

Dictionary contains `"aaa"` and `dp[0] = true`

```
dp[3] = true
```

---

### i = 4

```
s[0:4] = "aaaa"
```

Dictionary contains `"aaaa"` and `dp[0] = true`

```
dp[4] = true
```

---

### i = 6

```
s[3:6] = "aaa"
```

Dictionary contains `"aaa"` and `dp[3] = true`

```
dp[6] = true
```

---

### i = 7

```
s[3:7] = "aaaa"
```

Dictionary contains `"aaaa"` and `dp[3] = true`

```
dp[7] = true
```

Final answer:

```
dp[7] = true
```

---

# Code

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {

        int n = s.size();

        unordered_set<string> dict(wordDict.begin(), wordDict.end());

        vector<bool> dp(n + 1, false);

        dp[0] = true;

        for (int i = 1; i <= n; i++) {

            for (int j = 0; j < i; j++) {

                string word = s.substr(j, i - j);

                if (dict.count(word) && dp[j]) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};
```

---

# Complexity Analysis

### Time Complexity

```
O(n^3)
```

Explanation:

```
O(n^2) substring checks
O(n) substring creation
```

---

### Space Complexity

```
O(n)
```

For the DP array.

---

# Alternative Approaches

### Top-Down (Memoization)

Instead of building prefixes, we recursively check if the string from index `i` can be segmented.

Define:

```
dfs(i) = whether substring s[i:n] can be segmented
```

Memoization prevents recomputation.

---

# Key Insight

This problem can also be viewed as a **graph reachability problem**.

Indices are nodes:

```
0 1 2 3 4 5 ... n
```

If `s[i:j]` is a dictionary word, we add an edge:

```
i → j
```

The problem becomes:

```
Can we reach node n starting from node 0?
```

Dynamic Programming simply tracks **which indices are reachable**.
