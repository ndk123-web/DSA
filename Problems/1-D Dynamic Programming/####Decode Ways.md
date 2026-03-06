# Decode Ways

Given a string `s` containing only digits, return the number of ways to decode it using the mapping:

```
'A' -> 1
'B' -> 2
...
'Z' -> 26
```

A valid decoding must follow the rules:

- Digits must form numbers between **1 and 26**
- Leading zeros are **invalid**

Example

```
Input:  "226"

Possible decodings:
2 2 6  -> B B F
22 6   -> V F
2 26   -> B Z

Output: 3
```

---

# Intuition

At any index `i`, we have two possible decoding choices:

1. Decode **one digit**

```
s[i]
```

Then move to:

```
i + 1
```

2. Decode **two digits together**

```
s[i..i+1]
```

Only valid if:

```
10 ≤ number ≤ 26
```

Then move to:

```
i + 2
```

So the number of ways to decode starting from index `i` is:

```
ways(i) = ways(i+1) + ways(i+2)
```

(when both options are valid)

This forms a **1D dynamic programming recurrence**.

---

# Approach 1: Top-Down DP (Memoization)

## Idea

Use recursion to explore both decoding choices.

Define:

```
dfs(i) = number of ways to decode substring starting at index i
```

Base cases:

```
If i reaches the end → return 1
If s[i] == '0' → return 0
```

We memoize results so each index is computed only once.

---

## Complexity

Time Complexity

```
O(n)
```

Each index is solved once.

Space Complexity

```
O(n)
```

For memo storage and recursion stack.

---

## Code (Top-Down)

```cpp
class Solution {
private:
    unordered_map<int,int> memo;

    int dfs(string& s , int i) {

        if (i >= s.size())
            return 1;

        if (s[i] == '0')
            return 0;

        if (memo.count(i))
            return memo[i];

        int ways = dfs(s, i+1);

        if (i + 1 < s.size()) {

            int num = (s[i] - '0')*10 + (s[i+1] - '0');

            if (num >= 10 && num <= 26)
                ways += dfs(s,i+2);
        }

        memo[i] = ways;
        return ways;
    }

public:
    int numDecodings(string s) {
        return dfs(s,0);
    }
};
```

---

# Approach 2: Bottom-Up DP (Tabulation)

## Idea

Instead of recursion, we compute the answers from the **end of the string toward the beginning**.

Define:

```
dp[i] = number of ways to decode substring starting at index i
```

Base case:

```
dp[n] = 1
```

Meaning reaching the end represents **one valid decoding**.

Transition:

```
dp[i] = dp[i+1]      (single digit decoding)

if 10 ≤ number ≤ 26:
    dp[i] += dp[i+2]
```

We iterate backward because `dp[i]` depends on `dp[i+1]` and `dp[i+2]`.

---

## Complexity

Time Complexity

```
O(n)
```

Space Complexity

```
O(n)
```

---

## Code (Bottom-Up)

```cpp
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        int dp[n + 1];

        for (int i = 0 ; i < n; i++)
            dp[i] = 0;

        dp[n] = 1;

        for (int i = n - 1; i >= 0; i--) {

            if (s[i] == '0')
                continue;

            dp[i] = dp[i + 1];

            if (i + 1 < n) {

                int num = (s[i] - '0') * 10 + (s[i + 1] - '0');

                if (num >= 10 && num <= 26)
                    dp[i] += dp[i+2];
            }
        }

        return dp[0];
    }
};
```

---

# Key Insight

This problem is structurally similar to **Climbing Stairs**.

At each index you can take:

```
1 step → decode one digit
2 steps → decode two digits (if valid)
```

So the recurrence resembles:

```
dp[i] = dp[i+1] + dp[i+2]
```

with constraints based on the decoding rules.

---
