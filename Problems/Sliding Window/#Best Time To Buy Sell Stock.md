
---

# Best Time to Buy and Sell Stock — LeetCode 121

**Pattern:** One-Pass Greedy, Running Minimum
**Difficulty:** Easy
**Goal:**
Find the maximum profit you can make by choosing **one day to buy** and a later day to **sell**.

```
profit = prices[sell] – prices[buy]
```

---

# 1. Two-Pointer Approach (Buy Pointer + Sell Pointer)

### Idea

Use two pointers:

* `left`  → potential **buy** day
* `right` → potential **sell** day

Move `right` forward, and:

* If `prices[right] > prices[left]` → profit possible
* Else if `prices[right] <= prices[left]` → better buying day found → move `left = right`

### Code

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int left = 0, n = prices.size();
        int maxProfit = 0;
        int right = 1;

        while (right < n) {
            if (prices[left] < prices[right]) {
                int currentProfit = prices[right] - prices[left];
                maxProfit = max(maxProfit, currentProfit);
            } else {
                left = right;            // Found a better buying price
            }
            right++;
        }

        return maxProfit;
    }
};
```

### Complexity

* Time: O(n)
* Space: O(1)

### Notes

This approach works by dynamically adjusting the best buy point whenever a cheaper price appears.

---

# 2. Running Minimum Approach (Kadane-Style)

### Idea

Maintain:

* `minDay` → lowest price so far
* For each day, compute possible profit: `prices[i] - minDay`
* Track maximum profit

### Code

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfit = INT_MIN;
        int minDay = INT_MAX;

        for (int price : prices) {
            minDay = min(minDay, price);           // best buy so far
            maxProfit = max(maxProfit, price - minDay);  // profit if sold today
        }

        return maxProfit;
    }
};
```

### Complexity

* Time: O(n)
* Space: O(1)

### Notes

This is the most common and simplified greedy approach.
Tracks best buy price and best sell profit in a single pass.

---

# Summary

| Approach                 | Idea                                      | Time | Space |
| ------------------------ | ----------------------------------------- | ---- | ----- |
| Two-Pointer              | Move buy/sell pointers depending on price | O(n) | O(1)  |
| Running Minimum (Greedy) | Track lowest price so far + profit        | O(n) | O(1)  |

Both solutions are optimal and follow the same underlying principle:
**Always buy at the lowest price seen so far and try selling at every future point.**

---
