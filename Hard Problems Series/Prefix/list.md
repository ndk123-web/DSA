## Prefix Sum Lists

### [PATTERN 1 - Foundation Of Prefix Sum --> (prev Prefix - current Prefix = subarray sum)]
* 1. Subarray Sum Equals K (Prefix Sum + HashMap) - [LeetCode 560](https://leetcode.com/problems/subarray-sum-equals-k/)
  - Trick -> need to check is there previous prefix sum that is in map ? (map contains previous prefix sums of subarrays)
  - Best example: [1,-1,1,-1,1], k = 1, output = 6, dry run it 
  - if previous prefix sum is exists then we need to add the count of that prefix sum count to the result
  - In Map we are storing the prefix sum and its count, (count means how many times that prefix sum has been seen so far in subarray)
  - Need (HashMap, and PrefixSum) to solve this problem
  - Main Trick -> if we see the same prefix sum again then we can say that subarray sum from index (previous index + 1) to current index is equal to k

### [[PATTERN 2 - Prefix Sum + HashMap + Remainder Modulo]]
* 2. Subarray Continous Sum (Prefix Sum + HashMap) - [LeetCode 523](https://leetcode.com/problems/continuous-subarray-sum/)
  - `If two prefix sums have the same remainder modulo k, then the subarray from (previous_index + 1) to current_index has a sum divisible by k.`
  - Trick -> Map storing prefix sum remainder with the index where it was seen
  - assume [23,2,4,6,7] k = 6, here remainder of prefx sum is [5, 1, 5, 5, 0] and we can see that remainder 5 is seen at index 0 and index 2, so we can say that subarray sum from index 1 to index 2 is divisible by k 
  - see assume current index at 2, current prefix sum is 29, remainder is 5, we can see that remainder 5 is seen at index 0, so we can say that subarray sum from index 1 to index 2 is divisible by k 
  - Main Trick -> if we see the same remainder again then we can say that subarray sum from index (previous index + 1) to current index is divisible by k
* 3. Subarray Sum Divisible by K (Prefix Sum + HashMap) - [LeetCode 974](https://leetcode.com/problems/subarray-sums-divisible-by-k/)
  - Trick -> Map storing prefix sum remainder with the count of that remainder
  - `If two prefix sums have the same remainder modulo k, then the subarray from (previous_index + 1) to current_index has a sum divisible by k.`
```cpp
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        int prefix = 0, n = nums.size();
        int res = 0;

        map[0] = 1;
        for (int& num : nums) {
            prefix += num;

            if (map.count(((prefix % k) + k) % k)) {
                res += map[((prefix % k) + k) % k];
            }

            map[((prefix % k) + k) % k]++;
        }

        return res;
    }
};
```
  
### [PATTERN 3 - Transformed Prefix Sum + HashMap + Convert 0 to -1 and 1 to 1]
* 4. Contiguous Array (Prefix Sum + HashMap) - [LeetCode 525](https://leetcode.com/problems/contiguous-array/)
  - Trick -> Map storing prefix sum with the index where it was seen 
  - It becomes `longest subarrat with sum = 0`, `after converting 0 to -1 and 1 to 1`, we can say that if we see the same prefix sum again then we can say that subarray sum from index (previous index + 1) to current index is equal to 0
```cpp
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> map;
        map[0] = -1;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0)
                nums[i] = -1;
        }

        int len = 0;
        int prefix = 0;
        for (int i = 0; i < nums.size(); i++) {
            prefix += nums[i];

            // prefix and prefix - 0 is same so, written prefix
            if (map.count(prefix)) {
                len = max(len, (i - map[prefix]));
            }
            else {
                map[prefix] = i;
            }
        }

        return len;
    }
};
```
* 5. Binary Subarrays With Sum (Prefix Sum + HashMap) - [LeetCode 930](https://leetcode.com/problems/binary-subarrays-with-sum/)
  - Trick -> Map storing prefix sum with the count of that prefix sum 
  - if (prefix - goal) is exist means remove that prevous prefix sum from current prefix sum then we can say that subarray sum from index (previous index + 1) to current index is equal to goal
```cpp
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int, int> map;
        int res = 0;
        int prefix = 0;
        map[0] = 1;

        for (int i = 0; i < nums.size(); i++) {
            prefix += nums[i];

            if (map.count(prefix - goal))
                res + = map[prefix - goal];

            map[prefix]++;
        }

        return res;
    }
};
```

* 6. Count Number of Nice Subarrays (Prefix Sum + HashMap) - [LeetCode 1248](https://leetcode.com/problems/count-number-of-nice-subarrays/)
  - transformed event -> 0, odd -> 1 
  - Trick -> Map storing prefix sum with the count of that prefix sum
  - and then same logic current_prefix - previous_prefix = k, if previous prefix sum is exists then we can say that subarray sum from index (previous index + 1) to current index is equal to k
```cpp
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        for (int i = 0; i < n; i++)
            nums[i] = (nums[i] % 2 == 0) ? 0 : 1;

        int prefix = 0;
        int res = 0;
        unordered_map<int, int> map;

        map[0] = 1;
        for (int i = 0; i < n; i++) {
            prefix += nums[i];

            if (map.count(prefix - k))
                res += map[prefix - k];

            map[prefix]++;
        }

        return res;
    }
};
```

### [PATTERN 4 - Difference Sum] 
* 7. Corporate Flight Bookings (Prefix Sum + Difference Array) - [LeetCode 1109](https://leetcode.com/problems/corporate-flight-bookings/)
  - Trick -> Difference Array, we can say that if we want to add value to a range of indexes then we can add that value to the start index and subtract that value from the end index + 1, and then take prefix sum of that difference array to get the final result
  - Dry run it with example [[1,2,10],[2,3,20],[2,5,25]], n = 5
```cpp
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> res(n, 0);

        for (vector<int>& booking : bookings) {
            int first = booking[0];
            int last = booking[1];
            int seats = booking[2];

            res[first - 1] += seats;
            if (last < n)
                res[last] -= seats;
        }

        for (int i = 1; i < n; i++) {
            res[i] += res[i - 1];
        }

        return res;
    }
};
```

* 3. Minimum Lights to Illuminate a Street (Prefix Sum + Greedy + Difference Array) [LeetCode 605](https://leetcode.com/problems/can-place-flowers/)
   