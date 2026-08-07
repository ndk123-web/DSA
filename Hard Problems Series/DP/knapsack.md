## Knapsack Problems 

### Types of Knapsack Problems 
1. Target Sum Problem [leetcode](https://leetcode.com/problems/target-sum/)
   - Trick -> Count the number of ways to assign + and - signs to make the sum equal to target, used `dp` to store the number of ways to reach a certain sum at a certain index.
```cpp
class Solution {
public:
    struct pair_hash {
        size_t operator()(const pair<int, int>& p) const {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };

    unordered_map<pair<int, int>, int, pair_hash> dp;

    int dfs(vector<int>& nums, int& target, int idx, int sum) {
        if (idx >= nums.size()) {
            if (target == sum)
                return 1;

            return 0;
        }

        if (dp.count({idx, sum})) {
            return dp[{idx, sum}];
        }

        int leftCount = dfs(nums, target, idx + 1, sum + nums[idx]);
        int rightCount = dfs(nums, target, idx + 1, -nums[idx] + sum);

        return dp[{idx, sum}] = leftCount + rightCount;
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        return dfs(nums, target, 0, 0);
    }
};
```

2. Partition Equal Subset Sum [leetcode](https://leetcode.com/problems/partition-equal-subset-sum/)
   - Trick -> use dp, basic cases to check,
     - if sum of all elements is odd, return false
     - if sum of all elements is even, check if there is a subset with sum equal to half of total sum
     - our `target` will be `half of total sum`
     - `Simple Logic is that if we can find a subset with sum equal to `target`, then the other subset will automatically have sum equal to `target` as well, since total sum is even`. 
```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);

        if (sum % 2 != 0)
            return false;

        int target = sum / 2;
        vector<bool> dp(target + 1, false);

        dp[0] = true;

        // if its divisible by 2 then
        // we need target as sum / 2
        // if we get one sum/2 as true means other half automatically will be sum / 2
        for (int& num : nums) {

            for (int j = target; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }

        return dp[target];
    }
};
```