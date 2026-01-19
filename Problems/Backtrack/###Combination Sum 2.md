# 📘 Combination Sum II

## 📌 Problem Summary

Given a collection of candidate numbers `candidates` (which may contain duplicates) and a target number `target`, return **all unique combinations** where the chosen numbers sum to `target`.

### Rules:

- Each number may be used **at most once**
- Input may contain **duplicate numbers**
- Output must not contain **duplicate combinations**
- Order of combinations does not matter

---

## 💡 Intuition

Ye problem **backtracking + duplicate handling** ka perfect example hai.

Key ideas:

- **Each element can be used only once** → next recursive call starts from `i + 1`
- Input ko pehle **sort** karte hain
- Same recursion level pe **duplicate values skip** karte hain
- `remain` track karta hai kitna sum abhi banana baaki hai

---

## 🔁 Recursive Strategy

At each step:

1. Loop from index `idx` to end
2. Choose `nums[i]`
3. Reduce `remain`
4. Move to `i + 1` (reuse not allowed)
5. Backtrack

---

## 🧩 Algorithm

1. Sort the input array
2. Start recursion with:
   - `remain = target`
   - `idx = 0`

3. If `remain == 0`:
   - Store the current combination

4. If `remain < 0`:
   - Stop exploring that path

5. Skip duplicates using:

   ```cpp
   if (i > idx && nums[i] == nums[i-1]) continue;
   ```

---

## 🧪 Dry Run

### Input

```
candidates = [10,1,2,7,6,1,5]
target = 8
```

### After Sorting

```
[1,1,2,5,6,7,10]
```

### Valid Combinations

```
[1,1,6]
[1,2,5]
[1,7]
[2,6]
```

---

## 🧠 Why `i + 1`?

Because:

- Each element can be used **only once**
- `i + 1` ensures the same index is not reused
- Prevents combinations like `[1(index0), 1(index0)]`

---

## 🧠 Why Skip Duplicates?

```cpp
if (i > idx && nums[i] == nums[i-1]) continue;
```

- Skips duplicate values **only at the same recursion level**
- Allows same value in deeper levels if coming from different indices
- Prevents duplicate combinations in result

---

## ⏱️ Time Complexity

```
O(2ⁿ)
```

Worst case: exploring all subsets.

---

## 💾 Space Complexity

- Recursion stack: `O(n)`
- Result storage: depends on number of valid combinations

---

## ⚠️ Common Mistakes

- Forgetting to sort input
- Using `i` instead of `i+1`
- Not skipping duplicates correctly
- Using global mutable state incorrectly

---

## 🧠 Comparison with Similar Problems

| Problem            | Reuse Allowed | Duplicates in Input | Next Index |
| ------------------ | ------------- | ------------------- | ---------- |
| Combination Sum    | ✅            | ❌                  | `i`        |
| Combination Sum II | ❌            | ✅                  | `i+1`      |
| Subsets II         | ❌            | ✅                  | `idx+1`    |

---

## 🧾 Final Code

```cpp
class Solution {
private:
    vector<vector<int>> res;

    void comb(vector<int>& nums, int remain, vector<int>& part, int idx) {
        if (remain < 0) return;

        if (remain == 0) {
            res.push_back(part);
            return;
        }

        for (int i = idx; i < nums.size(); i++) {
            if (i > idx && nums[i] == nums[i - 1]) continue;

            part.push_back(nums[i]);
            comb(nums, remain - nums[i], part, i + 1);
            part.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> part;
        sort(candidates.begin(), candidates.end());
        comb(candidates, target, part, 0);
        return res;
    }
};
```

---

## ✅ Takeaway

✔ Correct backtracking
✔ Proper duplicate handling
✔ No unnecessary memory
✔ Interview-ready solution

Agar interviewer bole:

> “Explain how you avoid duplicates”

Tum confidently bol sakte ho:

> “I sort the array and skip duplicate values at the same recursion level.”
