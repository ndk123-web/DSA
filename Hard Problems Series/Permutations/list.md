## Permutations List

### [Pattern 1: Foundation]
1. Permutations 
   - Trick -> use DFS to generate all permutations of the given array.
   - `temp` vector store the current nums after using the current number and then call the dfs function recursively to generate the next number.
   - 
```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<int> part;

    void dfs(vector<int>& nums, int idx) {
        if (nums.empty()) {
            res.push_back(part);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            part.push_back(nums[i]);
            temp(nums.begin(), nums.end());

            temp.erase(temp.begin() + i);

            dfs(temp, 0);

            // backtrack
            part.pop_back();
        }

        return;
    }

    vector<vector<int>> permute(vector<int>& nums) {
        dfs(nums, 0);
        return res;
    }
};
```

2. Permutations II (with duplicates)
   - Trick -> use DFS to generate all permutations of the given array.
   - `temp` vector store the current nums after using the current number and then call the dfs function recursively to generate the next number.
   - Use a set to avoid duplicates.
   - Use Unordered_set of string to store compress value of current permutation to avoid duplicates.
```cpp
class Solution {
public:
    unordered_set<string> sett;
    vector<vector<int>> res;
    vector<int> part;

    void dfs(vector<int>& nums, int idx) {
        if (nums.empty()) {
            string s = "";
            for (int i = 0; i < part.size(); i++) {
                s += to_string(part[i]);
            }

            if (sett.count(s)) {
                return;
            }

            res.push_back(part);
            sett.insert(s);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            part.push_back(nums[i]);

            vector<int> temp(nums.begin(), nums.end());
            temp.erase(temp.begin() + i);

            dfs(temp, 0);

            part.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        dfs(nums, 0);
        return res;
    }
};
```

3. Next Permutation
   - Trick -> 
     - find the `pivot` index from right side
     - if pivot is found, find the `closest max to pivot` index from right side
     - swap the pivot and closest max to pivot index
     - reverse the array from pivot+1 to end of the array
```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int pivot = -1;
        int i = nums.size() - 1;

        // find pivot
        while (i >= 1) {
            if (nums[i - 1] < nums[i]) {
                pivot = i - 1;
                break;
            }
            i--;
        }

        // if no pivot means greatest permutation, after that will be start
        // permutation
        if (pivot == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }

        // find closestMaxIdx to the pivot element
        int closestMaxIdx = pivot + 1;
        for (int j = pivot + 1; j < nums.size(); j++) {
            if (nums[pivot] < nums[j] && nums[j] <= nums[closestMaxIdx]) {
                closestMaxIdx = j;
            }
        }

        // swap pivot and closesMax
        swap(nums[pivot], nums[closestMaxIdx]);

        // reverse from pivot + 1 to end since they are in increeaasing order ,
        // if we want next immediate greater then we need to reverse that
        reverse(nums.begin() + pivot + 1, nums.end());
        return;
    }
};
```