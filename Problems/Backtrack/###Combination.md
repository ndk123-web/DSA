# 📘 Combinations (n choose k) 

## 📌 Problem Summary

Given two integers `n` and `k`, return **all possible combinations of `k` numbers** chosen from the range `[1, n]`.

- Each number is used **at most once**
- Order of combinations does **not** matter
- Result should contain **all unique combinations**

---

## 💡 Intuition

Ye problem **Combination Sum II** ka simplified version hai:

- Numbers fixed hain → `1` to `n`
- Target sum nahi, balki **fixed length (`k`)** chahiye
- Har element **sirf ek baar** use hota hai

Isliye:

- Index hamesha **aage move karta hai (`i+1`)**
- Jab `part.size() == k` → valid combination

---

## 🔁 Recursive Strategy

At index `idx`:

- Try each number from `idx` to `n`
- Add current number to `part`
- Recurse for next index
- Backtrack

---

## 🧩 Algorithm

1. Generate numbers from `1` to `n`
2. Start backtracking with:
   - `idx = 0`
   - empty `part`

3. If `part.size() == k`:
   - Store it

4. Loop from `idx` to end:
   - Include current number
   - Recurse with `i + 1`
   - Backtrack

---

## 🧪 Dry Run

### Input

```
n = 4, k = 2
```

### Numbers

```
[1, 2, 3, 4]
```

### Recursive Tree (simplified)

```
[]
├── 1 → [1]
│   ├── 2 → [1,2] ✅
│   ├── 3 → [1,3] ✅
│   └── 4 → [1,4] ✅
├── 2 → [2]
│   ├── 3 → [2,3] ✅
│   └── 4 → [2,4] ✅
├── 3 → [3]
│   └── 4 → [3,4] ✅
└── 4 → [4] ❌ (size < k)
```

### Output

```
[[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
```

---

## 🧠 Why `i + 1`?

- Ensures each number is used **once**
- Prevents permutations like `[2,1]`
- Maintains increasing order → uniqueness guaranteed

---

## ⏱️ Time Complexity

```
O(C(n, k))
```

Number of combinations generated.

---

## 💾 Space Complexity

- Recursion stack: `O(k)`
- Output storage: `O(C(n, k))`

---

## ⚠️ Common Mistakes

- Using `i` instead of `i+1` (allows reuse)
- Forgetting base case `part.size() == k`
- Generating permutations instead of combinations
- Not backtracking properly

---

## 🧠 Optimization (Optional but Good)

You can prune recursion like this:

```cpp
for (int i = idx; i <= nums.size() - (k - part.size()); i++)
```

This avoids useless calls when remaining numbers are insufficient.

---

## 🧾 Final Code

```cpp
class Solution {
private:
    vector<vector<int>> res;

    void comb(vector<int>& nums, vector<int> part, int k, int idx) {
        if (part.size() == k) {
            res.push_back(part);
            return;
        }

        for (int i = idx; i < nums.size(); i++) {
            part.push_back(nums[i]);
            comb(nums, part, k, i + 1);
            part.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> nums(n);
        for (int i = 1; i <= n; i++)
            nums[i - 1] = i;

        comb(nums, {}, k, 0);
        return res;
    }
};
```

---

## ✅ Takeaway

✔ Classic backtracking
✔ Clean index control
✔ No duplicates
✔ Interview-ready solution

Agar interviewer bole:

> “Explain your approach”

Tum confidently bol sakte ho:

> “I generate combinations using backtracking by fixing the length and advancing the index to avoid reuse.”
