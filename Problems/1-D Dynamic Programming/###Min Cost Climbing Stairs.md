# ✅ Problem: Min Cost Climbing Stairs

You are given an array `cost`, where `cost[i]` is the cost of stepping on stair `i`.

You can move:

- 1 step
- 2 steps

You can start from index `0` or `1`.

Goal: Reach just beyond the last index with minimum total cost.

---

# 🔵 Solution 1: Bottom-Up DP (Forward Build)

## 🧠 Intuition

To reach stair `i`, you must have come from:

- `i-1`
- `i-2`

So the minimum cost to reach `i` is:

```
dp[i] = cost[i] + min(dp[i-1], dp[i-2])
```

We build the solution from left to right.

---

## 🔧 Approach

1. Create DP array of size `n`.
2. Base cases:
   - `dp[0] = cost[0]`
   - `dp[1] = cost[1]`

3. Fill from `i = 2` to `n-1`
4. Final answer:
   - We can reach top from `n-1` or `n-2`
   - Return `min(dp[n-1], dp[n-2])`

---

## ⏱ Complexity

- Time Complexity: **O(n)**
- Space Complexity: **O(n)**

---

## 💻 Code (Bottom-Up)

```cpp
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int dp[n];

        dp[0] = cost[0];
        dp[1] = cost[1];

        for (int i = 2; i < n; i++) {
            dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
        }

        return min(dp[n - 1], dp[n - 2]);
    }
};
```

---

# 🔴 Solution 2: Reverse Bottom-Up (Backward Build)

Now here’s something interesting.

You flipped the direction.

Instead of asking:
“What is minimum cost to reach i?”

You asked:
“What is minimum cost starting from i to reach top?”

That changes state definition.

---

## 🧠 Intuition

Define:

```
dp[i] = minimum cost to reach the top starting from stair i
```

Now from stair `i`, you can go to:

- `i+1`
- `i+2`

So recurrence becomes:

```
dp[i] = cost[i] + min(dp[i+1], dp[i+2])
```

Now we build from right to left.

---

## 🔧 Approach

1. Base cases:
   - `dp[n-1] = cost[n-1]`
   - `dp[n-2] = cost[n-2]`

2. Iterate backward from `n-3` to `0`
3. Final answer:
   - We can start from 0 or 1
   - Return `min(dp[0], dp[1])`

---

## ⏱ Complexity

- Time Complexity: **O(n)**
- Space Complexity: **O(n)**

---

## 💻 Code (Backward Build)

```cpp
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int dp[n];

        dp[n-1] = cost[n-1];
        dp[n-2] = cost[n-2];

        for (int i = n-3; i >= 0; i--) {
            dp[i] = cost[i] + min(dp[i+1], dp[i+2]);
        }

        return min(dp[0], dp[1]);
    }
};
```

---

# 🧠 What’s the Deep Insight Here?

Both solutions are actually **bottom-up DP**.

Second one is NOT top-down.

Why?

Because:

- No recursion
- No memoization
- Just iterative filling

You simply changed the state definition.

Forward version:

- State = cost to reach i

Backward version:

- State = cost to go from i to top

Same problem.
Same recurrence pattern.
Different perspective.

---
