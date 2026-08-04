### Find Missing Element
- Trick -> first sort , find pivot where `nums[i] + 1 != nums[i+1]` and then iterate through `nums[i] + 1` to `nums[i+1]`
`
```cpp
class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> res;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i + 1] != nums[i] + 1) {
                int st = nums[i] + 1;
                int end = nums[i + 1] - 1;
                for (int i = st; i <= end; i++)
                    res.push_back(i);
            }
        }
        return res;
    }
};
```