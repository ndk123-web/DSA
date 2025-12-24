# 🔍 Search in Rotated Sorted Array II (Duplicates Allowed)

---

## 🔹 Problem Summary

You are given a **rotated sorted array** that **may contain duplicates** and a `target`.

Your task:

> Return `true` if `target` exists in the array, otherwise `false`.

---

## ❗ Why This Problem Is Harder Than Rotated Array I

In **Rotated Array I**:

- All elements are **unique**
- Binary search logic is clean

In **Rotated Array II**:

- **Duplicates break the “sorted half” detection**
- `nums[l] == nums[m] == nums[r]` gives no information
- Worst case degrades to **O(n)**

So we must **shrink boundaries carefully**.

---

## 🧠 High-Level Strategy (Your Approach)

You solved the problem in **three clear phases**:

1. **Trim duplicate boundaries** (important new step)
2. **Find pivot (minimum element index)**
3. **Apply binary search on both sorted halves**

This is a **valid and robust approach** for duplicates.

---

## 🔑 Core Concepts Used

- Binary search with duplicates
- Pivot (minimum element) detection
- Boundary shrinking when information is ambiguous
- Standard binary search on sorted ranges

---

## 💻 Final Code (Your Solution with Short Comments)

```cpp
class Solution {
private:
    // Standard binary search on sorted subarray
    bool binary_search(vector<int>& nums, int target, int l, int r) {
        while (l <= r) {
            int m = l + (r - l) / 2;

            if (nums[m] > target) {
                r = m - 1;
            } else if (nums[m] < target) {
                l = m + 1;
            } else {
                return true;
            }
        }
        return false;
    }

public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = n - 1;

        // Step 1: Find pivot while handling duplicates
        while (l < r) {

            // Remove duplicates from left boundary
            while (l < n - 1 && nums[l] == nums[l + 1] && nums[l] != target)
                l++;

            // Remove duplicates from right boundary
            while (r > 0 && nums[r] == nums[r - 1] && nums[r] != target)
                r--;

            int m = l + (r - l) / 2;

            if (nums[m] > nums[r]) {
                l = m + 1;   // minimum is in right half
            } else {
                r = m;       // minimum is at m or left half
            }
        }

        // l is pivot index
        int left_bound = (l == 0) ? 0 : l - 1;

        // Step 2: Search left sorted part
        if (binary_search(nums, target, 0, left_bound))
            return true;

        // Step 3: Search right sorted part
        return binary_search(nums, target, l, n - 1);
    }
};
```

---

## 🧪 Dry Run Example

### Input

```
nums = [2,5,6,0,0,1,2]
target = 0
```

---

### Step 1: Remove duplicates & find pivot

```
Initial: [2,5,6,0,0,1,2]
```

After shrinking duplicate edges (when needed), binary search converges to:

```
pivot index l = 3
nums[l] = 0
```

---

### Step 2: Search left part `[0..2]`

```
[2,5,6]
target = 0 → not found
```

---

### Step 3: Search right part `[3..6]`

```
[0,0,1,2]
target = 0 → found ✅
```

Return `true`.

---

## ⏱ Time Complexity

| Scenario                     | Complexity |
| ---------------------------- | ---------- |
| Average                      | O(log n)   |
| Worst case (many duplicates) | O(n)       |

⚠️ Worst case is unavoidable due to duplicates.

---

## 📌 Space Complexity

```
O(1)
```

---

## 🧠 Why Boundary Shrinking Is Required

When:

```
nums[l] == nums[m] == nums[r]
```

We cannot decide:

- Which half is sorted
- Where the minimum lies

So we:

- Move `l` forward
- Move `r` backward
- Remove useless duplicates

This **restores information** for binary search.

---

## ⚠️ Important Notes

- `while (l < r)` is correct for **pivot detection**
- `while (l <= r)` is mandatory for **value search**
- This problem **cannot guarantee O(log n)** due to duplicates
- Your approach is **safe and correct**

---

## 🎯 Interview One-Liner

> “Duplicates break standard rotated binary search, so we shrink boundaries when ambiguous, then locate the pivot and binary-search both sorted halves.”

---

## 🧠 Final Comparison

| Problem          | Duplicates | Strategy                |
| ---------------- | ---------- | ----------------------- |
| Rotated Array I  | ❌ No      | Single binary search    |
| Rotated Array II | ✅ Yes     | Boundary shrink + pivot |

---
