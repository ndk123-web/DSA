### String DP

1. Longest Common Subsequence [leetcode](https://leetcode.com/problems/longest-common-subsequence/)
   - Trick -> use 2d DP, where `dp[i][j]` will represent the length of longest common subsequence of `text1[0..i-1]` and `text2[0..j-1]` 
```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (text1[i] == text2[j]) {
                    dp[i][j] = dp[i + 1][j + 1] + 1;
                } else {
                    dp[i][j] = max(dp[i][j + 1], dp[i + 1][j]);
                }
            }
        }

        return dp[0][0];
    }
};
```

2. Longest Palindrome Substring 
   - Trick -> use 2d DP, where `dp[i][j]` will represent whether the substring `s[i..j]` is a palindrome or not. If it is a palindrome then we can check if the length of that substring is greater than the current max length and update accordingly.
```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        int st = 0;
        int maxLen = 1;

        vector<vector<bool>> dp(n, vector<bool>(n, false));

        // all diagonals are one of the answers
        // it covers length 1 palidrome substrings
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }

        /*
            assume, "aabaa"
            at len = 5, in (st = a, end = 1) we will check whether (aba) is palidrome
        */

        // now check for len = 2 to n 
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                
                if (s[i] == s[j]) {
                    if (len == 2 || dp[i + 1][j - 1]) {
                        dp[i][j] = true;

                        if (len > maxLen) {
                            maxLen = len;
                            st = i;
                        }
                    }
                }
            }
        }

        return s.substr(st, maxLen);
    }
};
``` 