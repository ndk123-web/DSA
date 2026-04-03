# Jump Game – Greedy (Reachability Based)

## Problem Statement

Given an array `nums` where each element represents your maximum jump length at that position, determine if you can reach the last index starting from the first index.

---

## Intuition

This is **not a path selection problem**, but a **reachability problem**.

At any index, the question is:

> “Can I even reach this index?”

If yes, then:

> “From here, how far can I extend my reach?”

---

## Key Idea

Maintain a variable:

```text
maxReach = farthest index reachable so far
```

At each index `i`:

1. If `i > maxReach` → this index is unreachable → return `false`
2. Update:

   ```text
   maxReach = max(maxReach, i + nums[i])
   ```
3. If `maxReach >= n - 1` → last index reachable → return `true`

---

## Approach

* Traverse the array from left to right
* Keep expanding the reachable boundary
* Stop early if:

  * You reach the end
  * You encounter an unreachable index

---

## Code

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;
        int n = nums.size();

        for (int i = 0 ; i < n; i++) {

            // if already can reach last index
            if (maxReach >= n - 1) return true;

            // if current index is not reachable
            if (i > maxReach) return false;

            // if current jump reaches end
            if (i + nums[i] >= n - 1) return true;

            // update maximum reachable index
            maxReach = max(maxReach, i + nums[i]);
        }

        return false;
    }
};
```

---

## Example

### Input

```text
nums = [1, 0, 1, 0]
```

### Dry Run

| i | nums[i] | maxReach | Explanation                  |
| - | ------- | -------- | ---------------------------- |
| 0 | 1       | 1        | Can reach index 1            |
| 1 | 0       | 1        | Stuck here                   |
| 2 | —       | —        | `i > maxReach` → unreachable |

### Output

```text
false
```

---

## Edge Cases

1. **Single element**

   ```text
   [0] → true
   ```

2. **Starting with 0**

   ```text
   [0, x, x] → false
   ```

3. **Zeros in between (skip possible)**

   ```text
   [2, 0, 0] → true
   ```

4. **Unreachable gap**

   ```text
   [3, 2, 1, 0, 4] → false
   ```

---

## Complexity Analysis

* Time Complexity: `O(n)`
* Space Complexity: `O(1)`

---

## Core Logic Summary

* Track **maximum reachable index**
* Ensure every index is **reachable before using it**
* Expand reach greedily

---

## Final Insight

> “You are not choosing jumps — you are expanding reach.”

---
