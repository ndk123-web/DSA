### 1 Majority Element 2

- Why candidate1 & candidate2 ? because in whether any amount of size the maximum elements will be the 2 (if we want > n/3)
- How ? Example
- Ex 1: [2,3,3,2] => 4/3 = 1 , here maximum 1 + 1 = 2 greatest which is first 2 and second 2
- Ex 2: [2,3,3,2,1,2] => 6/3 = 2 , here maximum 2 + 1 = 3 greatest which is first 3 and second 3

- Time -> N
- Space -> O(1)

```cpp
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int candidate1 = 0 , candidate2 = 1;
        int cnt1 = 0 , cnt2 = 0;
        vector<int> ans;

        // find most greatest 2 elements
        for (int num: nums){
            if (num == candidate1) cnt1++;
            else if (num == candidate2) cnt2++;
            else if (cnt1 == 0) {candidate1 = num; cnt1 = 1;}
            else if (cnt2 == 0) { candidate2 = num , cnt2 = 1;}
            else{cnt1--; cnt2--;}
        }

        // find actual count of that both candidates
        cnt1 = cnt2 = 0;
        for (int num: nums){
            if (num == candidate1) cnt1++;
            if (num == candidate2) cnt2++;
        }

        // verify > n/3 if yes put it in ans
        if (cnt1 > nums.size()/3) ans.push_back(candidate1);
        if (cnt2 > nums.size()/3) ans.push_back(candidate2);

        // in last return the ans
        return ans;

    }
};
```

### 2 Pascal Triagnle

- Returns the entire traingle

```cpp
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        vector<int> part;

        if (numRows == 1) {
            part.push_back(1);
            ans.push_back(part);
            return ans;
        }

        part.push_back(1);
        ans.push_back(part);

        part.push_back(1);
        ans.push_back(part);

        part.clear();

        for (int i = 2; i < numRows; i++) {
            vector<int> last = ans.back();

            int placing = i - 1;
            part.push_back(1);

            for (int j = 0; j < placing; j++) {
                part.push_back(last[j] + last[j + 1]);
            }

            part.push_back(1);
            ans.push_back(part);

            part.clear();
        }

        return ans;
    }
};
```

### 3 Pascal Triagle

- Returns specific row

```cpp
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> ans;
        vector<int> lastPart = {1};

        if (rowIndex == 0){
            return lastPart;
        }
        lastPart.push_back(1);

        for (int i = 2; i <= rowIndex; i++){
            int placing = i - 1;
            ans.push_back(1);

            for (int j = 0 ; j < placing; j++){
                ans.push_back(lastPart[j]+lastPart[j+1]);
            }

            ans.push_back(1);
            lastPart = ans;
            ans.clear();
        }
        return lastPart;
    }
};
```

### 4 Three sum (Optimized)

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> part;
        int n = nums.size();

        // first sort
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    ans.push_back({nums[i], nums[left], nums[right]});

                    // skip duplicates
                    // left < right is imprtant because we need to validate is in the range or not
                    while (left < right && nums[left] == nums[left + 1])
                        left++;
                    while (left < right && nums[right] == nums[right - 1])
                        right--;

                    // after duplicates take next left and right elements
                    left++;
                    right--;
                }

                else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
       return ans;
    }
};
```

### Three Sum ( Hashing )

- Time -> N^2
- Space -> N

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> sett;
        int n = nums.size();
        sort(nums.begin(), nums.end()); // sort array first

        for (int i = 0; i < n - 1; i++) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;         // skip duplicates

            unordered_set<int> q; // to check the required number quickly

            for (int j = i + 1; j < n; j++) {
                int tobeFind = -(nums[i] + nums[j]);
                if (q.find(tobeFind) != q.end()) {
                    sett.insert({nums[i], tobeFind, nums[j]}); // sorted triplet
                }
                q.insert(nums[j]);
            }
        }

        return vector<vector<int>>(sett.begin(), sett.end());
    }
};
```
