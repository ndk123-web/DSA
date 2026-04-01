# Maximum Sum Circular Subarray

## Problem Statement

Given a circular integer array `nums` of length `n`, return the maximum possible sum of a non-empty subarray.

A circular array means the end of the array connects to the beginning.

---

## Intuition

A subarray in a circular array can be of two types:

1. **Non-circular subarray**

   * Lies completely within the array.
   * Solved using standard Kadane’s Algorithm.

2. **Circular subarray**

   * Wraps around the end to the beginning.
   * Instead of directly finding it, we think in reverse:

     * Remove the **minimum subarray** from the total sum.
     * Remaining elements form the maximum circular subarray.

---

## Key Idea

We compute:

* `maxSubarraySum` → using Kadane (maximum sum)
* `minSubarraySum` → using Kadane variant (minimum sum)
* `totalSum` → sum of all elements

Final answer:

```
max(maxSubarraySum, totalSum - minSubarraySum)
```

---

## Edge Case

If all elements are negative:

* `totalSum - minSubarraySum` becomes `0` (invalid case)
* We return `maxSubarraySum` directly

---

## Approach

1. Traverse the array once.
2. Maintain:

   * Current maximum subarray sum
   * Current minimum subarray sum
   * Global maximum and minimum
   * Total sum
3. Apply Kadane logic for both max and min.
4. Handle edge case (all negative).
5. Return final result.

---

## Code

```cpp
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int currentSubarrayMxSum = 0, currentSubarrayMnSum = 0;      
        int maxSubarraySum = INT_MIN, minSubarrySum = INT_MAX;
        int totalSum = 0;

        for (int& num : nums) {

            // Standard Kadane (maximum subarray)
            currentSubarrayMxSum = max(num, currentSubarrayMxSum + num);
            maxSubarraySum = max(maxSubarraySum, currentSubarrayMxSum);

            // Minimum subarray (reverse Kadane)
            currentSubarrayMnSum = min(num, currentSubarrayMnSum + num);
            minSubarrySum = min(currentSubarrayMnSum, minSubarrySum);

            // Total sum
            totalSum += num;
        }

        // Edge case: all elements are negative
        if (maxSubarraySum < 0) {
            return maxSubarraySum;
        }

        // Maximum of non-circular and circular cases
        return max(maxSubarraySum, totalSum - minSubarrySum);
    }
};
```

---

## Example

### Input

```
nums = [5, -3, 5]
```

### Computation

* maxSubarraySum = 7
* minSubarraySum = -3
* totalSum = 7

Circular sum:

```
total - min = 7 - (-3) = 10
```

### Output

```
10
```

---

## Complexity Analysis

* Time Complexity: `O(n)`
* Space Complexity: `O(1)`

---

## Summary

* Use Kadane to get maximum subarray.
* Use modified Kadane to get minimum subarray.
* Circular result = total sum - minimum subarray.
* Final answer is the maximum of both cases.
* Handle all-negative edge case separately.

---
