## Longest Increasing Subsequence (LIS)

1. Longest Increasing Subsequence (LIS): [leetcode](https://leetcode.com/problems/longest-increasing-subsequence/)
   - Trick -> use `tails` array to store the smallest tail of all inceasing subsequences with different lengths. The length of `tails` is the length of the longest increasing subsequence.
   - `tails` is `not storing LIS` but `actual highest length of increasing subsequence`

   1. NLogN solution using binary search
```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;

        for (int i = 0; i < nums.size(); i++) {
            auto it = lower_bound(tails.begin(), tails.end(), nums[i]);

            if (it == tails.end())
                tails.push_back(nums[i]);
            else {
                *it = nums[i];
            }
        }

        return tails.size();
    }
};
```
   2. N^2 solution using DP
```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size() + 1, 1);

        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];

            // for each num, check previous smallest counts , and take max one
            // counts

            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        long long res = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            res = max(res, 1LL*dp[i]);
        }

        return res;
    }
};
```

1. Russian Doll Envelopes: [leetcode](https://leetcode.com/problems/russian-doll-envelopes/)
   - Trick -> sort the envelopes by width in ascending order and by height in descending order if widht is same. Then find the LIS based on height.
   - `desc` order height if `width` is same to avoid counting the same width envelopes in LIS. 
```cpp
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {

        // (2,3) (2,5)
        // sort -> (2,5) then (2,3)
        // because see after we loop on sort, 5->3 not working and thats what
        // the behaviour we want

        sort(envelopes.begin(), envelopes.end(),
             [](const auto& a, const auto& b) {
                 // if same then descending with height because so that
                 // biggest first then smallest by that automatically
                 // lower_bound will work dry run it
                 if (a[0] == b[0]) {
                     return a[1] > b[1];
                 }

                 // or else sort according to the width
                 return a[0] < b[0];
             });

        vector<int> tails;

        for (vector<int>& envelop : envelopes) {
            int h = envelop[1];

            auto it = lower_bound(tails.begin(), tails.end(), h);
            if (it == tails.end())
                tails.push_back(h);

            else
                *it = h;
        }

        return tails.size();
    }
};
```