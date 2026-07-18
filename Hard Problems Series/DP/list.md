## DP Lists

### [Pattern-1: Basic Foundation]
1. [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)
   - Trick -> Use DP to store the number of ways to reach each step. The recurrence relation is `dp[i] = dp[i-1] + dp[i-2]`, where `dp[i]` represents the number of ways to reach step `i`.

2. [House Robber](https://leetcode.com/problems/house-robber/)
   - Trick -> Use DP to store the maximum amount of money that can be robbed up to each house. The recurrence relation is `dp[i] = max(dp[i-1], dp[i-2] + nums[i])`, where `dp[i]` represents the maximum amount that can be robbed up to house `i`.
```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return nums[0];

        if (n == 2)
            return max(nums[0], nums[1]);

        vector<int> dp(n, 0);

        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[n - 1];
    }
};
```

### [Pattern-2: Advanced Foundation]
1. Coin Change [Leetcode 322](https://leetcode.com/problems/coin-change/)
   - Trick: Use DP to store the minimum number of coins needed to make up each amount. The recurrence relation is `dp[i] = min(dp[i], dp[i - coin] + 1)` for each coin in the list of coins.
   - Time -> O(N * M), Space -> O(N)
```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);

        dp[0] = 0;

        // for each amount sequntially
        for (int i = 1; i <= amount; i++) {
            
            // for each coin we have
            for (int coin : coins) {

                // if its in range and dp of that sub is not INT_MAX means we can add 1 there
                // because if its not INT_MAX means we already putted min value to create that amount
                if (i - coin >= 0 && dp[i - coin] != INT_MAX)
                    dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }

        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};
```

2. Longest Increasing Subsequence [Leetcode 300](https://leetcode.com/problems/longest-increasing-subsequence/)
   - Trick: Use monotonic behaviour vector to store the smallest tail of all increasing subsequences with different lengths. Use binary search to find the position of the current number in the vector and update it accordingly.
```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> arr;
        
        for (int i = 0; i < nums.size(); i++) {
            
            // find in arr that >= nums[i]
            auto it = lower_bound(arr.begin(), arr.end(), nums[i]);

            // if there is no num >= nums[i] push (means biggest)
            if (it == arr.end())
                arr.push_back(nums[i]);
            
            // if there then update that iterator 
            else 
                *it = nums[i];
        }

        return arr.size();   
    }
};
```
    - DP 
```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++) {

            // we can skip the j = 0 to j = i-1 because we already initialized dp[i] = 1, so if there is no smaller number than nums[i] then it will remain 1
            for (int j = 0; j < i; j++) {

                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};
```