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

### 8 Longest Consecutive Sequence (Better)

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        // sort first
        sort(nums.begin(),nums.end());

        // 1 2 3 4 100 200
        int cnt = 0;
        int longcnt = 0;

        for (int i = 0; i < nums.size()-1; i++){

            // for duplicates
            if (nums[i] == nums[i+1]) continue;

            // for checking i == i + 1
            if (nums[i] + 1 == nums[i+1]){
                cnt++;
                longcnt = max(longcnt,cnt);
                continue;
            }
            cnt=0;
        }

        return longcnt + 1;
    }
};
```

### 9 Longest Consecutive Sequence (Optimize)

- Time -> N
- Space -> N

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;

        // N
        unordered_set<int> sett(nums.begin(),nums.end());

        int x = 0;
        int longcnt=0;
        int cnt=0;

        for (auto it: sett){

            // imp -> it means index is end it means we not found
            // so it might be the first element
            if(sett.find(it-1) == sett.end()){
                cnt = 0;
                x = it;
                while (sett.find(x+1) != sett.end()){
                    cnt++;
                    x=x+1;
                }
                longcnt = max(longcnt,cnt);
            }
            else{
                cnt = 0;
            }
        }

        return longcnt + 1;
    }
};
```

### 10 Set Zeroes

- Time -> N \* M
- Space -> N \* M

```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        vector<int> rowsTobeZero;
        vector<int> colsTobeZero;

        int m = matrix.size();
        int n = matrix[0].size();

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == 0){
                    rowsTobeZero.push_back(i);
                    colsTobeZero.push_back(j);
                }
            }
        }

        // Set rows to zero
        for (int i = 0 ; i < rowsTobeZero.size(); i++){
            int r = rowsTobeZero[i];
            for (int j = 0 ; j < n; j++){
                matrix[r][j] = 0;
            }
        }

        // Set columns to zero
        for (int i = 0 ; i < colsTobeZero.size(); i++){
            int c = colsTobeZero[i];
            for (int j = 0 ; j < m; j++){
                matrix[j][c] = 0;
            }
        }
    }
};
```

### 11 Set Zeroes(Optimal)

- Time -> N \* M
- Space -> O (1)

```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool firstRowHasZero = false, firstColHasZero = false;

        // Check first row
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0)
                firstRowHasZero = true;
        }

        // Check first column
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0)
                firstColHasZero = true;
        }

        // Use first row & column as markers
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // Set zeros based on markers
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Handle first row
        if (firstRowHasZero) {
            for (int j = 0; j < n; j++)
                matrix[0][j] = 0;
        }

        // Handle first column
        if (firstColHasZero) {
            for (int i = 0; i < m; i++)
                matrix[i][0] = 0;
        }
    }
};

```

### 12 Rotate Matrix By 90 Deg (Brute)

- T -> N^2
- S -> N^2

```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>

using namespace std;

int main() {

    vector<vector<int>> mat = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };

    vector<vector<int>> ans(mat.begin(),mat.end());

   for (int i = 0; i < mat.size(); i++){
        for (int j = 0; j < mat.size(); j++){
            ans[j][mat.size() - i - 1] = mat[i][j];
        }
    }

    for (auto i : ans){
        for (auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }

    return 0;
}
```

### 13 Rotate Matrix In Place

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // 1. Transpose the matrix [row -> col , col -> row]
        for (int i = 0 ; i < n; i++){
            for (int j = i+1 ; j < n; j++){
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // reverse each row
        for (int i = 0 ; i < n; i++){
           reverse(matrix[i].begin(),matrix[i].end());
        }
    }
};
```

### 14 Spiral Matrix

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> ans;

        int top = 0, bottom = n - 1;
        int left = 0, right = m - 1;

        while (top <= bottom && left <= right) {

            // go right
            for (int i = left; i <= right; i++) {
                ans.push_back(matrix[top][i]);
            }
            top++;

            // go down
            for (int i = top; i <= bottom; i++) {
                ans.push_back(matrix[i][right]);
            }
            right--;

            // go left
            if (top <= bottom) {
                for (int i = right; i >= left; i--) {
                    ans.push_back(matrix[bottom][i]);
                }
                bottom--; 
            }

            // go up
            if (left <= right) { 
                for (int i = bottom; i >= top; i--) {
                    ans.push_back(matrix[i][left]);
                }
                left++;
            }
        }

        return ans;
    }
};

```
