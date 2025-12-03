
---

# #️⃣ Remove Duplicates from Sorted Array — LeetCode 26

**Pattern:** Two Pointers
**Difficulty:** Easy
**Topics:** Arrays, In-Place Modification

---

# 🔥 PROBLEM

Given a **sorted** array `nums`,
remove all duplicates **in-place**,
such that each element appears only once.

Return the **count of unique elements**.
The first `k` elements of `nums` should store the unique values.

---

# --------------------------------------------

# 🟧 **BRUTE FORCE APPROACH — Extra Space (Easy but Not Allowed)**

Your brute idea:

- Compare each element with previous
- If duplicate → mark it
- Build a new array without marked elements
- Replace the original array with cleaned version

---

## ✔ LOGIC

1. Traverse array using two pointers (`prev`, `next`)
2. Mark duplicates with a sentinel (−101)
3. Build a `temp` array containing non-marked values
4. Replace `nums` with `temp`
5. Return temp size

---

## ✔ CODE — Brute Force (Extra Space)

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int next = 1;
        int prev = 0;

        if (nums.size() == 1) return 1;

        while (next < nums.size()) {
            if (nums[next] == nums[prev]) {
                nums[prev] = -101;  // mark duplicate
            }
            next++;
            prev++;
        }

        vector<int> temp;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != -101) {
                temp.push_back(nums[i]);
            }
        }

        nums = temp;
        return temp.size();
    }
};
```

---

# ✔ COMPLEXITY

| Time | Space              |
| ---- | ------------------ |
| O(n) | O(n) (extra array) |

---

# --------------------------------------------

# 🟩 **OPTIMAL — Two Pointer Technique (In-Place, O(1) space)**

This is the official and best solution.

---

# ✔ WHY IT WORKS

Since array is **sorted**, duplicates will always appear **next to each other**.

We want:

- `right` → scans entire array
- `left` → holds position for next unique number

Whenever `nums[right] != nums[right-1]`,
we have found a **new unique value**, so we:

```
nums[left] = nums[right];
left++;
```

At the end,
`left` = total count of unique elements.

---

# ✔ CODE — Optimal (Two Pointers)

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int left = 1;
        int right = 1;

        while (right < nums.size()) {
            if (nums[right] != nums[right - 1]) {
                nums[left] = nums[right];
                left++;
            }
            right++;
        }

        return left;
    }
};
```

---

# ✔ COMPLEXITY

| Time     | Space               |
| -------- | ------------------- |
| **O(n)** | **O(1)** (in-place) |

---

# --------------------------------------------

# 📝 SUMMARY

**Brute Force:**

- Mark duplicates
- Build new clean array
- Uses extra memory

**Optimal (Recommended):**

- Two-pointer method
- Moves unique elements to the front
- Fully in-place, O(1) space
- Returns count of unique values

---
