# Maximum Product Subarray

Given an integer array `nums`, find a contiguous subarray within the array that has the **largest product**, and return that product.

A subarray must be **non-empty** and **contiguous**.

Example:

```
Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product = 6
```

---

# Intuition

This problem looks similar to **Maximum Subarray Sum (Kadane’s Algorithm)**, but multiplication introduces an important twist.

Negative numbers can flip the sign of the product:

```
positive × negative → negative
negative × negative → positive
```

This means a very **small negative product** can become the **largest positive product** if multiplied by another negative number later.

Because of this, at every index we must track **two values**:

```
1. Maximum product ending at the current index
2. Minimum product ending at the current index
```

Why minimum?

Because a negative number multiplied with the **minimum product** could become the next **maximum product**.

For every element `nums[i]`, the possible products are:

```
nums[i]                    (start a new subarray)
nums[i] * previousMax      (extend previous maximum product)
nums[i] * previousMin      (extend previous minimum product)
```

So we take:

```
newMax = max(nums[i], nums[i]*previousMax, nums[i]*previousMin)
newMin = min(nums[i], nums[i]*previousMax, nums[i]*previousMin)
```

We keep updating the global answer with the maximum product found so far.

---

# Approach

This solution uses **Dynamic Programming with state compression**.

Instead of storing a full DP array, we only track:

```
prevMx → maximum product ending at previous index
prevMn → minimum product ending at previous index
```

Since the current state depends only on the previous state, we reduce the space complexity to **O(1)**.

---

# Complexity

**Time Complexity**

```
O(n)
```

We iterate through the array once.

**Space Complexity**

```
O(1)
```

Only constant extra variables are used.

---

# Code

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {

        // initially we initialized 0th number as res, prevMn, prevMx
        int res = nums[0];
        int prevMn = res, prevMx = res;

        //
        for (int i = 1; i < nums.size(); i++) {
            int oldMx = prevMx;
            int oldMn = prevMn;

            // we need to track new prevMx from previous subarray
            prevMx = max({nums[i], oldMx * nums[i], oldMn * nums[i]});

            // we need to track new prevMx from previous subarray
            prevMn = min({nums[i], oldMx * nums[i], oldMn * nums[i]});

            // in last res will be max btw the prevmax and res
            res = max(prevMx, res);
        }

        return res;
    }
};
```

---

# Key Insight

The crucial idea is that **both maximum and minimum products must be tracked** because negative numbers can flip the sign of the product.

This technique is a variation of **Kadane’s Algorithm**, extended to handle multiplication and sign changes.
