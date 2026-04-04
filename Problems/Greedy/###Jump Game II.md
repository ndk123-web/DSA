# Jump Game II – Complete Approaches (Greedy + DP)

## Problem Statement

Given an array `nums`, where each element represents the maximum jump length at that position, return the **minimum number of jumps** required to reach the last index.

You can assume that the last index is always reachable.

---

# 🧠 Intuition

This problem can be approached in **three different ways**:

1. **Local Greedy (Path-based thinking)**
2. **Optimal Greedy (Range / BFS thinking)**
3. **Dynamic Programming (DP)**

Each approach represents a different level of optimization and understanding.

---

# 🚀 Approach 1: Local Greedy (Path Selection)

## Idea

* From current index, explore reachable range
* Choose the next index that gives the **maximum future reach**
* Move step by step

---

## Code

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int curr = 0;      // current index
        int mn = 0;        // jump count
        int maxR = 0;      // maximum reachable from next range

        while (curr < n - 1){

            int st = curr + 1;
            int end = curr + nums[curr];
            
            // if we can reach end directly
            if (end >= n - 1) {
                return mn + 1;
            }

            bool foundMax = false;

            // find best next index inside current range
            for (int i = st; i <= end && i < n; i++) {
                if (i + nums[i] > maxR) {
                    foundMax = true;
                    curr = i;
                    maxR = nums[i] + i;
                }
            }

            // fallback (if no better found)
            if (!foundMax) {
                curr = curr + nums[curr];
            }

            mn++;
        }

        return mn;        
    }
};
```

---

## Key Insight

> Always choose the next position that maximizes future reach.

---

## Complexity

* Time: `O(n²)` (worst case)
* Space: `O(1)`

---

## Limitation

* Path-based greedy → not optimal
* Can be slower and complex

---

# ⚡ Approach 2: Optimal Greedy (Range / BFS Style)

## Idea

Instead of choosing a path, think in **levels (ranges)**:

* Each jump covers a range
* From that range, compute the **farthest next range**
* Increase jump count only when range ends

---

## Code

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        int farthest = 0;     // farthest reachable index
        int currentEnd = 0;   // end of current jump range
        int jump = 0;

        if (nums.size() == 1) return 0;

        for (int i = 0; i < nums.size(); i++) {

            // update farthest reachable index
            farthest = max(farthest, i + nums[i]);

            // if we reach end of current range
            if (currentEnd == i) {
                jump++;

                // if we can reach last index
                if (farthest >= nums.size() - 1 ) return jump;

                // move to next range
                currentEnd = farthest;
            }
        }

        return jump;      
    }
};
```

---

## Key Insight

> One jump = one range (not one index)

---

## Mental Model

* Expand range → `[start ... end]`
* From that range → compute next range
* Jump when range ends

---

## Complexity

* Time: `O(n)`
* Space: `O(1)`

---

## Why Optimal?

* No backtracking
* No nested loops
* Greedy works due to monotonic reach expansion

---

# 🧩 Approach 3: Dynamic Programming (DP)

## Idea

Define:

```text
dp[i] = minimum jumps required to reach index i
```

Transition:

```text
dp[j] = min(dp[j], dp[i] + 1)
```

where `j` is reachable from `i`

---

## Code

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, INT_MAX);

        dp[0] = 0; // starting point

        for (int i = 0; i < n - 1; i++) {

            int st = i + 1;
            int end = i + nums[i];

            // update all reachable indices
            for (int j = st; j <= end && j < n; j++) {
                dp[j] = min(dp[j], dp[i] + 1);
            }
        }

        return dp[n - 1] == INT_MAX ? 0 : dp[n - 1];
    }
};
```

---

## Key Insight

> Every index depends on all previous reachable indices

---

## Complexity

* Time: `O(n²)`
* Space: `O(n)`

---

## When to Use?

* When greedy is not obvious
* When problem explicitly asks for minimum steps

---

# 📊 Comparison

| Approach       | Idea               | Time  | Space | Notes                     |
| -------------- | ------------------ | ----- | ----- | ------------------------- |
| Local Greedy   | Best next index    | O(n²) | O(1)  | Intuitive but not optimal |
| Optimal Greedy | Range expansion    | O(n)  | O(1)  | Best solution             |
| DP             | Min cost per index | O(n²) | O(n)  | Clear but slower          |

---

# 🧠 Final Takeaways

* This problem is fundamentally:

  > **BFS on array (levels = jumps)**

* Key shift:

  * ❌ “Which index to jump to?”
  * ✅ “How far can I reach in this jump?”

---

# 💥 One-Line Summary

> Minimum jumps = number of times you expand your reachable range.

---
