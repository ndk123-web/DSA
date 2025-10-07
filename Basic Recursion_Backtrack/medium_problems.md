### 1. Subsequence

- Time Complexity -> O (2^ n)
- Space Complexity -> O (n)

```bash
                   []
             /                 \
          [3]                 []
       /        \           /       \
   [3,1]       [3]      [1]         []
   /   \       /  \      /  \        /  \
[3,1,2][3,1] [3,2][3] [1,2][1]    [2]  []

```

```cpp
#include <iostream>
#include <vector>

using namespace std;

void subseq(vector<int> &ans, vector<int> &arr, int index, int size){

   if (index >= size){
       if (ans.empty()){
            cout << "[]" << endl;
       }
       cout << "[";
       for (auto i : ans){
           cout << i << " ";
       }
       cout << "]" << endl;
       return;
   }

   // take it
   ans.push_back(arr[index]);
   subseq(ans,arr,index+1,size);

   // after take it remove it (backtrack)
   ans.erase(ans.begin()+index);
   subseq(ans,arr,index+1,size);
}

int main() {

    vector<int> arr = {3,1,2};
    vector<int> ans = {};

    subseq(ans,arr,0,arr.size());

    return 0;
}
```

### 2. Subsequence Sum

```cpp
#include <iostream>
#include <vector>

using namespace std;

void subseq(vector<int> &ans, vector<int> &arr, int index, int size, int k , int sum){

   if (index >= size){
       if(sum == k){
           for(auto i : ans){
               cout << i << " ";
           }
           cout << endl;
       }
       return;
   }

   // take it
   ans.push_back(arr[index]);
   sum+=arr[index];

   subseq(ans,arr,index+1,size,k,sum);

   // after take it remove it (backtrack)
   ans.erase(ans.begin()+index);
   sum-=arr[index];
   subseq(ans,arr,index+1,size,k,sum);
}

int main() {

    vector<int> arr = {3,1,2};
    vector<int> ans = {};
    int k = 3;

    subseq(ans,arr,0,arr.size(),k,0);

    return 0;
}
```

### 3 Combination Sum 1 (leetcode 39)

```cpp
class Solution {
public:
    void recursion(vector<int>& candidates, int target, vector<vector<int>> &ans, int start, vector<int> &can) {
        if (target == 0) {
            ans.emplace_back(can);
            return;
        }
        else if (target < 0){
            return;
        }
        for (int i = start; i < candidates.size(); i++){
            can.emplace_back(candidates[i]);
            recursion(candidates,target-candidates[i],ans,i,can);
            can.pop_back();  // this is very important
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> can;
        recursion(candidates, target, ans , 0 ,can);
        return ans;
    }
};
```

### 4 Combination Sum 2

```cpp
class Solution {
public:
    void recursion(vector<int>& candidates, int target, vector<int>& can, vector<vector<int>>& ans, int start) {
        if (target == 0) {
            ans.emplace_back(can);
            return;
        } else if (target < 0) {
            return;
        }

        for (int i = start; i < candidates.size(); i++) {

            // because duplicate not allowed
            if (i > start && candidates[i] == candidates[i - 1]) {
                continue;
            }

            can.emplace_back(candidates[i]);
            recursion(candidates, target - candidates[i], can, ans, i+1);
            can.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> can;
        vector<vector<int>> ans;

        // sort first if multiple elements is there
        sort(candidates.begin(), candidates.end());

        recursion(candidates, target, can, ans, 0);
        return ans;
    }
};
```

### 5 Subset 1
- Time -> O (N * 2^N)
- Space -> O (2^N)
```bash
[]
├── [1]
│   ├── [1, 2]
│   │   ├── [1, 2, 3]
│   │   └── (backtrack to [1, 2])
│   └── [1, 3]
│       └── (backtrack to [1])
│
├── [2]
│   ├── [2, 3]
│   └── (backtrack to [2])
│
└── [3]
    └── (backtrack to [])

```
```cpp
class Solution {
public:

    void recursion(vector<int>& oneAns, vector<vector<int>>& ans, vector<int> &nums, int start){
        ans.push_back(oneAns);

        for(int i = start; i < nums.size(); i++){
            oneAns.push_back(nums[i]);
            recursion(oneAns,ans,nums,i+1);
            oneAns.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> oneAns;

        recursion(oneAns,ans,nums,0);

        return ans;
    }
};
```

### 6 Subset 2
- Time -> O (N * 2^N)
- Space -> O (2^N)
```cpp
class Solution {
public:

    void recursion(vector<vector<int>>& ans, vector<int>& oneAns, int start, vector<int>& nums){
        ans.push_back(oneAns);

        for(int i = start; i < nums.size(); i++){
            if( i > start && nums[i] == nums[i-1] ) continue;
            oneAns.push_back(nums[i]);
            recursion(ans,oneAns,i+1,nums);
            oneAns.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> oneAns;

        sort(nums.begin(),nums.end());

        recursion(ans,oneAns,0,nums);

        return ans;
    }
};
```

### 7 Permutations
| Complexity Type     | Complexity | Explanation                                           |
| ------------------- | ---------- | ----------------------------------------------------- |
| **Time**            | O(N × N!)  | N! permutations, each costs O(N) work to copy + erase |
| **Auxiliary Space** | O(N)       | Recursion stack + temp vectors per call               |
| **Total Space**     | O(N × N!)  | Including output storage                              |

```cpp
class Solution {
public:

    void recursion(vector<vector<int>>& ans, vector<int>& oneAns, vector<int> &nums, int size){
        if (nums.empty()){
            ans.push_back(oneAns);
            return;
        }   

        for (int i = 0; i < nums.size(); i++){
            oneAns.push_back(nums[i]); // selects first

            vector<int> tempNums(nums.begin(),nums.end());
            // its erase only that index element (it takes iterator object)
            tempNums.erase(tempNums.begin()+i);
            
            recursion(ans,oneAns,tempNums,size);
            
            // after done remove the added element on that specific loop 
            oneAns.pop_back();
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> oneAns;

        recursion(ans,oneAns,nums,nums.size());

        return ans;
    }
};
```
