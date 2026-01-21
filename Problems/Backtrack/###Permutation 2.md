# 🔁 Permutations II (Unique Permutations)

## 📌 Problem Statement

Given a collection of numbers `nums` that **may contain duplicates**, return **all unique permutations**.

---

## 🔍 Key Observation

- Duplicate numbers can produce duplicate permutations.
- We must ensure **each permutation appears only once**.
- Sorting is essential to detect duplicates.

---

## 🧠 Approach Overview

We solve this problem using **backtracking**, with two different strategies:

1. **Pick & Remove (extra array, easier to reason)**
2. **In-place Swap with duplicate pruning (optimal, tricky)**

Both are correct. The second one avoids extra memory.

---

## 🟠 Solution 1 — Pick & Remove (Your Intuitive Solution)

### 💡 Idea

- At each step, pick one number.
- Remove it from the remaining list.
- Skip duplicates using sorting.
- Build permutations step by step.

---

### 🛠️ Algorithm

1. Sort the array.
2. For each index `i`:
   - Skip `nums[i]` if it is the same as `nums[i-1]`.

3. Add `nums[i]` to the current permutation.
4. Recurse on the remaining elements.
5. Backtrack.

---

### 💻 Code

```cpp
class Solution {
private:
    vector<vector<int>> res;

    void perm(vector<int>& nums, vector<int> part) {
        if (nums.empty()) {
            res.push_back(part);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            part.push_back(nums[i]);

            vector<int> newnums(nums.begin(), nums.end());
            newnums.erase(newnums.begin() + i);

            perm(newnums, part);
            part.pop_back();
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        perm(nums, {});
        return res;
    }
};
```

---

### ⏱️ Complexity

- **Time:** `O(n × n!)`
- **Space:** `O(n!)` (due to array copying)

---

### ✅ Pros / ❌ Cons

✅ Easy to understand
❌ Extra memory and slower due to copying

---

## 🟢 Solution 2 — In-Place Swap with Duplicate Pruning

### 💡 Core Idea

- We **fix positions one by one**.
- At position `i`, we allow **each value only once**.
- Duplicate values are skipped **at the same recursion depth**.
- No extra arrays are created.

---

### 🛠️ Key Rule (Very Important)

> **Index `i` represents a POSITION, not an element.**
> At position `i`, we decide **which value can come here**.

---

### 🛠️ Algorithm

1. Sort the array.
2. Start fixing positions from index `0`.
3. For position `i`, try swapping it with indices `j = i → n-1`.
4. Skip a swap if the same value was already used at this position.
5. Recurse to fix the next position.
6. Restore the array after recursion.

---

### 💻 Code

```cpp
class Solution {
    vector<vector<int>> res;

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        dfs(0, nums);
        return res;
    }

    void dfs(int i, vector<int>& nums) {
        if (i == nums.size()) {
            res.push_back(nums);
            return;
        }

        for (int j = i; j < nums.size(); ++j) {
            if (j > i && nums[j] == nums[i]) continue;
            swap(nums[i], nums[j]);
            dfs(i + 1, nums);
        }

        // restore array state
        for (int j = nums.size() - 1; j > i; --j) {
            swap(nums[i], nums[j]);
        }
    }
};
```

---

## 🔍 Duplicate-Skip Logic Explained

```cpp
if (j > i && nums[j] == nums[i]) continue;
```

Meaning:

- At position `i`, if a value has already been placed once,
  **do not place the same value again**.
- Prevents duplicate permutations at the same recursion depth.

---

## 🧠 Example

Input:

```
nums = [1,1,2]
```

Output:

```
[
 [1,1,2],
 [1,2,1],
 [2,1,1]
]
```

---

## 🔄 Comparison

| Aspect               | Pick & Remove | Swap-Based |
| -------------------- | ------------- | ---------- |
| Extra memory         | High          | Low        |
| Speed                | Slower        | Faster     |
| Readability          | High          | Medium     |
| Interview preference | ⚠️            | ✅         |

---

## 🏁 Interview One-Liner

> “We generate permutations by fixing positions one by one and skip duplicate values at the same recursion depth after sorting.”
