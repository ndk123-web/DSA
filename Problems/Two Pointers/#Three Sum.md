
---

# #️⃣ Three Sum — LeetCode 15

**Pattern:** Two Pointers / Sorting
**Difficulty:** Medium
**Topics:** Arrays, Sorting, Two Pointers, Hashing

---

# 🔥 PROBLEM

Return **all unique triplets** `(a, b, c)` in the array
such that:

```
a + b + c = 0
```

No duplicate triplets allowed.

---

# --------------------------------------

# 🟧 **BRUTE FORCE (HashMap Frequency Method)**

Uses sorting + two fixed numbers + frequency map to find the 3rd value.

---

## ✔ **Idea (Short)**

* Sort array
* For each pair `(i, j)`
* Third number = `-(i + j)`
* Check in frequency map if still available
* Skip duplicates
* Restore frequency after inner loop

---

## ✔ **CODE — Brute O(n²) with map**

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());          // sort for duplicates
        unordered_map<int,int> freq;
        for (auto x : nums) freq[x]++;           // build frequency map

        vector<vector<int>> res;

        for (int i = 0; i < nums.size(); i++) {
            freq[nums[i]]--;                     // use nums[i]
            if (i > 0 && nums[i] == nums[i-1])   // skip duplicate i
                continue;

            for (int j = i + 1; j < nums.size(); j++) {
                freq[nums[j]]--;                 // use nums[j]
                if (j > i + 1 && nums[j] == nums[j-1]) // skip duplicate j
                    continue;

                int target = -(nums[i] + nums[j]);     // third number

                if (freq[target] > 0)                  // exists?
                    res.push_back({nums[i], nums[j], target});
            }

            // restore freq for next i
            for (int j = i + 1; j < nums.size(); j++)
                freq[nums[j]]++;
        }

        return res;
    }
};
```

---

## ✔ **Complexity**

* **Time:** O(n²)
* **Space:** O(n) map
* Slower than optimal but easy to understand.

---

# --------------------------------------

# 🟩 **OPTIMAL — Two Pointer Method (Best Solution)**

---

## ✔ **Idea (Short)**

* Sort array
* Loop index `i`
* For each i, use two-pointer (`left`, `right`) to find pairs
* Skip all duplicates (i, left, right)
* Push triplet when sum == 0

---

## ✔ **CODE — Optimal O(n²), O(1) space**

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int n = nums.size();

        for (int i = 0; i < n - 2; i++) {

            if (i > 0 && nums[i] == nums[i - 1])       // skip duplicate i
                continue;

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < 0) left++;                   // need bigger
                else if (sum > 0) right--;             // need smaller
                else {
                    res.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    right--;

                    while (left < right && nums[left] == nums[left - 1])
                        left++;                        // skip duplicate left
                    while (left < right && nums[right] == nums[right + 1])
                        right--;                       // skip duplicate right
                }
            }
        }

        return res;
    }
};
```

---

## ✔ **Complexity**

* **Time:** O(n²)
* **Space:** O(1) (in-place, ignoring output)

---

# --------------------------------------

# 📝 **SUMMARY**

* Brute (map-based)

  * Easy to write
  * Requires frequency map
  * Still O(n²), heavier constants

* Optimal (two-pointer)

  * Most common
  * Sorted + pointers
  * Handles duplicates neatly
  * Faster and cleaner

---