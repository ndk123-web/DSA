# 📘 Combination Sum

## 📌 Problem Summary

Given an array of **distinct integers** `candidates` and a target integer `target`, return **all unique combinations** of candidates where the chosen numbers sum to `target`.

- A number may be chosen **unlimited times**
- Order of combinations does **not** matter
- Each combination must sum exactly to `target`

---

## 💡 Intuition

Ye problem **subset jaisi nahi**, balki **combination** problem hai.

Key observations:

- Har number ko **multiple times use kar sakte hain**
- Isliye jab kisi number ko choose karo:
  - next call mein **same index** se start karte hain

- Agar sum target se bada ho gaya → wahi path chhod do

Hum **remaining sum (`remain`)** track karte hain:

- `remain == 0` → valid combination
- `remain < 0` → invalid path

---

## 🔁 Recursive Strategy (Backtracking)

At any recursion call:

- Loop from `idx` to end
- Choose `nums[i]`
- Reduce remaining sum
- Backtrack after recursion

---

## 🧩 Algorithm

1. Start recursion with:
   - `remain = target`
   - `idx = 0`

2. If `remain == 0`:
   - Store current combination

3. If `remain < 0`:
   - Stop exploring this path

4. For each index `i ≥ idx`:
   - Include `nums[i]`
   - Recurse with updated `remain`
   - Backtrack

---

## 🧪 Dry Run

### Input

```
candidates = [2,3,6,7]
target = 7
```

### Recursive Tree (simplified)

```
[]
├── 2 → remain=5
│   ├── 2 → remain=3
│   │   ├── 2 → remain=1 ❌
│   │   └── 3 → remain=0 ✅ [2,2,3]
│   └── 3 → remain=2 ❌
├── 3 → remain=4 ❌
├── 6 → remain=1 ❌
└── 7 → remain=0 ✅ [7]
```

### Output

```
[[2,2,3], [7]]
```

---

## 🧠 Why This Works

- `idx` ensures combinations stay **unique**
- Reusing same index allows **unlimited usage**
- Backtracking removes last choice cleanly
- Pruning (`remain < 0`) avoids useless recursion

---

## ⏱️ Time Complexity

```
O(2^target)
```

(Not exact, but exponential in nature due to recursion tree)

---

## 💾 Space Complexity

- **Recursion stack**: `O(target)`
- **Output storage**: depends on number of valid combinations

---

## ⚠️ Common Mistakes

- Passing `i+1` instead of `i` (breaks reuse rule)
- Mixing `currSum` and `remain`
- Forgetting backtracking (`pop_back`)
- Allowing duplicates by resetting `idx`

---

## 🧠 Comparison with Subset Problem

| Feature       | Subset      | Combination Sum |
| ------------- | ----------- | --------------- |
| Reuse element | ❌          | ✅              |
| Order matters | ❌          | ❌              |
| Index move    | `idx+1`     | `i`             |
| Goal          | All subsets | Target sum      |

---

## 🧾 Final Code

```cpp
class Solution {
private:
    vector<vector<int>> res;

    void comb(vector<int>& nums, int remain, int idx, vector<int>& part) {
        if (remain < 0) return;

        if (remain == 0) {
            res.push_back(part);
            return;
        }

        for (int i = idx; i < nums.size(); i++) {
            part.push_back(nums[i]);
            comb(nums, remain - nums[i], i, part);
            part.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> part;
        comb(candidates, target, 0, part);
        return res;
    }
};
```

---

## ✅ Takeaway

✔ Clean backtracking
✔ Correct pruning
✔ No duplicates
✔ Interview-ready

Agar interviewer bole:

> “Explain your approach”

Tum seedha bol sakte ho:

> “I use backtracking with remaining sum and index control to generate unique combinations efficiently.”
