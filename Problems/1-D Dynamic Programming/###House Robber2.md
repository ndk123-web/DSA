# Intuition

In the original **House Robber** problem, houses are arranged in a straight line.
We use the recurrence:

```
dp[i] = max(dp[i-1], nums[i] + dp[i-2])
```

At each house we decide:

- **Skip it** → keep the best profit until the previous house.
- **Rob it** → add current money and skip the previous house.

However, in **House Robber II**, the houses are arranged in a **circle**.
This means the **first and last houses are adjacent**, so we cannot rob both.

Therefore, two scenarios must be considered:

1. Rob houses from **index 0 to n-2** (exclude the last house)
2. Rob houses from **index 1 to n-1** (exclude the first house)

Each scenario becomes the **original linear House Robber problem**.

The final answer is the maximum of these two cases.

---

# Approach

### Case 1 — Exclude the last house

We compute the maximum robbery amount for houses:

```
[0 ... n-2]
```

DP initialization:

```
dp1[0] = nums[0]
dp1[1] = max(nums[0], nums[1])
```

Transition:

```
dp1[i] = max(dp1[i-1], dp1[i-2] + nums[i])
```

Loop until `n-2`.

---

### Case 2 — Exclude the first house

Now we compute for houses:

```
[1 ... n-1]
```

We shift the indexing for convenience.

Initialization:

```
dp2[0] = nums[1]
dp2[1] = max(nums[1], nums[2])
```

Transition:

```
dp2[i-1] = max(dp2[i-2], dp2[i-3] + nums[i])
```

Loop until the last house.

---

### Final Result

The optimal answer is:

```
max(dp1[n-2], dp2[n-2])
```

Because:

- `dp1[n-2]` → best robbery excluding the last house
- `dp2[n-2]` → best robbery excluding the first house

---

# Complexity

Time Complexity:

```
O(n)
```

We iterate through the array twice.

Space Complexity:

```
O(n)
```

Two DP arrays are used.

---

# Code

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);

        int dp1[n];
        int dp2[n];

        // Case 1: houses [0 ... n-2]
        dp1[0] = nums[0];
        dp1[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n - 1; i++) {
            dp1[i] = max(dp1[i - 1], dp1[i - 2] + nums[i]);
        }

        // Case 2: houses [1 ... n-1]
        dp2[0] = nums[1];
        dp2[1] = max(nums[1], nums[2]);

        for (int i = 3; i < n; i++) {
            dp2[i-1] = max(dp2[i-2], dp2[i-3] + nums[i]);
        }

        return max(dp1[n - 2], dp2[n - 2]);
    }
};
```

---

# Key Insight

The circular constraint only creates **one conflict**:
the first and last house cannot both be robbed.

By splitting the problem into two linear robberies and taking the maximum result, we eliminate that conflict and reuse the original **House Robber DP pattern**.
