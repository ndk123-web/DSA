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

### 6 Next Permutation

- Steps:
  1. Find First BreakPoint
  2. Then After in place of BreakPoint put closest smaller number
  3. swap that BreakPoint with Closest Smaller Number
  4. In End Reverse Array After BreakPoint+1 to end
  5. because we want after BreakPoint most smallest numbers

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;
        int breakPoint = -1;

        // 1️⃣ Find the breakpoint
        while (i >= 0) {
            if (nums[i] < nums[i + 1]) {
                breakPoint = i;
                break;
            }
            i--;
        }

        // if no breakpoint, reverse (already highest permutation)
        if (breakPoint == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }

        // 2️⃣ Find the smallest number greater than nums[breakPoint] to its right
        int closestMaxIndex = breakPoint + 1;
        for (int j = breakPoint + 1; j < nums.size(); j++) {
            if (nums[j] > nums[breakPoint] && nums[j] <= nums[closestMaxIndex]) {
                closestMaxIndex = j;
            }
        }

        // 3️⃣ Swap them
        swap(nums[breakPoint], nums[closestMaxIndex]);

        // 4️⃣ Reverse right part
        reverse(nums.begin() + breakPoint + 1, nums.end());
    }
};

```

### 7 Leader in Array
- Time-> N
- Space -> N 
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {

    // Leader In Array
    vector<int> arr = {10,22,12,3,0,6};
    vector<int> ans;

    int maxRight = arr.back();
    ans.push_back(maxRight);

    for (int i = arr.size() - 2; i >= 0; i--) {
        if (arr[i] > maxRight) {
            ans.push_back(arr[i]);
            maxRight = arr[i];
        }
    }
    reverse(ans.begin(), ans.end());

    for (auto i : ans){
        cout << i << " ";
    }

    return 0;
}
```
