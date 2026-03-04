# Longest Palindromic Substring

Given a string `s`, return the longest substring that is a palindrome.

A **palindrome** is a string that reads the same forward and backward.

Examples:

```
Input:  s = "babad"
Output: "bab" or "aba"

Input:  s = "cbbd"
Output: "bb"
```

---

# Intuition

A palindrome has a key structural property:

If a substring `s[i..j]` is a palindrome:

1. The **first and last characters must match**
2. The **substring inside it must also be a palindrome**

```
s[i..j] is palindrome if
s[i] == s[j]  AND  s[i+1..j-1] is palindrome
```

Example:

```
abba
↑  ↑
a  a

Inside substring = "bb"
```

Since `"bb"` is already a palindrome, `"abba"` becomes a palindrome.

This idea leads to a **Dynamic Programming solution**.

Another observation is that every palindrome expands **around a center**, which leads to a **two-pointer approach**.

---

# Approach 1: Dynamic Programming (2D DP)

## Idea

Define:

```
dp[i][j] = true if substring s[i..j] is palindrome
```

Transition rule:

```
dp[i][j] = true
if
s[i] == s[j] AND (len == 2 OR dp[i+1][j-1])
```

Explanation:

- If the substring length is **2**, we only check if both characters match.
- If length > 2, the **inner substring must already be a palindrome**.

Example:

```
abba
```

Step-by-step:

```
bb → palindrome
abba → edges match AND inner substring "bb" is palindrome
```

---

## Algorithm

1. Initialize all single characters as palindromes.
2. Check substrings of length `2`.
3. Expand to longer substrings using the recurrence relation.
4. Track the longest palindrome found.

---

## Complexity

Time Complexity

```
O(n²)
```

Space Complexity

```
O(n²)
```

---

## Code (2D DP)

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();

        vector<vector<bool>> dp(n, vector<bool>(n,false));

        int start = 0;
        int maxLen = 1;

        for(int i=0;i<n;i++)
            dp[i][i] = true;

        for(int len=2; len<=n; len++){

            for(int i=0;i<=n-len;i++){

                int j = i + len - 1;

                if(s[i] == s[j]){

                    if(len == 2 || dp[i+1][j-1]){

                        dp[i][j] = true;

                        if(len > maxLen){
                            start = i;
                            maxLen = len;
                        }
                    }
                }
            }
        }

        return s.substr(start,maxLen);
    }
};
```

---

# Approach 2: Expand Around Center (Two Pointers)

## Idea

Every palindrome expands **around a center**.

Examples:

```
aba   → center = b
abba  → center between b and b
```

So for each index we check two cases:

```
odd length  → expand(i, i)
even length → expand(i, i+1)
```

We expand outward while characters match.

---

## Example

```
s = "babad"
```

Check center at index `1`:

```
expand(1,1)
a
bab
```

Check center at index `2`:

```
expand(2,2)
b
aba
```

Longest palindrome = `"bab"` or `"aba"`.

---

## Complexity

Time Complexity

```
O(n²)
```

Space Complexity

```
O(1)
```

This approach avoids the DP table and only uses pointers.

---

## Code (Two Pointers)

```cpp
class Solution {
private:
    string expand(string& s, int l, int r){

        while(l>=0 && r<s.size() && s[l]==s[r]){
            l--;
            r++;
        }

        return s.substr(l+1, r-l-1);
    }

public:
    string longestPalindrome(string s) {

        int n = s.size();
        string ans = "";

        for(int i=0;i<n;i++){

            string odd = expand(s,i,i);
            string even = expand(s,i,i+1);

            if(odd.size() > ans.size())
                ans = odd;

            if(even.size() > ans.size())
                ans = even;
        }

        return ans;
    }
};
```

---

# Key Insight

The DP solution explicitly stores palindrome states for every substring.

The expand-around-center solution relies on the observation that **palindromes grow symmetrically from a center**, allowing us to check them without storing intermediate states.

Both approaches have `O(n²)` time complexity, but the two-pointer method uses **constant space**, making it the preferred practical solution.
