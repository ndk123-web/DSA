# Jump Game VII – BFS + DP (Sliding Window)

## Problem Statement

You are given a binary string `s` and two integers `minJump` and `maxJump`.
You start at index `0` (which is always `'0'`).

You can jump from index `i` to index `j` if:

* `i + minJump ≤ j ≤ i + maxJump`
* `s[j] == '0'`

Return `true` if you can reach the last index, otherwise `false`.

---

# 🧠 Intuition

This is a **reachability problem**:

> Can we reach index `n-1` starting from index `0`?

There are two strong approaches:

1. **BFS (Graph traversal + optimization)**
2. **DP + Sliding Window (Optimized range checking)**

---

# 🚀 Approach 1: BFS + Sliding Window Optimization

## Idea

Treat indices as nodes in a graph:

* From each index `i`, you can jump to a range:

  ```
  [i + minJump → i + maxJump]
  ```

Use BFS to explore reachable indices.

---

## Optimization

Without optimization:

* Each node explores overlapping ranges → **O(n²)**

With optimization:

* Use `farthest` to avoid re-processing indices

---

## Key Insight

```text
farthest = last index already processed
```

So for each index `i`:

```text
start = max(i + minJump, farthest + 1)
```

---

## Code

```cpp
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        queue<int> q;
        int n = s.size();
        int farthest = 0;

        q.push(0);

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            int start = max(i + minJump, farthest + 1);
            int end = min(i + maxJump, n - 1);

            for (int j = start; j <= end; j++) {
                if (s[j] == '0') {
                    if (j == n - 1) return true;
                    q.push(j);
                }
            }

            // update processed boundary
            farthest = end;
        }

        return false;
    }
};
```

---

## Complexity

* Time: `O(n)`
* Space: `O(n)`

---

## Key Takeaway

> Each index is processed only once due to `farthest`.

---

# ⚡ Approach 2: DP + Sliding Window

## Idea

Define:

```text
dp[i] = true if index i is reachable
```

To compute `dp[i]`, check:

```text
Is there any j such that:
j ∈ [i - maxJump → i - minJump] AND dp[j] == true
```

---

## Problem

Checking this range for every `i` leads to:

```text
O(n²) ❌
```

---

## Optimization: Sliding Window

Maintain a count:

```text
cnt = number of reachable indices in current window
```

Window:

```text
[i - maxJump → i - minJump]
```

---

## How window moves

When `i` increases:

* Add new index → `i - minJump`
* Remove old index → `i - maxJump - 1`

---

## Code

```kotlin
class Solution {
    fun canReach(s: String, minJump: Int, maxJump: Int): Boolean {
        val n = s.length
        if (s[n - 1] == '1') return false

        val dp = BooleanArray(n)
        dp[0] = true

        var cnt = 0

        for (i in 1 until n) {

            // add new index to window
            if (i >= minJump && dp[i - minJump]) {
                cnt++
            }

            // remove old index from window
            if (i > maxJump && dp[i - maxJump - 1]) {
                cnt--
            }

            // check reachability
            if (cnt > 0 && s[i] == '0') {
                dp[i] = true
            }
        }

        return dp[n - 1]
    }
}
```

---

## Complexity

* Time: `O(n)`
* Space: `O(n)`

---

# 📊 Comparison

| Approach            | Idea                      | Time | Space |
| ------------------- | ------------------------- | ---- | ----- |
| BFS                 | Explore reachable indices | O(n) | O(n)  |
| DP + Sliding Window | Count reachable in range  | O(n) | O(n)  |

---

# 🧠 Key Concepts

### BFS Approach

* Graph traversal
* Avoid repeated work using `farthest`

### DP Approach

* State: `dp[i]`
* Transition: depends on previous range
* Sliding window removes nested loop

---

# 💥 Core Insight

> You don’t need to check all indices —
> just track if **any valid reachable index exists in the range**

---

# 🚀 Final One-Line Summary

> This problem is about **range-based reachability**, optimized using BFS or sliding window DP.

---
