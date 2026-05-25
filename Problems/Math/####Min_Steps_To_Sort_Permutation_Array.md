Absolutely. Your code has a nice observation-based approach. Here’s a clean LeetCode-style writeup for it.

---

# Intuition

The target array after all operations must become:

```text
0,1,2,3,...,n-1
```

We are allowed only two operations:

* **Left circular shift**
* **Reverse entire array**

So instead of simulating every possible operation, we can first ask:

### What kind of arrays can actually be converted?

After trying a few dry runs, an important pattern appears:

* The array must be a **circular increasing permutation**, or
* a **circular decreasing permutation**

If it is neither, then it is impossible to sort using only these operations.

---

## Observation 1 — Circular Increasing

Example:

```text
2 3 0 1
```

This follows:

```text
2 → 3 → 0 → 1
(+1 mod n)
```

Two possible ways:

### Path A — only left shifts

```text
2 3 0 1
→ 3 0 1 2
→ 0 1 2 3
```

Operations:

```text
position of 0
```

---

### Path B — reverse + shifts + reverse

```text
2 3 0 1
→ 1 0 3 2   (reverse)
→ ...
→ 3 2 1 0
→ 0 1 2 3   (reverse)
```

Cost:

```text
2 + (n - positionOfZero)
```

---

# Observation 2 — Circular Decreasing

Example:

```text
2 1 0 3
```

This follows:

```text
2 → 1 → 0 → 3
(-1 mod n)
```

Again two possible paths:

---

### Path A — shifts then reverse

```text
2 1 0 3
→ 1 0 3 2
→ 0 3 2 1
→ reverse
→ 0 1 2 3
```

Cost:

```text
(positionOfZero + 1) + 1
```

---

### Path B — reverse then shifts

```text
2 1 0 3
→ 3 0 1 2   (reverse)
→ 0 1 2 3
```

Cost:

```text
1 + (n - 1 - positionOfZero)
```

---

Then we simply take the minimum among all valid paths.

---

# Approach

1. Find index of `0`.
2. Check whether array is:

   * circular increasing
   * circular decreasing
3. If neither → return `-1`
4. If increasing:

   * compute both possible costs
5. If decreasing:

   * compute both possible costs
6. Return minimum

---

# Complexity

* **Time complexity:** `O(n)`

We traverse the array a constant number of times.

---

* **Space complexity:** `O(1)`

Only variables are used.

---

# Code

```cpp []
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        bool isAscending = true;
        bool isDescending = true;

        int posOfZero = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                posOfZero = i;
                break;
            }
        }

        // Check circular increasing
        for (int i = 0; i < n; i++) {
            if ((nums[i] + 1) % n != nums[(i + 1) % n]) {
                isAscending = false;
                break;
            }
        }

        // Check circular decreasing
        for (int i = 0; i < n; i++) {
            if (((nums[i] - 1) + n) % n != nums[(i + 1) % n]) {
                isDescending = false;
                break;
            }
        }

        if (!isAscending && !isDescending) {
            return -1;
        }

        int res = INT_MAX;

        /*
            Increasing example:
            2 3 0 1

            Path 1:
            left shifts only -> cost = posOfZero

            Path 2:
            reverse + shifts + reverse
            cost = 2 + (n - posOfZero)

            --------------------------------

            Decreasing example:
            2 1 0 3

            Path 1:
            shifts + reverse
            cost = posOfZero + 1 + 1

            Path 2:
            reverse + shifts
            cost = 1 + (n - 1 - posOfZero)
        */

        if (isAscending) {
            res = min(res, posOfZero);
            res = min(res, 2 + (n - posOfZero));
        }

        if (isDescending) {
            res = min(res, posOfZero + 2);
            res = min(res, 1 + (n - 1 - posOfZero));
        }

        return res;
    }
};
```
