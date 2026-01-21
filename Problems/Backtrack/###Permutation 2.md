# 🔁 Permutations II (Unique Permutations)

## 📌 Problem Statement

## Given a collection of numbers `nums` that **may contain duplicates**, return **all unique permutations**.

## 🔍 Key Observations

- Duplicate numbers can generate duplicate permutations.
- Each permutation must appear **exactly once**.
- Sorting or frequency tracking is required to handle duplicates correctly.

---

## 🧠 Approach Overview

We solve this problem using **backtracking**, with three standard strategies:

1. **Pick & Remove (extra array, easiest to reason)**
2. **In-place Swap with duplicate pruning (optimal, tricky)**
3. **Frequency Map (count-based DFS, cleanest for duplicates)**

All three are correct.
The **third approach is the most elegant** for duplicate-heavy inputs.

---

## 🟠 Solution 1 — Pick & Remove (Intuitive Approach)

### 💡 Idea

- At each step, pick one number.
- Remove it from the remaining list.
- Skip duplicates using sorting.
- Build permutations incrementally.

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
- **Space:** `O(n!)` (array copies + recursion)

---

### ✅ Pros / ❌ Cons

✅ Very easy to understand
❌ Extra memory and slower due to copying arrays

---

## 🟢 Solution 2 — In-Place Swap with Duplicate Pruning

### 💡 Core Idea

- We **fix positions one by one**.
- At each position, a value is allowed **only once**.
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

### 🔍 Duplicate-Skip Logic Explained

```cpp
if (j > i && nums[j] == nums[i]) continue;
```

Meaning:

- At position `i`, if a value has already been placed once,
  **do not place the same value again**.
- Prevents duplicate permutations at the same recursion depth.

---

## 🔵 Solution 3 — Frequency Map / Count-Based DFS (Best for Duplicates)

### 💡 Core Idea

- Count how many times each number appears.
- Build permutations using only available counts.
- A number can be used **only if its count > 0**.
- This guarantees uniqueness naturally.

---

### 🛠️ Algorithm

1. Build a frequency map of all numbers.
2. At each step:
   - Try all numbers whose count is greater than zero.

3. Choose a number:
   - Decrease its count.
   - Add it to the current permutation.

4. Backtrack by restoring the count.

---

### 💻 Code

```cpp
class Solution {
private:
    vector<vector<int>> res;
    unordered_map<int,int> mapp;

    void perm(int n, vector<int>& part) {
        if (part.size() == n) {
            res.push_back(part);
            return;
        }

        for (auto &p : mapp) {
            if (p.second > 0) {
                part.push_back(p.first);
                p.second--;

                perm(n, part);

                p.second++;
                part.pop_back();
            }
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        for (int num : nums) mapp[num]++;
        vector<int> part;
        perm(nums.size(), part);
        return res;
    }
};
```

---

### ⏱️ Complexity

- **Time:** `O(n × n!)`
- **Space:** `O(n)` (recursion stack + map)

---

### ⭐ Why This Method Is Excellent

- No sorting required
- No swapping
- No duplicate checks
- Very clean DFS logic
- Handles heavy duplicates efficiently

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

## 🔄 Comparison Summary

| Aspect               | Pick & Remove | Swap-Based | Frequency Map |
| -------------------- | ------------- | ---------- | ------------- |
| Extra memory         | High          | Low        | Low           |
| Speed                | Medium        | Fast       | Fast          |
| Readability          | High          | Medium     | ⭐⭐⭐        |
| Duplicate handling   | Skip          | Prune      | Natural       |
| Interview preference | ⚠️            | ✅         | ⭐⭐⭐        |

---

## 🏁 Interview One-Liner

> “We generate unique permutations using backtracking, either by fixing positions with duplicate pruning or by tracking element frequencies to avoid duplicates entirely.”
