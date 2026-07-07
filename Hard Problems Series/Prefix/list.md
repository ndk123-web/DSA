## Prefix Sum Lists

* #[Foundation of Prefix Sum]
* 1. Subarray Sum Equals K (Prefix Sum + HashMap) - [LeetCode 560](https://leetcode.com/problems/subarray-sum-equals-k/)
  - Trick -> need to check is there previous prefix sum that is in map ? (map contains previous prefix sums of subarrays)
  - Best example: [1,-1,1,-1,1], k = 1, output = 6, dry run it 
  - if previous prefix sum is exists then we need to add the count of that prefix sum count to the result
  - In Map we are storing the prefix sum and its count, (count means how many times that prefix sum has been seen so far in subarray)
  - Need (HashMap, and PrefixSum) to solve this problem

* 2. Subarray Continous Sum (Prefix Sum + HashMap) - [LeetCode 523](https://leetcode.com/problems/continuous-subarray-sum/)
  - Trick -> Map storing prefix sum remainder with the index where it was seen
  - assume [23,2,4,6,7] k = 6, here remainder of prefx sum is [5, 1, 5, 5, 0] and we can see that remainder 5 is seen at index 0 and index 2, so we can say that subarray sum from index 1 to index 2 is divisible by k 
  - see assume current index at 2, current prefix sum is 29, remainder is 5, we can see that remainder 5 is seen at index 0, so we can say that subarray sum from index 1 to index 2 is divisible by k 

* 3. Minimum Lights to Illuminate a Street (Prefix Sum + Greedy + Difference Array) [LeetCode 605](https://leetcode.com/problems/can-place-flowers/)
   