# Intuition

A sorted array always satisfies:

nums[i] \le nums[i+1]

for every adjacent pair.

If the array is rotated exactly once, then the sorted order can break at only one position.

Example:

```text id="u7cz9m"
3 4 5 1 2
```

Only one violation exists:

```text id="l2qp6v"
5 > 1
```

So the key observation is:

> A sorted and rotated array can contain at most one descending break.

---

# Approach

We count the number of positions where:

nums[i] > nums[(i+1)%n]

The modulo handles the circular connection between:

* last element
* first element

Cases:

### Valid Sorted Array

```text id="n4ax1r"
1 2 3 4
```

Only one circular break:

```text id="u0fv8k"
4 > 1
```

Count = 1 → valid.

---

### Valid Rotated Sorted Array

```text id="c9jd3s"
3 4 5 1 2
```

Only one break:

```text id="r5wt7y"
5 > 1
```

Count = 1 → valid.

---

### Invalid Array

```text id="g1mb4p"
3 1 4 2
```

Breaks:

```text id="x8qe2h"
3 > 1
4 > 2
```

Count = 2 → invalid.

---

# Complexity

* Time complexity:

```text id="p3zc6n"
O(n)
```

Single traversal of the array.

---

* Space complexity:

```text id="w7ya1d"
O(1)
```

No extra space used.

---

# Code

```cpp id="m6xt2q"
class Solution {
public:
    bool check(vector<int>& nums) {
        int cnt = 0;

        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i] > nums[i + 1]) {
                cnt++;
            }
        }

        if (nums[0] < nums[nums.size() - 1])
            cnt++;

        /*
            1. pure sorted
                nums = 1 2 3 4
                -> till 4 , cnt = 0, in last 1 < 4 => cnt++ = 1 still ok

            2. rotated sorted
                nums = 3 4 5 1 2
                -> (5,1) cnt = 1
                -> 3 < 2 no so cnt still 1 means rotated
            
            3. sorted with duplicate 
                nums = 1 1 1
                cnt = 0 but still according to problem sorted

            Allowed: cnt = 0 and 1
        */
        return cnt <= 1;
    }
};
```
