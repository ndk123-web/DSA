
---

# Container With Most Water — LeetCode 11

**Pattern:** Two Pointers
**Difficulty:** Medium
**Topics:** Array, Greedy, Two Pointers

---

# 1. Problem

Given an array `height`, where `height[i]` represents the height of the i-th bar, choose two bars such that the container formed between them stores the maximum amount of water.

Water stored by bars at indices `i` and `j`:

```
area = min(height[i], height[j]) * (j - i)
```

Return the maximum possible area.

---

# 2. Brute Force Approach

### Idea

Check all pairs `(i, j)` and compute area using:

```
min(height[i], height[j]) * (j - i)
```

Track the maximum area.

### Why it works

Every pair of lines is considered. Nothing is missed. But time complexity is high.

### Code

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int maxAmount = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int area = min(height[i], height[j]) * (j - i);
                maxAmount = max(maxAmount, area);
            }
        }

        return maxAmount;
    }
};
```

### Complexity

* Time: O(n²)
* Space: O(1)

Brute force is correct but too slow for large arrays.

---

# 3. Optimal Approach — Two Pointers

### Idea

Use two pointers:

* left at start
* right at end

At each step:

1. Compute area with current left and right
2. Move the pointer which has the smaller height

   * because the smaller height limits the area
   * moving the larger height cannot increase the area unless the smaller one increases

This gives a linear time solution.

### Why it works

The key observation:

```
To increase area, width should reduce only if height can increase.

Height can increase only if we move the smaller line.
```

So one of the pointers always moves inward intelligently.

---

### Code

```cpp
class Solution {
public:
    int maxArea(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        int maxAmount = 0;

        while (left < right) {
            int currentAmount = min(nums[left], nums[right]) * (right - left);
            maxAmount = max(maxAmount, currentAmount);

            if (nums[left] < nums[right])
                left++;
            else
                right--;
        }

        return maxAmount;
    }
};
```

---

### Complexity

* Time: O(n)
* Space: O(1)

---

# 4. Summary

| Approach               | Idea                           | Time  | Space |
| ---------------------- | ------------------------------ | ----- | ----- |
| Brute Force            | Try all pairs                  | O(n²) | O(1)  |
| Two Pointers (Optimal) | Move pointer at smaller height | O(n)  | O(1)  |

Two-pointer method is the standard and optimal solution.

---

