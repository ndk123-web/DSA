## Prefix Sum Lists

* #[Foundation of Prefix Sum]
* 1. Subarray Sum Equals K (Prefix Sum + HashMap) - [LeetCode 560](https://leetcode.com/problems/subarray-sum-equals-k/)
  - Trick -> need to check is there previous prefix sum that is in map ? (map contains previous prefix sums of subarrays)
  - Best example: [1,-1,1,-1,1], k = 1, output = 6, dry run it 
  - if previous prefix sum is exists then we need to add the count of that prefix sum count to the result
  - In Map we are storing the prefix sum and its count, (count means how many times that prefix sum has been seen so far in subarray)
  - Need (HashMap, and PrefixSum) to solve this problem
  
1. Minimum Lights to Illuminate a Street (Prefix Sum + Greedy + Difference Array) [LeetCode 605](https://leetcode.com/problems/can-place-flowers/)