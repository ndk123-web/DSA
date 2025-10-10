### 1 Subarray Sum Equals K

- `Hashing is Important`
  | Step | i | prefix sum | sum - k | psum before | count added | psum after |
  | ---- | --- | ---------- | ------- | ------------- | ----------- | ----------------- |
  | 1 | 0 | 1 | -1 | {0:1} | 0 | {0:1,1:1} |
  | 2 | 1 | 2 | 0 | {0:1,1:1} | +1 | {0:1,1:1,2:1} |
  | 3 | 2 | 3 | 1 | {0:1,1:1,2:1} | +1 | {0:1,1:1,2:1,3:1} |

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int total = 0;
        int cnt = 0;
        unordered_map<int,int> mapp;

        mapp[0] = 1;

        for (int i=0; i < nums.size();i++){
            total = total + nums[i];

            // it means find returns iterator/not found
            // end() means returns always iterators
            if (mapp.find(total-k) != mapp.end()){
                cnt = cnt + mapp[total-k];
            }

            mapp[total]++; // if key not exist then key:0 ++ means key:1
        }

        return cnt;
    }
};
```

### 2 Majority Element

- Time -> N
- Space -> N

```cpp
#include <bits/stdc++.h>

using namespace std;

int main(){

    vector<int> inp = {2,2,3,3,1,2,2};
    vector<int> ans;
    unordered_map<int,int> mpp;

    // majority element
    int n = inp.size();
    int mjaority_n = n / 2;

    for (int i = 0; i < n; i++){
        mpp[inp[i]]++;
    }

    int maxx;

    for (auto mp: mpp){
        if (mp.second > mjaority_n){
            ans.push_back(mp.first);
        }
    }

    for (auto i : ans){
        cout << i << " ";
    }

    return 0;
}
```

### 3 Boyer-Moore Voting Algorithm (alternative to ### 2)

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int elem, cnt = 0;

        for (int i = 0; i < nums.size(); i++) {
            if (cnt == 0) {
                elem = nums[i];
                cnt++;
            } else if (elem == nums[i]) {
                cnt++;
            } else {
                cnt--;
            }
        }
        return elem;
    }
};
```

### 4 Maximun Subarray Sum ( kadane's Algorithm )

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxElem = INT_MIN;
        int sum = 0;

        for (int i = 0 ; i < nums.size(); i++){
            sum = sum + nums[i];
            maxElem = max(maxElem,sum); // for future purpose if there is no positive high value

            if (sum < 0){ // if sum negative dont include
                sum = 0;
            }
        }

        return maxElem;

    }
};
```

### 5 Rearrange Array Elements by sign

```cpp
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> pos;
        vector<int> neg;
        vector<int> ans;

        // divide negative and positive 
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < 0) {
                neg.push_back(nums[i]);
            } else if (nums[i] > 0) {
                pos.push_back(nums[i]);
            }
        }

        // observation is positive values are in even index 
        // observation is negative values are in odd index
        int p = 0, n = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i % 2 == 0) {
                ans.push_back(pos[p++]);
            } else {
                ans.push_back(neg[n++]);
            }
        }

        return ans;
    }
};
```
