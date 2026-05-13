# 303. Range Sum Query - Immutable

## Intuition

If every query asks:

```txt
sum from left to right
```

and we calculate it every time using loop:

```cpp
for(int i=left; i<=right; i++)
```

then each query becomes:

```txt
O(n)
```

which is expensive for many queries.

So instead of recalculating sums repeatedly, we preprocess cumulative sums once using:

# Prefix Sum

---

# What is Prefix Sum?

Prefix sum means:

```txt
prefix[i]
=
sum from index 0 to i
```

Example:

```txt
nums = [-2, 0, 3, -5, 2, -1]
```

Build prefix:

```txt
prefix[0] = -2
prefix[1] = -2 + 0 = -2
prefix[2] = -2 + 0 + 3 = 1
prefix[3] = 1 + (-5) = -4
prefix[4] = -4 + 2 = -2
prefix[5] = -2 + (-1) = -3
```

Final:

```txt
prefix = [-2, -2, 1, -4, -2, -3]
```

---

# Why Prefix Sum Works

Suppose we need:

```txt
sum from left to right
```

Example:

```txt
left = 2
right = 4
```

Wanted:

```txt
3 + (-5) + 2
= 0
```

Using prefix:

```txt
prefix[right]
=
sum from 0 to right
```

So:

```txt
prefix[4] = -2
```

But this includes unwanted left part:

```txt
-2 + 0
```

Remove it using:

```txt
prefix[left-1]
```

So:

```txt
answer
=
prefix[right] - prefix[left-1]
```

Example:

```txt
prefix[4] - prefix[1]
=
(-2) - (-2)
=
0
```

Correct.

---

# Important Edge Case

If:

```txt
left == 0
```

then there is no previous prefix.

So directly:

```txt
prefix[right]
```

Example:

```txt
sumRange(0,2)
=
-2 + 0 + 3
=
1
```

Directly:

```txt
prefix[2] = 1
```

---

# Visualization

```txt
nums:
[-2,  0,  3, -5,  2, -1]

prefix:
[-2, -2,  1, -4, -2, -3]
```

Suppose:

```txt
sumRange(2,4)
```

We use:

```txt
prefix[4] - prefix[1]

(-2) - (-2)
= 0
```

Meaning:

```txt
(0 -> 4)
minus
(0 -> 1)
=
(2 -> 4)
```

---

# Core Concept

Prefix sum converts:

```txt
Repeated range sum queries
```

from:

```txt
O(n)
```

to:

```txt
O(1)
```

after preprocessing.

---

# Complexity

## Constructor

Building prefix array:

```txt
O(n)
```

---

## sumRange()

Constant time lookup:

```txt
O(1)
```

---

# Code

```cpp
class NumArray {
public:
    vector<int> prefix;

    NumArray(vector<int>& nums) {
        int pSum = 0;

        for (int i = 0; i < nums.size(); i++) {
            pSum += nums[i];
            prefix.push_back(pSum);
        }
    }

    int sumRange(int left, int right) {

        // if range starts from 0
        if (left == 0)
            return prefix[right];

        // remove unwanted left portion
        return prefix[right] - prefix[left - 1];
    }
};
```

---

# Pattern Recognition

Whenever you see:

```txt
multiple range sum queries
```

think:

# Prefix Sum

Common signals:

* sum from L to R
* many queries
* immutable array
* cumulative frequency
* running totals

---

# Key Formula

For any range:

```txt
sum(L,R)
=
prefix[R] - prefix[L-1]
```

provided:

```txt
L > 0
```
