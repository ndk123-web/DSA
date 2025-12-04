
---

# #️⃣ Rotate Array — LeetCode 189

**Pattern:** Array Manipulation
**Difficulty:** Medium
**Topics:** Arrays, Modulo, Reversal Technique

---

# 🔥 PROBLEM

Given array `nums` and integer `k`, rotate the array to the **right** by `k` steps.

Example:

```
nums = [1,2,3,4,5,6,7], k = 3
Output = [5,6,7,1,2,3,4]
```

---

# --------------------------------------

# 🟧 **Solution 1 — Extra Array (Easiest, Intuitive)**

Put each element at its new rotated index using modulo.

---

## ✔ IDEA

If element at index `i` moves to:

```
newIndex = (i + k) % n
```

---

## ✔ CODE

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> temp(n);

        for (int i = 0; i < n; i++) {
            int idx = (i + k) % n;   // compute new position
            temp[idx] = nums[i];
        }

        for (int i = 0; i < n; i++) {
            nums[i] = temp[i];       // copy back
        }
    }
};
```

---

## ✔ COMPLEXITY

* **Time:** O(n)
* **Space:** O(n) extra array

---

# --------------------------------------

# 🟩 **Solution 2 — Reverse Using STL (Best & Cleanest)**

This is the **optimal and shortest** way using the 3-reverse trick.

---

## ✔ WHY IT WORKS

Rotate right by k = reverse parts:

1. Reverse entire array
2. Reverse first `k` elements
3. Reverse the rest

This shifts elements correctly.

---

## ✔ CODE

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        int normalize_k = k % n;

        reverse(nums.begin(), nums.end());                   // reverse whole
        reverse(nums.begin(), nums.begin() + normalize_k);    // reverse first part
        reverse(nums.begin() + normalize_k, nums.end());      // reverse second part
    }
};
```

---

## ✔ COMPLEXITY

* **Time:** O(n)
* **Space:** O(1)

---

# --------------------------------------

# 🟦 **Solution 3 — Custom Reverse Function (Manual Implementation)**

Same logic as STL version but implemented manually.

---

## ✔ CODE

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        int normalize_k = k % n;

        reverseBro(nums, 0, n - 1);               // reverse whole
        reverseBro(nums, 0, normalize_k - 1);     // reverse first part
        reverseBro(nums, normalize_k, n - 1);     // reverse second part
    }

    void reverseBro(vector<int>& nums, int left, int right) {
        while (left < right) {
            swap(nums[left], nums[right]);
            left++;
            right--;
        }
    }
};
```

---

## ✔ COMPLEXITY

* **Time:** O(n)
* **Space:** O(1)

---

# --------------------------------------

# 📝 SUMMARY

### ✔ Extra Array Method (Easy)

* Simple modulo logic
* Uses O(n) extra space

### ✔ STL Reverse Method (Best)

* 3-step reverse trick
* Cleanest code
* O(n) time, O(1) space

### ✔ Manual Reverse Method

* Same optimal approach
* You control the reverse function

---