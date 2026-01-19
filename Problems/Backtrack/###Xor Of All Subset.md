# 🧠 Subset XOR Sum

## 📌 Problem Summary

Given an integer array `nums`, return the **sum of XOR of all possible subsets** of the array.

- Subset can be empty
- XOR of empty subset = `0`

---

## 💡 Intuition

Subset ka concept simple hai:

- Har element ke paas **2 choices** hote hain:
  - **Include**
  - **Exclude**

Isliye total subsets = `2ⁿ`.

Instead of:

- pehle saare subsets banana
- phir unka XOR calculate karna

👉 hum **recursion ke dauraan hi XOR calculate** kar sakte hain.

Har recursive call mein:

- current XOR value pass karte hain
- jab array khatam ho jaaye → us XOR ko answer mein add kar dete hain

📌 **No extra storage. No waste.**

---

## 🔁 Recursive Strategy

At index `idx`:

1. **Include `nums[idx]`** → `currXor ^ nums[idx]`
2. **Exclude `nums[idx]`** → `currXor` as it is

---

## 🧩 Algorithm

1. Start recursion from index `0`
2. Maintain `currXor`
3. When `idx == nums.size()`:
   - Add `currXor` to result

4. Explore both include & exclude paths

---

## 🧪 Dry Run

### Input

```
nums = [1, 3]
```

### Recursive Tree

```
Start: idx=0, currXor=0

Include 1 → idx=1, currXor=1
   Include 3 → idx=2, currXor=1^3=2  → add 2
   Exclude 3 → idx=2, currXor=1      → add 1

Exclude 1 → idx=1, currXor=0
   Include 3 → idx=2, currXor=3      → add 3
   Exclude 3 → idx=2, currXor=0      → add 0
```

### Subsets & XOR

| Subset | XOR |
| ------ | --- |
| {}     | 0   |
| {1}    | 1   |
| {3}    | 3   |
| {1,3}  | 2   |

### Final Answer

```
0 + 1 + 3 + 2 = 6
```

---

## 🧠 Key Insight

> **Each element participates in exactly `2^(n-1)` subsets**

So theoretically:

```
Answer = (nums[0] + nums[1] + ... + nums[n-1]) × 2^(n-1)
```

But recursion is clearer and safer for interviews.

---

## 🧪 Edge Cases

- Empty array → result = 0
- Single element → result = element
- All same numbers → XOR cancels correctly

---

## 🧾 Code (Final & Optimized)

```cpp
class Solution {
private:
    int result = 0;

    void dfs(int idx, vector<int>& nums, int currXor) {
        if (idx == nums.size()) {
            result += currXor;
            return;
        }

        // include
        dfs(idx + 1, nums, currXor ^ nums[idx]);

        // exclude
        dfs(idx + 1, nums, currXor);
    }

public:
    int subsetXORSum(vector<int>& nums) {
        dfs(0, nums, 0);
        return result;
    }
};
```

---

## ⏱️ Time Complexity

```
O(2ⁿ)
```

Each element has include/exclude choice.

---

## 💾 Space Complexity

```
O(n)
```

Recursion stack depth only.

---

## ❌ Common Mistakes

- Storing all subsets (unnecessary memory)
- Copying vectors in recursion
- Using XOR incorrectly across subsets
- Forgetting empty subset

---

## ✅ Takeaway

✔ Clean recursion
✔ No extra memory
✔ Interview-ready
✔ Competitive programming friendly
