### Longest Valid Paranthesis

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if (n == 0)
            return 0;

        vector<int> dp(n, 0);
        int res = 0;

        for (int i = 0; i < n; i++) {

            // case 1
            if (s[i] == ')' && i > 0 && s[i - 1] == '(') {
                dp[i] = 2;

                if (i >= 2)
                    dp[i] += dp[i - 2];
            }

            // case 2
            else if (s[i] == ')' && i > 0 && s[i - 1] == ')') {
                int j = i - dp[i - 1] - 1;
                if (j >= 0 && s[j] == '(') {
                    dp[i] += dp[i - 1] + 2;
                    if (j > 0)
                        dp[i] += dp[j - 1];
                }
            }

            res = max(res, dp[i]);
        }

        return res;
    }
};
```
