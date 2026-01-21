# 🧩 Subsets II (Handling Duplicates)

## 📌 Problem Statement

Given an integer array `nums` that may contain duplicates, return **all possible subsets (the power set)**.

The solution set **must not contain duplicate subsets**.

---

## 🔍 Key Observation

- Duplicate elements in `nums` can lead to duplicate subsets.
- We must ensure **each subset appears only once**.
- Sorting the array helps group duplicates together, making them easier to handle.

---

## 🧠 Approach Overview

We solve this problem using **backtracking**, with two different strategies:

1. **Generate all subsets → remove duplicates using a set**
2. **Avoid generating duplicate subsets in the first place (optimal)**

Both are correct. The second one is preferred in interviews.

---

## 🟠 Solution 1 — Using `set` to Remove Duplicates

### 💡 Idea

- Generate **all possible subsets** (including duplicates).
- Store them in a `set<vector<int>>` to automatically remove duplicates.
- Convert the set to a vector at the end.

---

### 🛠️ Algorithm

1. Sort the array to make duplicates identical in structure.
2. At each index:
   - Either include the current element
   - Or exclude it

3. When `idx == nums.size()`, insert the subset into a set.
4. Return all unique subsets from the set.

---

### 💻 Code

```cpp
class Solution {
private:
    set<vector<int>> sett;

    void sub(vector<int>& nums, vector<int> part, int idx) {
        if (idx == nums.size()) {
            sett.insert(part);
            return;
        }

        // include nums[idx]
        part.push_back(nums[idx]);
        sub(nums, part, idx + 1);

        // exclude nums[idx]
        part.pop_back();
        sub(nums, part, idx + 1);
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        sub(nums, {}, 0);
        return vector<vector<int>>(sett.begin(), sett.end());
    }
};
```

---

### ⏱️ Complexity

- **Time:** `O(2^n * log M)`
  (`log M` for set insertion)
- **Space:** `O(2^n)` (set + recursion stack)

---

### ⚠️ Drawbacks

- Extra memory due to `set`
- Slower because of ordered insertions
- Not ideal for interviews

---

### ✅ When to Use

- When correctness matters more than performance
- When learning recursion basics

---

## 🟢 Solution 2 — Skipping Duplicates During Backtracking (Optimal)

### 💡 Idea

- Avoid generating duplicate subsets **at the recursion level itself**.
- Use sorting + a condition to **skip duplicate elements**.
- No extra data structures needed.

---

### 🛠️ Algorithm

1. Sort the array.
2. Always add the current subset to the result.
3. Loop from `idx` to `n - 1`:
   - If `nums[i]` is the same as `nums[i-1]` **and `i > idx`**, skip it.

4. Pick `nums[i]`, recurse, then backtrack.

---

### 💻 Code

```cpp
class Solution {
private:
    vector<vector<int>> res;

    void sub(vector<int>& nums, vector<int> part, int idx) {
        res.push_back(part);

        for (int i = idx; i < nums.size(); i++) {
            // skip duplicates at the same recursion level
            if (i > idx && nums[i] == nums[i - 1]) continue;

            part.push_back(nums[i]);
            sub(nums, part, i + 1);
            part.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        sub(nums, {}, 0);
        return res;
    }
};
```

---

### ⏱️ Complexity

- **Time:** `O(2^n)`
- **Space:** `O(n)` (recursion stack, excluding output)

---

### ⭐ Why This Is Better

- No extra memory (`set` not used)
- Faster execution
- Clean and interview-preferred

---

## 🧠 Duplicate-Skip Logic Explained

```cpp
if (i > idx && nums[i] == nums[i - 1]) continue;
```

Meaning:

- Only skip duplicates **at the same recursion level**
- Allows duplicates to be used in deeper recursive calls
- Prevents identical subsets from being generated

---

## 🔎 Example

Input:

```
nums = [1,2,2]
```

Output:

```
[
 [],
 [1],
 [1,2],
 [1,2,2],
 [2],
 [2,2]
]
```

---

## 🔄 Comparison Summary

| Feature            | Solution 1 (set) | Solution 2 (skip duplicates) |
| ------------------ | ---------------- | ---------------------------- |
| Duplicate handling | After generation | During generation            |
| Extra memory       | High             | Low                          |
| Performance        | Slower           | Faster                       |
| Interview use      | ❌               | ✅                           |

---

## 🏁 Final Interview Line

> “We generate subsets using backtracking and skip duplicate elements at the same recursion level after sorting the array.”
