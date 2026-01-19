# 📘 Subsets

## 📌 Problem Summary

Given an integer array `nums`, return **all possible subsets** (the power set).

- Subset may be empty
- Order does not matter
- Total subsets = `2ⁿ`

---

## 💡 Intuition

Har element ke paas sirf **2 choices** hoti hain:

1. Include the element
2. Exclude the element

Is binary decision se recursion naturally ban jaata hai.
Jaise hi hum array ke end tak pahunchte hain, jo bhi elements choose kiye gaye hain — wahi ek valid subset hai.

---

## 🔁 Recursive Strategy (Include / Exclude)

At index `idx`:

- **Include `nums[idx]`** → add to `part`
- **Exclude `nums[idx]`** → do nothing

Repeat until `idx == nums.size()`.

---

## 🧩 Solution 1: Class-Level `part` Vector

### 🧠 Idea

- `part` ko class member bana diya
- Recursion ke dauraan directly modify hota hai
- Base case pe `res` mein push

### ✅ Code

```cpp
class Solution {
private:
    vector<vector<int>> res;
    vector<int> part;

    void subset(int idx, vector<int>& nums) {
        if (idx == nums.size()) {
            res.push_back(part);
            return;
        }

        part.push_back(nums[idx]);
        subset(idx + 1, nums);

        part.pop_back();
        subset(idx + 1, nums);
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        subset(0, nums);
        return res;
    }
};
```

### 👍 Pros

- Code short aur clean
- Parameter kam pass hote hain
- Easy to read

### 👎 Cons

- Uses shared mutable state
- Not thread-safe
- Debugging thoda tricky ho sakta hai

---

## 🧩 Solution 2: Passing `part` as Parameter

### 🧠 Idea

- `part` ko recursion ke through pass kiya
- Function becomes **pure**
- No hidden side effects

### ✅ Code

```cpp
class Solution {
private:
    vector<vector<int>> res;

    void subset(int idx, vector<int>& nums, vector<int>& part) {
        if (idx == nums.size()) {
            res.push_back(part);
            return;
        }

        part.push_back(nums[idx]);
        subset(idx + 1, nums, part);

        part.pop_back();
        subset(idx + 1, nums, part);
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> part;
        subset(0, nums, part);
        return res;
    }
};
```

### 👍 Pros

- No global / class state
- Safer design
- Interviewers prefer this
- Easier to reason about

### 👎 Cons

- Slightly more verbose
- Extra parameter in recursion

---

## 🧪 Dry Run Example

### Input

```
nums = [1, 2]
```

### Recursive Tree

```
idx=0, part={}
├── include 1 → {1}
│   ├── include 2 → {1,2}
│   └── exclude 2 → {1}
└── exclude 1 → {}
    ├── include 2 → {2}
    └── exclude 2 → {}
```

### Output

```
[[], [1], [2], [1,2]]
```

---

## ⏱️ Time Complexity

```
O(2ⁿ)
```

Each element has 2 choices → total subsets.

---

## 💾 Space Complexity

### Auxiliary Space (Recursion)

```
O(n)
```

### Output Space

```
O(n × 2ⁿ)
```

Because every subset is stored.

---

## ⚠️ Common Mistakes

- Vector copy inside recursion
- Forgetting empty subset
- Modifying `part` without backtracking
- Using both index + slicing together

---

## 🧠 Which Solution Should You Use?

| Scenario              | Recommended   |
| --------------------- | ------------- |
| LeetCode / Interviews | ✅ Solution 2 |
| Quick CP coding       | Solution 1    |
| Production code       | Solution 2    |
| Learning recursion    | Solution 2    |

---

## ✅ Final Takeaway

> **Both solutions are correct.**
> But **passing `part` as a parameter** shows better software design and stronger fundamentals.

If an interviewer asks:

> “Which one do you prefer and why?”

Your answer should be:

> “The second one — because it avoids shared state and is easier to reason about.”
