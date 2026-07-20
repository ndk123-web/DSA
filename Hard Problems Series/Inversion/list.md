## Inversion Counting

1. Minimum Adjacent Swaps to partition arrays
- Trick -> 
    - If zoneA found in zoneC then need to traverse (zoneB + zoneC) , or if found in zoneB then need to traverse (zoneB) only 
    - If ZoneB found in zoneC then only need to traverse (zoneC)
    - If zoneC found in zoneB/zoneC then just increase the element count of zoneC 

```cpp
class Solution {
public:
    int minAdjacentSwaps(vector<int>& nums, int a, int b) {
        /*
            Input: nums = [1,3,2,4,5,6], a = 3, b = 4
        */
        long long zoneB = 0;
        long long zoneC = 0;
        long long res = 0;
        const int MOD = 1e9 + 7;

        for (int& num : nums) {
            if (num < a) {

                // if its zoneA in either of zoneB/zoneC then pass through both zones that many required adjacent swaps
                res += zoneB + zoneC;
            } else if (num >= a && num <= b) {

                // if its zoneB in zoneC then swap zoneC elements (logically swap)
                res += zoneC;
                zoneB++;
            } else {

                // if its zoneC then don't need to do anything just ++ , further condition 1,2 will do there work to count res
                zoneC++;
            }
        }

        return res % MOD;
    }
};
```

2. Global and Local Inversions [Leetcode 775](https://leetcode.com/problems/global-and-local-inversions/)
   - Trick-> if global inversion from nums[i] > any(nums[i+2]...nums[n-1]) means local inversion is not equal to global inversion, so we can check if nums[i] > max(nums[i+2]...nums[n-1]) then return false else true
   - Store PrefixMin[i] = min(nums[i], PrefixMin[i+1]) means we are storing the minimum value from n-1 to 0 in PrefixMin[i] 
```cpp
class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixMin(n, INT_MAX);

        // prefixMin[i] = min(nums[i], prefixMin[i + 1]) means we are storing the minimum value from i to n-1 in prefixMin[i]
        prefixMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            prefixMin[i] = min(nums[i], prefixMin[i + 1]);
        }

        for (int i = 0; i < n - 2; i++) {
            if (nums[i] > prefixMin[i + 2])
                return false;
        }

        return true;
    }
};
```

3. Count the smaller numbers after self [Leetcode 315](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)
   - Trick-> Use Merge Sort to count the smaller numbers after self, while merging we can count how many elements from right array are smaller than the current element from left array and add that count to the result for that index
```cpp
class Solution {
public:
    vector<int> res;

    void merge(vector<pair<int, int>>& arr, int l, int mid, int r) {

        vector<pair<int, int>> left(arr.begin() + l, arr.begin() + mid + 1);
        vector<pair<int, int>> right(arr.begin() + mid + 1,
                                     arr.begin() + r + 1);

        int i = 0;
        int j = 0;
        int k = l;

        int rightMoved = 0;

        while (i < left.size() && j < right.size()) {

            if (right[j].first < left[i].first) {
                arr[k++] = right[j++];
                rightMoved++;
            } else {
                res[left[i].second] += rightMoved;
                arr[k++] = left[i++];
            }
        }

        while (i < left.size()) {
            res[left[i].second] += rightMoved;
            arr[k++] = left[i++];
        }

        while (j < right.size()) {
            arr[k++] = right[j++];
        }
    }

    void mergeSort(vector<pair<int, int>>& arr, int l, int r) {

        if (l >= r)
            return;

        int mid = l + (r - l) / 2;

        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);

        merge(arr, l, mid, r);
    }

    vector<int> countSmaller(vector<int>& nums) {

        int n = nums.size();

        res.assign(n, 0);

        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++)
            arr.push_back({nums[i], i});

        mergeSort(arr, 0, n - 1);

        return res;
    }
};
```