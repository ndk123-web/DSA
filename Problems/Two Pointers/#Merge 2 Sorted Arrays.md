
---

# #️⃣ Merge Sorted Array — LeetCode 88

**Pattern:** Two Pointers / In-Place Merge
**Difficulty:** Easy
**Topics:** Arrays, Two Pointers, Sorting

---

# 🔥 PROBLEM

You are given:

- `nums1` → sorted array with extra space at the end
- `m` → number of valid elements in nums1
- `nums2` → sorted array
- `n` → size of nums2

You must merge both arrays into `nums1` **as one sorted array**.

---

# -------------------------------------------

# 🟦 **APPROACH 1 — Extra Array Merge (Easy, O(n+m) space)**

This approach uses the classic merge logic (like merge sort).

### ✔ WHY

- Simple merging from left to right
- No overwrite issue because result goes into a separate array
- Best for understanding merging before moving to in-place version

---

# 🧠 LOGIC

- Use pointers `i` for nums1 and `j` for nums2
- Compare and push smaller element into `result`
- Append leftovers
- Copy result back into nums1

---

## **CODE**

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> result(m + n);
        int i = 0, j = 0, k = 0;

        // merge until one list ends
        while (i < m && j < n) {
            if (nums1[i] < nums2[j])
                result[k++] = nums1[i++];
            else
                result[k++] = nums2[j++];
        }

        // append leftovers
        while (i < m) result[k++] = nums1[i++];
        while (j < n) result[k++] = nums2[j++];

        // copy back to nums1
        nums1.clear();
        for (int x : result)
            nums1.push_back(x);
    }
};
```

---

# ✔ COMPLEXITY

| Time   | Space  |
| ------ | ------ |
| O(m+n) | O(m+n) |

---

# -------------------------------------------

# 🟩 **APPROACH 2 — In-Place Merge from End (Optimal, O(1) space)**

This is the **best method** for interviews.

### ✔ WHY IT WORKS

- nums1 has empty space at **end**
- Largest elements should be placed **last**
- Compare from the end of valid ranges:

  - `i = m-1` for nums1
  - `j = n-1` for nums2
  - `last = m+n-1` in nums1

This avoids overwriting earlier values.

---

# 🧠 LOGIC

1. Move three pointers from the end
2. Put the **bigger of nums1[i] and nums2[j]** at `nums1[last]`
3. Decrement pointers accordingly
4. Only nums2 may remain at the end, so loop until j finishes

---

## **CODE**

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int last = m + n - 1;
        int j = n - 1;
        int i = m - 1;

        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[last--] = nums1[i--];
            } else {
                nums1[last--] = nums2[j--];
            }
        }
    }
};
```

---

# ✔ COMPLEXITY

| Time       | Space    |
| ---------- | -------- |
| **O(m+n)** | **O(1)** |

---

# -------------------------------------------

# 📝 SUMMARY

### ✔ Extra-Array Merge

- Easiest to understand
- Uses O(m+n) extra space
- Clean and intuitive

### ✔ In-Place Merge (Preferred)

- Works from the **end**
- Avoids overwriting
- Uses **constant space**
- Official optimal solution

---
