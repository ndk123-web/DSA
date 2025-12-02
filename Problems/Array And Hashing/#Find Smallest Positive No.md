
---

# #️⃣ First Missing Positive — LeetCode 41

**Difficulty:** Hard
**Topic:** Arrays, Sorting, Cyclic Sort
**Patterns:** Sorting, Index Placement, Hashing Logic

---

# 🔥 PROBLEM

Return the **smallest positive integer** missing from the array.

Example:

```
Input: [3,4,-1,1]
Output: 2
```

---

# -------------------------------------------

# 🟦 **APPROACH 1 — Sorting (O(n log n))**

A clean, simple approach using sorting.

### ✔ WHY

After sorting the array:

* Ignore negative numbers
* Track the smallest positive we expect (start from 1)
* If current number equals expected → expected++
* First mismatch = missing number

### ✔ WHAT

We just want to verify if 1,2,3,… appear in sorted order.

### ✔ HOW

* Sort
* Iterate
* Skip all ≤0
* Update expected positive if matched
* Return first missing

---

## **CODE — Sort + Scan (O(n log n))**

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int smallest = 1;

        for (int x : nums) {
            if (x < smallest) continue;  // ignore negatives, duplicates, and smaller numbers
            if (x == smallest) smallest++; // matched expected positive
        }

        return smallest;  // first missing positive
    }
};
```

---

# -------------------------------------------

# 🟩 **APPROACH 2 — Cyclic Sort / Index Placement (O(n))**

**Best solution** → linear time, constant space.

### ✔ WHY

Valid answer is always between **1 and n+1**.
So we place each number `x` at index `x-1` if possible.

After positioning:

```
index: 0 1 2 3
value: 1 2 3 4
```

* First place where nums[i] != i+1 → missing.
* If all correct → answer = n+1.

### ✔ WHAT

This is a form of **Cyclic Sort**:

> Move each number to its rightful position by swapping until
> every valid number 1..n is at index (x−1).

### ✔ HOW

1. Loop over array
2. If nums[i] is in valid range [1..n]
3. Try placing it at index = nums[i] - 1
4. Swap until correct
5. After placement, scan to find mismatch

---

## **CODE — Cyclic Sort Optimal (O(n))**

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        int i = 0;

        // Step 1: place each number in its correct index
        while (i < n) {
            if (nums[i] <= 0 || nums[i] > n) {
                i++;
                continue;               // ignore invalid values
            }

            int idx = nums[i] - 1;      // correct index for nums[i]

            if (nums[i] != nums[idx]) {
                swap(nums[i], nums[idx]); // place value in correct spot
            } else {
                i++;                     // already correct or duplicate
            }
        }

        // Step 2: find first missing positive
        for (i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }

        return n + 1; // all 1..n present
    }
};
```

---

# -------------------------------------------

# ⚙️ COMPLEXITY COMPARISON

| Approach    | Time       | Space    | Notes                  |
| ----------- | ---------- | -------- | ---------------------- |
| Sorting     | O(n log n) | O(1)     | Easy but slower        |
| Cyclic Sort | **O(n)**   | **O(1)** | Fastest + Most Logical |

---

# -------------------------------------------

# 📝 SUMMARY

* Sorting works but costs O(n log n)
* Cyclic Sort is the **intended optimal** solution
* Core idea: place each number at index (x−1)
* First mismatch → missing positive
* Handles negatives, duplicates, and big values naturally

---
