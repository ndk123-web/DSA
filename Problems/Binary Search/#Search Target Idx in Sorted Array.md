# 🔍 Search in Rotated Sorted Array

**(Pivot + Binary Search Approach)**

---

## 🔹 Problem Summary

You are given a **sorted array rotated at an unknown pivot** and a `target`.

Rules:

* Elements are **unique**
* Array order is preserved (rotated)
* Return index of `target`, else `-1`

---

## 🧠 High-Level Strategy (Your Approach)

You solved the problem in **two phases**:

1. **Find the pivot** (index of minimum element)
2. **Split the array into two sorted parts**
3. **Apply binary search on both halves**

This is a **valid and correct approach**, though slightly longer than the one-pass method.

---

## 🔑 Key Concepts Used

* Binary Search on rotated array
* Pivot (minimum element) detection
* Standard binary search on sorted subarrays
* Careful boundary handling (`<=` vs `<`)

---

## 💻 Final Code (Your Solution with Short Comments)

```cpp
class Solution {
private:
    // Standard binary search on sorted range [left, right]
    int binary_search(vector<int>& nums, int target, int left, int right) {
        while (left <= right) {
            int m = left + (right - left) / 2;

            if (nums[m] > target) {
                right = m - 1;
            } else if (nums[m] < target) {
                left = m + 1;
            } else {
                return m;
            }
        }
        return -1;
    }

public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = n - 1;

        // Step 1: Find pivot (index of minimum element)
        while (l < r) {
            int m = l + (r - l) / 2;

            if (nums[m] > nums[r]) {
                l = m + 1;   // min is in right half
            } else {
                r = m;       // min is at m or in left half
            }
        }

        // l is pivot index
        // Left part: [0 ... l-1]
        // Right part: [l ... n-1]

        int leftEnd = (l == 0) ? 0 : l - 1;

        // Step 2: Search in left sorted part
        int res = binary_search(nums, target, 0, leftEnd);
        if (res != -1)
            return res;

        // Step 3: Search in right sorted part
        return binary_search(nums, target, l, n - 1);
    }
};
```

---

## 🧪 Dry Run Example

### Input

```
nums = [4,5,6,7,0,1,2]
target = 0
```

---

### Step 1: Find Pivot

| l | r | m | nums[m] | nums[r] | Action  |
| - | - | - | ------- | ------- | ------- |
| 0 | 6 | 3 | 7       | 2       | l = m+1 |
| 4 | 6 | 5 | 1       | 2       | r = m   |
| 4 | 5 | 4 | 0       | 1       | r = m   |

Pivot index `l = 4`

---

### Step 2: Search Left Part `[0..3]`

```
[4,5,6,7]
target = 0
→ not found
```

---

### Step 3: Search Right Part `[4..6]`

```
[0,1,2]
target = 0
→ found at index 4
```

---

## ⏱ Time Complexity

| Phase         | Complexity |
| ------------- | ---------- |
| Pivot search  | O(log n)   |
| Binary search | O(log n)   |
| Total         | O(log n)   |

---

## 📌 Space Complexity

```
O(1)
```

---

## 🧠 Why This Works

* Pivot splits array into **two sorted subarrays**
* Standard binary search works on each half
* Boundary checks (`<=`) ensure no index is skipped
* Pivot logic guarantees correctness

---

## ⚠️ Notes (Important)

* Using `while (l < r)` is correct for **pivot search**
* Using `while (left <= right)` is mandatory for **value search**
* This approach is **correct but verbose**
* Interviewers often prefer **single-pass binary search**

---

## 🎯 Interview Explanation (One Line)

> “I first locate the pivot using binary search, then apply standard binary search on both sorted halves.”

---