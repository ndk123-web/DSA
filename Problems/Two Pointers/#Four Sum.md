
---

# #️⃣ Four Sum — LeetCode 18

**Pattern:** Two Pointers + Sorting
**Difficulty:** Medium
**Topics:** Array, Sorting, Two Pointers

---

# 🔥 PROBLEM

Given an integer array `nums` and an integer `target`,
return **all unique quadruplets** `[a, b, c, d]` such that:

```
a + b + c + d = target
```

Array may contain duplicates, but **answer must NOT** contain duplicate quadruplets.

---

# --------------------------------------------

# 🟧 BRUTE FORCE (Intuition Only)

### ✔ Idea

* Pick 4 nested loops (i, j, k, l)
* Check sum == target
* Store unique quadruplets

### ❌ Problem

* Time: **O(n⁴)** → too slow
* Duplicate handling messy
* Not acceptable for LeetCode

---

# --------------------------------------------

# 🟩 OPTIMAL APPROACH — SORT + 2 LOOPS + 2 POINTERS

### ✔ Why This Works

* Sorting helps skip duplicates
* Fix two numbers `(i, j)`
* Use two pointers `(left, right)` to find remaining 2 numbers
* Time = **O(n²)**
* Space = **O(1)** (excluding result)
* Clean and reliable pattern

---

# --------------------------------------------

# 🟦 WHY WE USE `long long` FOR `sum`

## ✔ Problem

If we do:

```cpp
int sum = nums[i] + nums[j] + nums[left] + nums[right];
```

`int + int + int + int` might overflow if values approach INT_MAX (~2 billion).

Example:

```
nums = {1e9, 1e9, 1e9, 1e9}
target = 4e9
```

`int` cannot store 4e9 → overflow → wrong result.

---

## ✔ Solution

Use **long long** for sum:

```cpp
long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
```

Now range becomes approx:

```
±9e18   (far bigger than int)
```

Safe for 4-integer addition.

---

# --------------------------------------------

# 🟩 WHY INT CAN COMPARE WITH LONG LONG

C++ allows comparison between `int` and `long long` because:

* int → automatically **promoted** to long long
* This is called **integer promotion**
* No precision loss when promoting int → long long
* So doing this is safe:

```cpp
if (sum < target) ...
```

Where:

* `sum` = long long
* `target` = int

C++ converts `target` to long long internally,
so comparison is perfectly valid.

---

# --------------------------------------------

# 🟩 CODE — FINAL OPTIMAL SOLUTION (With short comments)

```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        if (n < 4) return res;

        for (int i = 0; i < n - 3; i++) {

            if (i > 0 && nums[i] == nums[i - 1])   // skip duplicate i
                continue;

            for (int j = i + 1; j < n - 2; j++) {

                if (j > i + 1 && nums[j] == nums[j - 1])   // skip duplicate j
                    continue;

                int left = j + 1;
                int right = n - 1;

                while (left < right) {

                    long long sum = (long long)nums[i] 
                                   + nums[j] 
                                   + nums[left] 
                                   + nums[right];   // avoid overflow

                    if (sum < target) 
                        left++;
                    else if (sum > target) 
                        right--;
                    else {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        left++;
                        right--;

                        // skip duplicates at left
                        while (left < right && nums[left] == nums[left - 1])
                            left++;

                        // skip duplicates at right
                        while (left < right && nums[right] == nums[right + 1])
                            right--;
                    }
                }
            }
        }

        return res;
    }
};
```

---

# --------------------------------------------

# ⚙️ COMPLEXITY

| Part                     | Complexity                  |
| ------------------------ | --------------------------- |
| Sorting                  | O(n log n)                  |
| Two loops + two pointers | O(n²)                       |
| Total                    | **O(n²)**                   |
| Space                    | **O(1)** (excluding output) |

---

# --------------------------------------------

# 📝 SUMMARY

* Sorting + two loops + two pointers = best pattern
* Use **long long** to avoid overflow
* int vs long long compare safe due to **integer promotion**
* Skip duplicates at i, j, left, right
* Time complexity O(n²), very efficient

---