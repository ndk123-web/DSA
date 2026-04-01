# Maximum Subarray (Kadane’s Algorithm)

## Problem Statement

Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

---

## Intuition

We want the **maximum sum of a continuous subarray**.

At every index, we have two choices:

1. Start a new subarray from current element
2. Extend the previous subarray

We always pick the better option.

---

## Key Idea

At index `i`:

```text
currentSum = max(nums[i], currentSum + nums[i])
```

We keep updating the global maximum.

---

## Approach

1. Initialize:

   * `currentSum = 0`
   * `maxSum = INT_MIN`
2. Traverse the array:

   * Update current subarray sum
   * Update maximum sum
3. Return the result

---

## Code

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int currentSum = 0;
        int maxSum = INT_MIN;

        for (int num : nums) {
            currentSum = max(num, currentSum + num);
            maxSum = max(maxSum, currentSum);
        }

        return maxSum;
    }
};
```

---

## Example

### Input

```text
nums = [-2,1,-3,4,-1,2,1,-5,4]
```

### Steps

* Best subarray: `[4, -1, 2, 1]`
* Sum = `6`

### Output

```text
6
```

---

## Edge Cases

1. All negative numbers:

   * Example: `[-3, -2, -5]`
   * Output: `-2` (maximum element)

2. Single element:

   * Return that element

---

## Complexity Analysis

* Time Complexity: `O(n)`
* Space Complexity: `O(1)`

---

## Summary

* At each step: decide whether to extend or restart.
* Tracks maximum contiguous sum efficiently.
* Foundation for many advanced problems (including circular subarray).

---
