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