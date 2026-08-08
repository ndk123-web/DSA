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