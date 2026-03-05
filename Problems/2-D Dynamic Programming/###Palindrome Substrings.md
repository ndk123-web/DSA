# Palindromic Substrings

Given a string `s`, return the **number of substrings that are palindromes**.

A substring is a **palindrome** if it reads the same forward and backward.

Example

```
Input:  s = "abc"
Output: 3
Explanation: "a", "b", "c"
```

```
Input:  s = "aaa"
Output: 6
Explanation: "a","a","a","aa","aa","aaa"
```

---

# Approach 1 — Dynamic Programming (2D DP)

## Intuition

A substring `s[i..j]` is a palindrome if:

```
1. s[i] == s[j]
2. the inner substring s[i+1..j-1] is also a palindrome
```

So we define:

```
dp[i][j] = true if substring s[i..j] is palindrome
```

---

## Base Case

Single characters are always palindromes.

```
dp[i][i] = true
```

So initially we already have `n` palindromes.

```
res = n
```

---

## Transition

For substring length ≥ 2:

```
dp[i][j] = true
if
s[i] == s[j] AND (len == 2 OR dp[i+1][j-1])
```

Explanation:

- If length = 2 → only check characters match (`bb`)
- If length > 2 → the inside substring must already be palindrome

Example:

```
abba
```

Steps:

```
bb → palindrome
abba → edges match AND inside "bb" is palindrome
```

---

## Complexity

Time

```
O(n²)
```

Space

```
O(n²)
```

---

## Code (DP)

```cpp
class Solution {
public:
    int countSubstrings(string s) {

        int n = s.size();

        vector<vector<bool>> dp(n, vector<bool>(n,false));

        for(int i=0;i<n;i++)
            dp[i][i] = true;

        int res = n;

        for(int len=2; len<=n; len++){

            for(int i=0;i<=n-len;i++){

                int j = i + len - 1;

                if(s[i] == s[j]){

                    if(len == 2 || dp[i+1][j-1]){

                        dp[i][j] = true;
                        res++;
                    }
                }
            }
        }

        return res;
    }
};
```

---

# Approach 2 — Expand Around Center (Two Pointers)

This is actually the **cleaner approach**.

## Key Observation

Every palindrome expands around a **center**.

Examples

```
aba   → center = b
abba  → center between b and b
```

So for every index we check:

```
odd length  → expand(i, i)
even length → expand(i, i+1)
```

While characters match, we expand outward and count palindromes.

---

## Example

```
s = "aaa"
```

Centers:

```
i=0 → "a"
i=1 → "a","aaa","aa"
i=2 → "a"
```

Total = 6.

---

## Complexity

Time

```
O(n²)
```

Space

```
O(1)
```

---

## Code (Expand Around Center)

Your confusion came from the fact that **expand must count palindromes, not return bool**.

Correct version:

```cpp
class Solution {
private:

    int expand(string &s, int l, int r){

        int count = 0;

        while(l>=0 && r<s.size() && s[l]==s[r]){
            count++;
            l--;
            r++;
        }

        return count;
    }

public:
    int countSubstrings(string s){

        int n = s.size();
        int res = 0;

        for(int i=0;i<n;i++){

            res += expand(s,i,i);     // odd
            res += expand(s,i,i+1);   // even
        }

        return res;
    }
};
```

---

# Why your two-pointer version was wrong

You wrote:

```
bool expand(...)
```

But expansion can produce **multiple palindromes**:

Example:

```
aaa
```

Center at index `1`:

```
a
aaa
```

Two palindromes from one center.

So `expand` must **return count**, not true/false.

---

# Big Insight

Both problems you solved today share the **same palindrome engine**.

| Problem                       | Goal            |
| ----------------------------- | --------------- |
| Longest Palindromic Substring | find max length |
| Palindromic Substrings        | count all       |

Same detection logic, different output.
