# Product of Array Except Self — Two Solutions

---

## Problem Summary

Given an array `nums`, return an array `res` where:

```
res[i] = product of all elements in nums except nums[i]
```

You must solve the problem:

* **without using division**, and
* in **O(n)** time.

---

# Solution 1 — Optimized Prefix + Postfix Pass (Best Solution)

This approach does not use extra arrays for prefix and postfix. It builds:

* **prefix products** in `res[]` (first pass)
* **postfix products** using a variable `postFix` (second pass)

## Code

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {

        int n = nums.size();
        vector<int> res(n, 1);

        // Left prefix pass
        for (int i = 1; i < n; i++) {
            res[i] = res[i - 1] * nums[i - 1];
        }

        // Right postfix pass
        int postFix = 1;
        for (int i = n - 1; i >= 0; i--) {
            res[i] = res[i] * postFix;
            postFix = postFix * nums[i];
        }

        return res;
    }
};
```

---

## Explanation

### Prefix pass

`res[i]` stores the **product of all elements to the left** of index `i`.

Example building prefix:

```
nums = [1, 2, 3, 4]
res  = [1, 1, 2, 6]
```

### Postfix pass

`postFix` accumulates the **product of all elements to the right** of index `i`.
At each index:

```
res[i] = left_product * right_product
```

Then we update:

```
postFix *= nums[i]
```

This gives the final result in one array without extra memory.

---

## Time and Space Complexity

* Time: **O(n)**
* Space: **O(1)** extra space (ignoring output array)

---

# Solution 2 — Using Separate Left and Right Arrays (Simple to understand)

This method builds two arrays:

* `L[i]` = product of all elements to the **left** of `i`.
* `R[i]` = product of all elements to the **right** of `i`.

Finally:

```
res[i] = L[i] * R[i]
```

## Code

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> L(n, 1);
        vector<int> R(n, 1);
        vector<int> result(n, 1);

        // Build prefix left products
        for (int i = 1; i < n; i++) {
            L[i] = L[i - 1] * nums[i - 1];
        }

        // Build suffix right products
        for (int i = n - 2; i >= 0; i--) {
            R[i] = R[i + 1] * nums[i + 1];
        }

        // Multiply left and right
        for (int i = 0; i < n; i++) {
            result[i] = L[i] * R[i];
        }

        return result;
    }
};
```

---

## Explanation

For index `i`, we need:

```
all elements on left of i  → L[i]
all elements on right of i → R[i]
```

Multiplying these gives product except itself.

### Example

```
nums = [1, 2, 3, 4]
L    = [1, 1, 2, 6]
R    = [24, 12, 4, 1]
result = [24, 12, 8, 6]
```

---

## Time and Space Complexity

* Time: **O(n)**
* Space: **O(n)** for L and R arrays

---

# Summary

| Method                     | Time | Space | Notes                    |
| -------------------------- | ---- | ----- | ------------------------ |
| Optimized Prefix + Postfix | O(n) | O(1)  | Best solution, efficient |
| Separate L & R arrays      | O(n) | O(n)  | Easiest to understand    |

Both methods correctly solve the problem without using division and in linear time.

---
