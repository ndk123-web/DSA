---
# 📘 Minimum Size Subarray Sum

### **Brute → Better → Optimal (Sliding Window)**

Given an array `nums` and integer `target`, return the **minimum length** of a **contiguous subarray** whose sum is **≥ target**.
If no such subarray exists, return **0**.
---

# ## 🥇 1. Brute Force — O(n²) Time | O(1) Space

### **Idea**

Try every possible subarray and compute sum.

### **Code**

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int minLen = INT_MAX;

        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = i; j < n; j++) {
                sum += nums[j];
                if (sum >= target) {
                    minLen = min(minLen, j - i + 1);
                    break; // shorter window won't exist starting at i
                }
            }
        }

        return minLen == INT_MAX ? 0 : minLen;
    }
};
```

### **Short Comment**

- Check all subarrays
- Stop early when sum ≥ target
- Very slow for large input

---

# ## 🥈 2. Slight Improvement (Prefix Sum + Binary Search)

### **Time: O(n log n)**

### **Space: O(n)**

### **Idea**

- Build prefix sum array
- For each index, binary search next position where prefix sum ≥ target
- Smaller window found → update answer

(Advanced technique, not commonly preferred over sliding window)

---

# ## 🥉 3. Optimal Solution — Sliding Window (O(n) Time | O(1) Space)

### **Idea**

Use two pointers `left` and `right`.

Process:

1. Expand window by moving `right` and add to sum.
2. When sum ≥ target:

   - Update minimum length.
   - Shrink window from left while sum still ≥ target.

### **Code**

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int sum = 0;
        int minLen = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += nums[right];

            // shrink window while sum is valid
            while (sum >= target) {
                minLen = min(minLen, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }

        return minLen == INT_MAX ? 0 : minLen;
    }
};
```

### **Short Comment**

- Expand right → make sum large enough
- Shrink left → minimize window
- Both pointers move at most once → O(n)

---

# ## 🧠 Why Sliding Window Works?

For positive numbers:

- Increasing right only increases sum
- Moving left only decreases sum
- This guarantees correctness
- No need to recompute sums from scratch

Thus both pointers traverse the array only once.

---

# ## 🏁 Summary Table

| Approach                       | Time       | Space    | Notes             |
| ------------------------------ | ---------- | -------- | ----------------- |
| **Brute Force**                | O(n²)      | O(1)     | Try all subarrays |
| **Prefix Sum + Binary Search** | O(n log n) | O(n)     | Less common       |
| **Sliding Window (Optimal)**   | **O(n)**   | **O(1)** | Best solution     |

---
