# Median of Two Sorted Arrays (C++)

## Problem

Given two **sorted arrays** `nums1` and `nums2`, find the **median** of the combined sorted array.

---

## 🔴 Brute Force Approach

### 💡 Idea

- Merge both arrays
- Sort the combined array
- Find median normally

### ⏱ Time & Space

- Time: `O((n+m) log(n+m))`
- Space: `O(n+m)`
- ❌ Not optimal for interviews

---

### ✅ Brute Force Code (C++)

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

        vector<int> combined;
        combined.reserve(nums1.size() + nums2.size());

        for (int x : nums1) combined.push_back(x);
        for (int x : nums2) combined.push_back(x);

        sort(combined.begin(), combined.end());

        int n = combined.size();
        if (n % 2 == 0)
            return (combined[n/2] + combined[n/2 - 1]) / 2.0;
        else
            return combined[n/2];
    }
};
```

---

## 🟢 Optimal Approach (Binary Search)

### 💡 Core Logic (MOST IMPORTANT)

We **do NOT merge arrays**.

We try to find a **partition** such that:

- Left side has exactly half elements
- All elements in left ≤ all elements in right

---

## ✂️ Partition Concept

```
A: [ ... Aleft | Aright ... ]
B: [ ... Bleft | Bright ... ]
```

### ✅ Valid partition condition:

```cpp
Aleft <= Bright && Bleft <= Aright
```

---

## 📐 Why `cut2 = (n1 + n2 + 1)/2 - cut1` ?

- Left side must contain:

```
(total + 1) / 2 elements
```

- `cut1` = elements taken from A
- `cut2` = remaining elements taken from B

So:

```
cut1 + cut2 = (n1 + n2 + 1)/2
cut2 = (n1 + n2 + 1)/2 - cut1
```

---

## 🧮 Median Formula Logic

### Case 1: Total elements ODD

Median = **largest element in left side**

```cpp
median = max(Aleft, Bleft)
```

---

### Case 2: Total elements EVEN

Median = average of:

- largest left
- smallest right

```cpp
median = (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0
```

---

## 🔁 Binary Search Movement

| Condition        | Meaning           | Move           |
| ---------------- | ----------------- | -------------- |
| `Aleft > Bright` | A se zyada liya   | `r = cut1 - 1` |
| `Bleft > Aright` | A se kam liya     | `l = cut1 + 1` |
| both false       | perfect partition | stop           |

---

## 🧪 Dry Run Example

```
A = [1, 3, 5]
B = [2, 4]
```

Total = 5
Left size = `(5 + 1)/2 = 3`

---

### Iteration 1

```
cut1 = 1
cut2 = 2
```

```
A: [1 | 3 5]
B: [2 4 | ]
```

```
Aleft = 1, Aright = 3
Bleft = 4, Bright = INF
```

❌ `Bleft > Aright` → move right

---

### Iteration 2

```
cut1 = 2
cut2 = 1
```

```
A: [1 3 | 5]
B: [2 | 4]
```

```
Aleft = 3, Aright = 5
Bleft = 2, Bright = 4
```

✅ Valid partition

Median (odd):

```
max(3,2) = 3
```

---

## ✅ Optimal C++ Code

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {

        if (A.size() > B.size())
            return findMedianSortedArrays(B, A);

        int n1 = A.size(), n2 = B.size();
        int l = 0, r = n1;

        while (l <= r) {
            int cut1 = (l + r) / 2;
            int cut2 = (n1 + n2 + 1) / 2 - cut1;

            int Aleft  = (cut1 == 0) ? INT_MIN : A[cut1 - 1];
            int Aright = (cut1 == n1) ? INT_MAX : A[cut1];

            int Bleft  = (cut2 == 0) ? INT_MIN : B[cut2 - 1];
            int Bright = (cut2 == n2) ? INT_MAX : B[cut2];

            if (Aleft <= Bright && Bleft <= Aright) {
                if ((n1 + n2) % 2 == 0)
                    return (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0;
                else
                    return max(Aleft, Bleft);
            }
            else if (Aleft > Bright)
                r = cut1 - 1;
            else
                l = cut1 + 1;
        }
        return 0.0;
    }
};
```

---

## 🧠 Final One-Line Intuition

> **We are not finding the median directly.
> We are finding a balanced partition.**

---

## 📌 Interview Tip

- First explain brute force
- Then say: _“We can optimize using binary search on partition.”_
- Draw the partition diagram ✨

---
