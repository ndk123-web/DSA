
# Intuition

At first glance, for every index `i`, we can try to find the farthest `j` such that:

```text
i < j
nums[i] <= nums[j]
```

and maximize:

```text
j - i
```

But brute force checks every pair, which becomes `O(n²)` and gives TLE.

---

## Key Observation

For a valid ramp `(i, j)`:

```text
nums[i] <= nums[j]
```

If there exists an earlier index `k < i` where:

```text
nums[k] <= nums[i]
```

then `k` always gives a better or equal width than `i`.

So `i` is useful only when it is the **smallest value seen so far from the left**.

That leads to storing only candidate left boundaries.

---

# Approach

## 1. Build Monotonic Decreasing Stack

Traverse from left to right.

Store indices whose values are strictly decreasing:

```text
nums[stack[0]] > nums[stack[1]] > nums[stack[2]]
```

These are our possible left boundaries.

Example:

```text
[6,0,8,2,1,5]
```

Stack stores:

```text
[0,1]
```

because:

```text
6 -> first minimum
0 -> smaller than 6
```

Other elements are ignored since they can’t create a wider ramp than an earlier smaller value.

---

## 2. Traverse from Right to Left

Now check each `j` from rightmost side.

If:

```text
nums[stack.top()] <= nums[j]
```

then we found a valid ramp.

Width:

```text
j - stack.top()
```

Update answer and pop.

---

## Why pop?

Because while scanning from right to left:

the first `j` that satisfies a stack index `i` is already the **farthest possible right boundary** for that `i`.

So once used:

```text
i will never produce a larger width again
```

Hence we pop it permanently.

---

# Complexity

### Time complexity:

```text
O(n)
```

Each index:

* pushed once
* popped once

---

### Space complexity:

```text
O(n)
```

for the monotonic stack.

---

# Code

```cpp
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        stack<int> decStack;
        int n = nums.size();

        // Step 1: Build decreasing stack of candidate left indices
        for (int i = 0; i < n; i++) {
            if (!decStack.empty() && nums[decStack.top()] >= nums[i]) {
                decStack.push(i);
                continue;
            } 
            else if (decStack.empty()) {
                decStack.push(i);
            }
        }

        // Step 2: Traverse from right and find maximum width
        int res = 0;

        for (int i = n - 1; i >= 0; i--) {
            while (!decStack.empty() &&
                   nums[decStack.top()] <= nums[i]) {
                res = max(res, i - decStack.top());
                decStack.pop();
            }
        }

        return res;
    }
};
```
