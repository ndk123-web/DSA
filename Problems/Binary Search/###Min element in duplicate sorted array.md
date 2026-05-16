# Intuition

The array was originally sorted in increasing order, but then rotated at some pivot.

Example:

```txt id="lq4f8u"
Sorted:
1 2 3 4 5

Rotated:
4 5 1 2 3
```

The important observation is:

# One side of the array is always sorted.

We compare:

```txt id="q0k7n1"
nums[mid]
with
nums[high]
```

to determine where the minimum element lies.

However, duplicates make the problem tricky because sometimes:

```txt id="m5r2x9"
nums[mid] == nums[high]
```

In this case, we lose the ability to determine which side contains the minimum, so we safely shrink the search space by doing:

```cpp id="r8u3k5"
high--;
```

---

# Approach

We use Binary Search to reduce the search space.

Initialize:

```cpp id="z1p6v4"
low = 0
high = n-1
```

We continue searching while:

```cpp id="h3c8w7"
low < high
```

because once both pointers become equal, only one candidate remains, which must be the minimum.

---

## Case 1

```cpp id="x7n4q2"
nums[mid] < nums[high]
```

Example:

```txt id="d5m9u1"
3 4 5 1 2
      M   R
```

This means the right half is properly sorted, so the minimum must lie:

* at `mid`
* or somewhere on the left side

So we keep `mid` in the search space:

```cpp id="j6r2p8"
high = mid;
```

---

## Case 2

```cpp id="u4y8s3"
nums[mid] > nums[high]
```

Example:

```txt id="n1k5v9"
4 5 1 2 3
  M     R
```

This means the rotation point exists on the right side, so the minimum must be after `mid`.

Thus:

```cpp id="b9w4f6"
low = mid + 1;
```

---

## Case 3 (Duplicates)

```cpp id="f2q7m1"
nums[mid] == nums[high]
```

Example:

```txt id="p8x3n4"
10 1 10 10 10
      M     R
```

Here we cannot determine which side contains the minimum because duplicates destroy the ordering information.

But removing one duplicate from the right side is safe because:

* if `nums[high]` is not the minimum, removing it does not matter
* if it is the minimum, another equal value already exists at `mid`

So we shrink the search space safely:

```cpp id="t5v9k2"
high--;
```

---

# Why `while(low < high)` ?

We stop when:

```txt id="c7n4p6"
low == high
```

because at that point only one element remains in the search space, which must be the minimum.

Using:

```cpp id="m2x8w5"
while(low <= high)
```

with updates like:

```cpp id="k4q1r9"
high = mid
```

can lead to invalid states or infinite loops because `mid` is still kept inside the search space.

---

# Complexity

* Time complexity:

Average case:

```txt id="r6v2m8"
O(log n)
```

Worst case (many duplicates):

```txt id="w3k7p1"
O(n)
```

because duplicate cases may only reduce the search space by one element.

---

* Space complexity:

```txt id="j8m4x2"
O(1)
```

No extra space is used.

---

# Code

```cpp id="q5n8v3"
class Solution {
public:
    int findMin(vector<int>& nums) {

        int low = 0;
        int high = nums.size() - 1;

        if (high == 0)
            return nums[0];

        while (low < high) {

            int mid = low + (high - low) / 2;

            // minimum lies in left half including mid
            if (nums[mid] < nums[high]) {
                high = mid;
            }

            // minimum lies in right half
            else if (nums[mid] > nums[high]) {
                low = mid + 1;
            }

            // duplicates: cannot determine side safely
            else {
                high--;
            }
        }

        return nums[low];
    }
};
```
