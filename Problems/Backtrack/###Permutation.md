# 🔁 Permutations 

## 📌 Problem

Given an array `nums` of **distinct integers**, return **all possible permutations**.

---

## 🧠 Overview

Is problem ko hum **do tarike se** solve kar sakte hain:

1. **Pick & Remove (Extra Array)**
2. **In-Place Swap (Optimal Backtracking)**

Dono backtracking use karte hain, difference sirf **state manage karne ka** hai.

---

## METHOD 1️⃣ — Pick & Remove (Your First Solution)

### 🧠 Intuition

- Ek element choose karo
- Usko current permutation (`part`) mein daalo
- Baaki elements ke saath recursion
- Jab kuch bache hi nahi → permutation ready

### 🛠️ Approach

- `nums` → remaining elements
- `part` → current permutation being built
- Har recursion mein:
  - ek element uthao
  - baaki elements ka naya array banao
  - DFS call

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
            part.push_back(nums[i]);

            vector<int> newnums(nums.begin(), nums.end());
            newnums.erase(newnums.begin() + i);

            perm(newnums, part);
            part.pop_back();
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        perm(nums, {});
        return res;
    }
};
```

### ⏱️ Complexity

- **Time:** `O(n × n!)`
- **Space:** `O(n!)` (array copies + recursion)

### ⚠️ Note

- Logic easy hai
- But har call mein **naya vector + erase**
- Large input mein slow

---

## METHOD 2️⃣ — In-Place Swap (Your Second Solution)

### 🧠 Intuition

- Array ko todna nahi
- **Positions ko fix karte jao**
- Har position par baaki elements ko swap karke try karo
- Kaam ho jaaye → swap back (undo)

### 🛠️ Approach

- `idx` → current position to be fixed
- Index `idx` se pehle ke elements **final** ho chuke hain
- `i` loop karta hai possible candidates par

### 💻 Code

```cpp
class Solution {
    vector<vector<int>> res;

public:
    vector<vector<int>> permute(vector<int>& nums) {
        backtrack(nums, 0);
        return res;
    }

    void backtrack(vector<int>& nums, int idx) {
        if (idx == nums.size()) {
            res.push_back(nums);
            return;
        }

        for (int i = idx; i < nums.size(); i++) {
            swap(nums[idx], nums[i]);
            backtrack(nums, idx + 1);
            swap(nums[idx], nums[i]); // backtrack
        }
    }
};
```

### ⏱️ Complexity

- **Time:** `O(n × n!)`
- **Space:** `O(n)` (recursion stack)

### ⭐ Why This Is Better

- No extra arrays
- In-place operations
- Most preferred in interviews

---

## 🔍 Key Difference (Side-by-Side)

| Aspect               | Pick & Remove        | In-Place Swap |
| -------------------- | -------------------- | ------------- |
| Array handling       | New array every call | Same array    |
| Extra space          | High                 | Low           |
| Performance          | Slower               | Faster        |
| Interview preference | ❌                   | ✅            |

---

## 🧠 One-Line Interview Explanation

**Method 1:**

> “We build permutations by choosing an element and recursively permuting the remaining elements.”

**Method 2:**

> “We fix positions one by one using in-place swapping and backtracking.”
