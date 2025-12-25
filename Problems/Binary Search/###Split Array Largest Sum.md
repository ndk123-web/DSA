# 📌 Split Array Largest Sum — Deep Explanation

## Problem Statement (Simple Words)

You are given:

- An integer array `nums`
- An integer `k`

You must split `nums` into **k or fewer contiguous subarrays** such that:

- Each element belongs to exactly one subarray
- Order is preserved (contiguous)
- The **largest subarray sum** is as **small as possible**

👉 Return that **minimum possible largest subarray sum**.

---

## 🚀 Final Code

```cpp
class Solution {
private:
    bool canSplit(vector<int>& nums, int largest , int k) {
        int subarray = 1, currsum = 0;

        for (auto& num : nums) {
            currsum += num;

            if (currsum > largest) {
                subarray++;
                if (subarray > k) return false;
                currsum = num;
            }
        }
        return true;
    }

public:
    int splitArray(vector<int>& nums, int k) {
        int l = *max_element(nums.begin(), nums.end());
        int r = accumulate(nums.begin(), nums.end(), 0);
        int res = r;

        while (l <= r) {
            int m = l + (r - l) / 2;

            if (canSplit(nums, m, k)) {
                res = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return res;
    }
};
```

---

## 🧠 Core Idea (Very Important)

We are **NOT deciding where to split the array**.

We are answering this question instead:

> “What is the **smallest possible value** of the **largest subarray sum** such that the array can be split into **at most `k` subarrays**?”

That value is what we binary-search.

---

## 🔍 Why Binary Search Works

### Search Space

- **Minimum (`l`)** = `max(nums)`

  - Because a subarray must contain at least one element

- **Maximum (`r`)** = `sum(nums)`

  - One subarray containing everything

### Monotonic Property

If a value `X` **works**, then **any value > X also works**.
If a value `X` **fails**, then **any value < X also fails**.

👉 This monotonic behavior allows **binary search on the answer**.

---

## 🔑 Meaning of `m` (mid)

```cpp
int m = l + (r - l) / 2;
```

`m` represents:

> “Assume the **largest allowed subarray sum = m**
> Can we split the array into ≤ k subarrays under this restriction?”

---

## 🧪 What `canSplit()` Actually Does

```cpp
bool canSplit(nums, largest, k)
```

### Purpose

Checks whether:

- Every subarray sum can be kept **≤ largest**
- Total subarrays used **≤ k**

### Logic

- Traverse array left to right
- Keep adding elements to current subarray
- If sum exceeds `largest`, **forced split**
- Count how many subarrays are needed

If subarrays > k → ❌ not possible
Else → ✅ possible

---

## 🧾 Dry Run (Step-by-Step)

### Input

```
nums = [1, 0, 2, 3, 5]
k = 4
```

### Initial Values

```
l = max(nums) = 5
r = sum(nums) = 11
res = 11
```

---

### 🔁 Iteration 1

```
m = (5 + 11) / 2 = 8
```

#### canSplit(nums, 8, 4)

| Step | Current Subarray | Sum   |
| ---- | ---------------- | ----- |
| 1    | [1,0,2,3]        | 6     |
| 2    | +5 → 11 ❌       | split |
|      | [5]              | 5     |

Subarrays = 2 ≤ 4 → ✅ true

```
res = 8
r = 7
```

---

### 🔁 Iteration 2

```
m = (5 + 7) / 2 = 6
```

#### canSplit(nums, 6, 4)

| Subarrays |     |
| --------- | --- |
| [1,0,2,3] | 6   |
| [5]       | 5   |

Subarrays = 2 ≤ 4 → ✅ true

```
res = 6
r = 5
```

---

### 🔁 Iteration 3

```
m = (5 + 5) / 2 = 5
```

#### canSplit(nums, 5, 4)

| Subarrays |     |
| --------- | --- |
| [1,0,2]   | 3   |
| [3]       | 3   |
| [5]       | 5   |

Subarrays = 3 ≤ 4 → ✅ true

```
res = 5
r = 4
```

---

### ❌ Loop Ends (`l > r`)

### ✅ Final Answer

```
return res = 5
```

---

## 📌 Edge Cases

### 1️⃣ `k = 1`

```cpp
nums = [2,3,4]
```

Only one subarray allowed → answer = sum(nums)

---

### 2️⃣ `k = n`

```cpp
nums = [2,3,4]
```

Each element its own subarray → answer = max(nums)

---

### 3️⃣ Single Element

```cpp
nums = [10], k = 5
```

Answer = 10

---

### 4️⃣ All Zeros

```cpp
nums = [0,0,0], k = 2
```

Answer = 0

---

## 🧠 One-Line Summary (Remember This)

> **We binary search the minimum possible maximum subarray sum,
> and use greedy splitting to check if that value is feasible.**
