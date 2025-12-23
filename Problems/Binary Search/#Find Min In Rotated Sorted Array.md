# 🔁 Find Minimum in Rotated Sorted Array

---

## 🔹 Problem Summary

You are given a **sorted array that has been rotated** at some pivot.

Your task:

> Return the **minimum element** in the array.

Constraints guarantee:

- All elements are **unique**
- Array was originally sorted in ascending order
- Rotation can be 0 or more times

---

## 🔑 Key Understanding

A rotated sorted array looks like:

```
[3,4,5,6,1,2]
```

It has:

- One **sorted part**
- One **unsorted (rotated) part**
- The **minimum element is the rotation point**

---

# ✅ Approach 1: Sorting (Brute Force)

---

## 🧠 Logic

- Sort the array
- First element will be the minimum

This ignores the rotated property and treats it as a normal array.

---

## 💻 Code

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[0];
    }
};
```

---

## 🧪 Dry Run

```
nums = [3,4,5,6,1,2]
after sort → [1,2,3,4,5,6]
return 1
```

---

## ⏱ Complexity

| Metric | Value           |
| ------ | --------------- |
| Time   | O(n log n) ❌   |
| Space  | O(1) / O(log n) |

---

## ❌ Drawback

- Does not use the rotated-array property
- Slower than required
- Interviewers **do not prefer this**

---

# ✅ Approach 2: Binary Search (Optimal)

---

## 🧠 Core Concept

At any time in a rotated sorted array:

- One half is always **sorted**
- The **minimum lies in the unsorted half**
- Compare `nums[m]` with `nums[r]` to decide

This allows **binary search on index space**.

---

## 🔑 Key Rules

- Search space always contains the minimum
- Never discard a possible answer
- Shrink range safely until one element remains

---

## 💻 Code (Optimal)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;

        while (l < r) {
            int m = l + (r - l) / 2;

            // Minimum is strictly on the right side
            if (nums[m] > nums[r]) {
                l = m + 1;
            }
            // Minimum is at m or on the left side
            else {
                r = m;
            }
        }

        return nums[l];
    }
};
```

---

## 🧪 Proper Dry Run

### Input

```
nums = [3,4,5,6,1,2]
```

---

### Step 1

```
l = 0, r = 5
m = 2
nums[m] = 5, nums[r] = 2
5 > 2 → l = m + 1 = 3
```

---

### Step 2

```
l = 3, r = 5
m = 4
nums[m] = 1, nums[r] = 2
1 <= 2 → r = m = 4
```

---

### Step 3

```
l = 3, r = 4
m = 3
nums[m] = 6, nums[r] = 1
6 > 1 → l = m + 1 = 4
```

---

### End

```
l == r == 4
nums[4] = 1 ✅
```

---

## ⏱ Complexity

| Metric | Value       |
| ------ | ----------- |
| Time   | O(log n) ✅ |
| Space  | O(1)        |

---

## 🔍 Why `r = m` and not `m - 1`

- `nums[m] <= nums[r]` means `m` **can be the minimum**
- Removing `m` may discard the answer
- So we **keep `m` in the search space**

👉 Never remove a candidate unless you are **100% sure**

---

## 🧠 Final Comparison

| Approach      | Uses Rotation | Time       | Interview |
| ------------- | ------------- | ---------- | --------- |
| Sorting       | ❌ No         | O(n log n) | ❌        |
| Binary Search | ✅ Yes        | O(log n)   | ✅        |

---

## 🎯 One-Line Interview Explanation

> “Since one half of a rotated sorted array is always sorted, we use binary search by comparing mid with the right boundary to locate the minimum in O(log n).”

---
